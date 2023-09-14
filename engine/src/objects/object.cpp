#include <objects/object.hpp>
#include <prerequisites.hpp>
#include <graph/mesh.hpp>
#include <io/data_loader.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_transform.hpp>

using namespace nn;
using objects::Object;

Object::Object(const std::string &mesh_file, const std::string &shader, const std::string &texture) {
    m_position = { 0.0f, 0.0f, 0.0f };
    m_rotation = { 1.0f, 1.0f, 1.0f };
    m_scale = { 1.0f, 1.0f, 1.0f };
    m_meshes = load_mesh(mesh_file, shader, texture);
}

glm::mat4 Object::get_model_mat() {
    glm::mat4 model_mat(1.0f);
    model_mat = glm::translate(model_mat, *get_pos());
    model_mat = glm::rotate(model_mat, 0.f, *get_rot());
    model_mat = glm::scale(model_mat, *get_scale());
    return model_mat;
}

void Object::draw_meshes(const bgfx::UniformHandle &sampler) {
    for (graph::Mesh m : m_meshes) {
        m.draw(sampler);
    }
}

void Object::destroy_meshes() {
    for (graph::Mesh m : m_meshes) {
        m.destroy();
    }
}

graph::Mesh Object::get_mesh(u8 at) const {
    return m_meshes.at(at);
}

glm::vec3* Object::get_pos() {
    return &m_position;
}

glm::vec3* Object::get_rot() {
    return &m_rotation;
}

glm::vec3* Object::get_scale() {
    return &m_scale;
}

void Object::set_mesh(graph::Mesh* mesh, u8 at) {
    m_meshes.at(at) = *mesh;
}

void Object::set_pos(const glm::vec3 &pos) {
    m_position = pos;
}

void Object::set_rot(const glm::vec3 &rot) {
    m_rotation = rot;
}

void Object::set_scale(const glm::vec3 &scale) {
    m_scale = scale;
}
