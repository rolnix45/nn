#pragma once

#include <prerequisites.hpp>
#include <graph/renderer.hpp>
#include <scene/iscene.hpp>
#include <scene/game_scene.hpp>

#include <bgfx/bgfx.h>
#include <GLFW/glfw3.h>

#include <chrono>
#include <memory>

namespace nn {

class Game {
public:
    Game();
    void run();
protected:
    void update(f32 delta);
    void draw();
    void quit();
    f32 m_delta_time = 0.01f;
    GLFWwindow* m_window;
    std::unique_ptr<graph::Renderer> m_renderer;
    std::shared_ptr<scene::IScene> m_current_scene;
    std::shared_ptr<scene::GameScene> m_scene;
};

} // end namespace