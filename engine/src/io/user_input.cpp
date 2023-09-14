#include <io/user_input.hpp>
#include <prerequisites.hpp>

#include <glm/vec2.hpp>
#include <spdlog/spdlog.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace nn::io {

bool keys[32767];
void key_callback(GLFWwindow* wnd, s32 key, s32 scancode, s32 action, s32 mods) {
    if (key != GLFW_KEY_UNKNOWN) {
        keys[key] = action != GLFW_RELEASE;
    }
}

bool is_pressed(s32 key) {
    return keys[key];
}

glm::vec2 mouse_pos;
void mouse_callback(GLFWwindow* wnd, f64 x, f64 y) {
    mouse_pos = { x, y };
}

glm::vec2* get_mouse_pos() {
    return &mouse_pos;
}

bool mow;
void mouse_enter_callback(GLFWwindow* wnd, s32 entered) {
    mow = entered;
}

bool is_mouse_on_window() {
    return mow;
}

void mouse_button_callback(GLFWwindow *wnd, s32 button, s32 action, s32 mods) {
    if (button != GLFW_KEY_UNKNOWN) {
        keys[button] = action != GLFW_RELEASE;
    }
}

} // end namespace
