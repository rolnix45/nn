#include <GLFW/glfw3.h>
#include <cstdlib>
#include <game.hpp>
#include <prerequisites.hpp>
#include <graph/renderer.hpp>
#include <scene/game_scene.hpp>
#include <scene/iscene.hpp>
#include <io/user_input.hpp>

#include <spdlog/spdlog.h>

#include <memory>
#include <exception>
#include <chrono>
#include <thread>
#include <ratio>

using nn::Game;

Game::Game() {
    m_renderer = std::make_unique<graph::Renderer>();
    m_window = m_renderer->start_glfw();
    glfwSetKeyCallback(m_window, io::key_callback);
    glfwSetCursorPosCallback(m_window, io::mouse_callback);
    glfwSetCursorEnterCallback(m_window, io::mouse_enter_callback);
    glfwSetMouseButtonCallback(m_window, io::mouse_button_callback);
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(m_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    m_renderer->start_bgfx();
    m_scene = std::make_shared<scene::GameScene>();
    m_current_scene = std::dynamic_pointer_cast<scene::IScene>(m_scene);
    m_renderer->setup(0x303030FF, 0, 0, WIN_WIDTH, WIN_HEIGHT);
}

template <class Clock, class Duration>
void sleep_until(std::chrono::time_point<Clock, Duration> tp) {
    std::this_thread::sleep_until(tp - std::chrono::milliseconds(1));
    while (tp > Clock::now());
}

/**
 * @brief fucking mess
 * <br> attempt of getting deltatime (still not implemented), framerate and limiting fps
 * <br> tried to mark what some things to make it clearer but, doesn't help much
 * <br> i dunno, if it works, it works
 * <br> if you know better solution tell me
 */
void Game::run() {
    using namespace std::chrono;
    using frame_duration = duration<int, std::ratio<1, 100>>; // FPS LIMIT 100
    auto nextFrame = steady_clock::now() + frame_duration{ 1 }; // limit
    auto startTime = std::chrono::steady_clock::now(); // counter
    u32 frameCount = 0; // counter
    while (!glfwWindowShouldClose(m_window)) {
        auto currentTime = steady_clock::now(); // counter
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count(); // counter
        frameCount++; // counter
        update(m_delta_time);
        draw();
        if (elapsedTime >= 1) {     // counter
            u32 fps = frameCount / elapsedTime;
            spdlog::debug("FPS: {}", fps);
            frameCount = 0;
            startTime = currentTime;  
        } 
        sleep_until(nextFrame);  // limit
        nextFrame += frame_duration{ 1 }; // limit
    }
    bgfx::shutdown();
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Game::update(f32 delta) {
    glfwPollEvents();
    if (io::is_pressed(GLFW_KEY_ESCAPE))
        quit();
    m_current_scene->update(delta);
}

void Game::draw() {
    m_current_scene->draw();
    m_renderer->present();
}

void Game::quit() {
    m_current_scene->quit();
    m_renderer->quit();
    glfwSetWindowShouldClose(m_window, GLFW_TRUE);
}