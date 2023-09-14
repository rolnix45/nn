#pragma once

#include <prerequisites.hpp>

#include <glm/vec2.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace nn::io {

void key_callback(GLFWwindow* wnd, s32 key, s32 scancode, s32 action, s32 mods);
bool is_pressed(s32 key);

void mouse_callback(GLFWwindow* wnd, f64 x, f64 y);
glm::vec2* get_mouse_pos();

void mouse_enter_callback(GLFWwindow* wnd, s32 entered);
bool is_mouse_on_window();

void mouse_button_callback(GLFWwindow* wnd, s32 button, s32 action, s32 mods);

} // end namespace