#include <graph/mesh.hpp>
#include <prerequisites.hpp>
#include <io/data_loader.hpp>
#include <graph/structs.hpp>

#include <bgfx/bgfx.h>

#include <spdlog/spdlog.h>
#include <fmt/core.h>
#include <vector>
#include <algorithm>

using nn::graph::Mesh;

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<u16> &indices, const std::string &shader, const std::string &texture) {
    bgfx::VertexLayout v_layout;
    v_layout.begin()
        .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
        .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float, true)
        .add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float)
    .end();
    Vertex vertices_arr[vertices.size()];
    std::copy(vertices.begin(), vertices.end(), vertices_arr);
    u16 indices_arr[indices.size()];
    std::copy(indices.begin(), indices.end(), indices_arr);
    m_vbh = bgfx::createVertexBuffer(bgfx::copy(vertices_arr, sizeof(vertices_arr)), v_layout);
    m_ibh = bgfx::createIndexBuffer(bgfx::copy(indices_arr, sizeof(indices_arr)));
    std::string vs_filename = fmt::format("vs_{}.bin", shader);
    std::string fs_filename = fmt::format("fs_{}.bin", shader);
    bgfx::ShaderHandle vsh = load_shader(vs_filename);
    bgfx::ShaderHandle fsh = load_shader(fs_filename);
    m_program = bgfx::createProgram(vsh, fsh, true);
    std::string tex_filename = fmt::format("{}.dds", texture);
    m_texh = load_texture(tex_filename);
}

void Mesh::draw(const bgfx::UniformHandle &sampler) {
    bgfx::setVertexBuffer(0, m_vbh);
    bgfx::setIndexBuffer(m_ibh);
    bgfx::setTexture(0, sampler, m_texh);
    bgfx::submit(0, m_program);
}

bgfx::VertexBufferHandle* Mesh::get_vbh() {
    return &m_vbh;
}

bgfx::IndexBufferHandle* Mesh::get_ibh() {
    return &m_ibh;
}

bgfx::TextureHandle* Mesh::get_texture() {
    return &m_texh;
}

void Mesh::destroy() {
    bgfx::destroy(m_texh);
    bgfx::destroy(m_program);
    bgfx::destroy(m_ibh);
    bgfx::destroy(m_vbh);
}