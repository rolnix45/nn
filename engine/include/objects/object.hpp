#pragma once

#include <prerequisites.hpp>
#include <graph/mesh.hpp>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <vector>

namespace nn::objects {

class Object {
public:
    explicit Object(const std::string &mesh_file, const std::string &shader, const std::string &texture);

    glm::mat4 get_model_mat();
    void draw_meshes(const bgfx::UniformHandle &sampler);
    void destroy_meshes();

    // getters
    graph::Mesh get_mesh(u8 at) const;
    glm::vec3* get_pos();
    glm::vec3* get_rot();
    glm::vec3* get_scale();

    //setters
    void set_mesh(graph::Mesh* mesh, u8 at);
    void set_pos(const glm::vec3 &pos);
    void set_rot(const glm::vec3 &rot);
    void set_scale(const glm::vec3 &scale);
private:
    std::vector<graph::Mesh> m_meshes;
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
};

} // end namespace