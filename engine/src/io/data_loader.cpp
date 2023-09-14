#include <graph/structs.hpp>
#include <io/data_loader.hpp>
#include <prerequisites.hpp>
#include <graph/mesh.hpp>

#include <bgfx/bgfx.h>
#include <bgfx/defines.h>

#include <spdlog/spdlog.h>
#include <fmt/core.h>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/mesh.h>

#include <tuple>
#include <vector>
#include <string>
#include <cstdio>
#include <filesystem>
#include <fstream>

/*

    TODO:
    OPTIMIZE LOADING DATA:
    LOAD ONCE NOT PER MESH / OBJECT

*/

bgfx::ShaderHandle load_shader(const std::string &filename) {
    std::string shader_path = fmt::format("assets/shaders/{}", filename);
    std::ifstream input_stream(shader_path, std::ios::binary);
    if (!input_stream.is_open()) {
        fatal_error(fmt::format("<load_shader> {} not found", filename));
    }
    input_stream.seekg(0, std::ios::end);
    const long file_size = input_stream.tellg();
    input_stream.seekg(0);
    const bgfx::Memory* mem = bgfx::alloc(file_size + 1);
    input_stream.read(reinterpret_cast<char*>(mem->data), file_size);
    mem->data[mem->size - 1] = '\0';
    spdlog::info("<load_shader> {} loaded", filename);
    return bgfx::createShader(mem);
}

bgfx::TextureHandle load_texture(const std::string &filename) {
    std::string texture_path = fmt::format("assets/textures/{}", filename);
    std::ifstream input_stream(texture_path, std::ios::binary);
    if (!input_stream.is_open()) {
        fatal_error(fmt::format("<load_texture> {} not found", filename));
    }
    input_stream.seekg(0, std::ios::end);
    const long file_size = input_stream.tellg();
    input_stream.seekg(0);
    const bgfx::Memory* mem = bgfx::alloc(file_size + 1);
    input_stream.read(reinterpret_cast<char*>(mem->data), file_size);
    mem->data[mem->size - 1] = '\0';
    spdlog::info("<load_texture> {} loaded", filename);
    return bgfx::createTexture(mem);
}


std::vector<nn::graph::Mesh> meshes;
using nn::graph::Mesh;
Mesh process_mesh(aiMesh* mesh, const aiScene* scene, const std::string &shader, const std::string &texture) {
    using nn::graph::Vertex;
    std::vector<Vertex> vertices;
    std::vector<u16> indices;
    for (u32 i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        if (mesh->mTextureCoords[0]) {
            vertex.tex_coord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        }
        vertices.push_back(vertex);
    }
    for (u16 i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (u16 j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }
    return Mesh(vertices, indices, shader, texture);
}

void process_node(aiNode* node, const aiScene* scene, const std::string &shader, const std::string &texture) {
    for (u32 i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[i];
        meshes.push_back(process_mesh(mesh, scene, shader, texture));
    }
    for (UINT i = 0; i < node->mNumChildren; i++) {
		process_node(node->mChildren[i], scene, shader, texture);
	}
}

#define ASSIMP_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices)
std::vector<Mesh> load_mesh(const std::string &filename, const std::string &shader, const std::string &texture) {
    std::string model_path = fmt::format("assets/models/{}", filename);
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(model_path, ASSIMP_FLAGS);
    if (scene == nullptr) {
        fatal_error(fmt::format("<load_mesh> {} loading failed", filename));
    }
    process_node(scene->mRootNode, scene, shader, texture);
    return meshes;
}
