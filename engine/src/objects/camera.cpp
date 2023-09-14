#include <objects/camera.hpp>
#include <prerequisites.hpp>
#include <io/user_input.hpp>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_transform.hpp>

#include <memory>
#include <spdlog/spdlog.h>

using namespace nn;
using objects::Camera;

Camera::Camera() : m_position({ 0.0f, 0.0f, 0.0f }), m_rotation({ 0.0f, 0.0f, 0.0f }) {}
Camera::Camera(const glm::vec3 &pos, const glm::vec3 &rot) : m_position(std::move(pos)), m_rotation(std::move(rot)) {}

glm::mat4 nn::objects::Camera::get_view_mat() {
    glm::mat4 view(1.0f);
    view = glm::rotate(view, glm::radians(m_rotation.x), { 1, 0, 0 });
    view = glm::rotate(view, glm::radians(m_rotation.y), { 0, 1, 0 });
    view = glm::translate(view, -m_position);
    return view;
}

glm::vec2 previous_pos(0.f);
void Camera::input(f32 delta) {
    glm::vec3 cam_offset(0.0f);
    if (io::is_pressed(GLFW_KEY_W))
        cam_offset.z -= CAM_SPEED;
    if (io::is_pressed(GLFW_KEY_S))
        cam_offset.z += CAM_SPEED;
    if (io::is_pressed(GLFW_KEY_A))
        cam_offset.x -= CAM_SPEED;
    if (io::is_pressed(GLFW_KEY_D))
        cam_offset.x += CAM_SPEED;
    if (io::is_pressed(GLFW_KEY_Z))
        cam_offset.y += CAM_SPEED;
    if (io::is_pressed(GLFW_KEY_X))
        cam_offset.y -= CAM_SPEED;
    move(cam_offset * delta);
    
    if (!io::is_mouse_on_window()) return;
    glm::vec2 current_pos = *io::get_mouse_pos();
    glm::vec2 display(0.f);
    f32 delta_x = current_pos.x - previous_pos.x;
    f32 delta_y = current_pos.y - previous_pos.y;
    bool rotate_x = delta_x != 0;
    bool rotate_y = delta_y != 0;
    if (rotate_x) display.y = delta_x;
    if (rotate_y) display.x = delta_y;
    previous_pos = current_pos;
    rotate({ delta * (display * MOUSE_SENS), 0.0f });
}

void nn::objects::Camera::move(const glm::vec3 &offset) {
    if (offset.z != 0) {
        m_position.x += glm::sin<f32>(glm::radians<f32>(m_rotation.y)) * -1.0f * offset.z;
        m_position.z += glm::cos<f32>(glm::radians<f32>(m_rotation.y)) * offset.z;
    }
    if (offset.x != 0) {
        m_position.x += glm::sin<f32>(glm::radians<f32>(m_rotation.y - 90)) * -1.0f * offset.x;
        m_position.z += glm::cos<f32>(glm::radians<f32>(m_rotation.y - 90)) * offset.x;
    }
    m_position.y += offset.y;
}

void nn::objects::Camera::rotate(const glm::vec3 &offset) {
    m_rotation += offset;
}

glm::vec3* nn::objects::Camera::get_pos() {
    return &m_position;
}

glm::vec3* nn::objects::Camera::get_rot() {
    return &m_rotation;    
}

void nn::objects::Camera::set_pos(const glm::vec3 &pos) {
    m_position = std::move(pos);
}

void nn::objects::Camera::set_rot(const glm::vec3 &rot) {
    m_rotation = std::move(rot);    
}

