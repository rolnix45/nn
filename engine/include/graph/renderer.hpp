#pragma once

#include <prerequisites.hpp>
#include <graph/mesh.hpp>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include <glm/mat4x4.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace nn::graph {

//! @brief window size
#define WIN_WIDTH 1280
#define WIN_HEIGHT 960

//! @brief backbuffer resolution
#define BB_RES_X WIN_WIDTH //512
#define BB_RES_Y WIN_HEIGHT //384

class Renderer {
public:
    void setup(u32 rgba, u32 x, u32 y, u32 width, u32 height);
    static glm::mat4 get_proj_mat();
    void present();
    GLFWwindow* start_glfw();
    void start_bgfx();
    void set_clear_color(u32 rgba);
    void set_viewport(u32 x, u32 y, u32 width, u32 height);
    void quit();
private:
    GLFWwindow* m_window;
};

} // end namespace