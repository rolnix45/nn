#pragma once

#include <prerequisites.hpp>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace nn::objects {

#define MOUSE_SENS 1.50f
#define CAM_SPEED 24

class Camera {
public:
    Camera();
    Camera(const glm::vec3 &pos, const glm::vec3 &rot);
    glm::mat4 get_view_mat();
    void input(f32 delta);
    void move(const glm::vec3 &offset);
    void rotate(const glm::vec3 &offset);
    glm::vec3* get_pos();
    glm::vec3* get_rot();
    void set_pos(const glm::vec3 &pos);
    void set_rot(const glm::vec3 &rot);
private:
    glm::vec3 m_position;
    glm::vec3 m_rotation;
};

} // end namespace