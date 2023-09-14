#include <prerequisites.hpp>
#include <graph/renderer.hpp>
#include <graph/mesh.hpp>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bgfx/defines.h>
#include <bx/math.h>

#include <glm/ext/matrix_clip_space.hpp>

#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>
#include <fmt/core.h>

using nn::graph::Renderer;

void Renderer::setup(u32 rgba, u32 x, u32 y, u32 width, u32 height) {
    set_clear_color(rgba);
    set_viewport(x, y, width, height);
}

glm::mat4 Renderer::get_proj_mat() {
    glm::mat4 proj(1.0f);
    proj = glm::perspective(70.f, WIN_WIDTH / float(WIN_HEIGHT), 0.01f, 1000.f);
    return proj;
}

void Renderer::present() {
    bgfx::touch(0);
    bgfx::frame();
}

void Renderer::set_clear_color(u32 rgba) {
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, rgba, 1.0f, 0);
    spdlog::debug("<Renderer:set_clear_color> clear color has been set to {0:X}", rgba);
}

void Renderer::set_viewport(u32 x, u32 y, u32 width, u32 height) {
    bgfx::setViewRect(0, 0, 0, width, height);
    spdlog::debug("<Renderer:set_viewport> viewport size has been set to {} {} {} {}", x, y, width, height);
}

GLFWwindow* Renderer::start_glfw() {
    spdlog::info("<Renderer:start_glfw> initializing glfw...");
    if (!glfwInit()) fatal_error("failed initializing glfw");
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    m_window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "nn", nullptr, nullptr);
    spdlog::info("<Renderer:start_glfw> initializing glfw - done!");
    return m_window;
}

void Renderer::start_bgfx() {
    spdlog::info("<Renderer:start_bgfx> initializing bgfx...");
    bgfx::Init bgfx_init;
    bgfx_init.type = bgfx::RendererType::Direct3D9;
    bgfx_init.platformData.nwh = glfwGetWin32Window(m_window);
    bgfx_init.resolution.width = BB_RES_X;
    bgfx_init.resolution.height = BB_RES_Y;
    bgfx_init.resolution.reset = BGFX_RESET_VSYNC;
    if (!bgfx::init(bgfx_init))
        fatal_error("could not initialize bgfx");
    spdlog::info("<Renderer:start_bgfx> initializing bgfx - done!");
}

void Renderer::quit() {}