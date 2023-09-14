#include <scene/game_scene.hpp>
#include <scene/iscene.hpp>
#include <prerequisites.hpp>
#include <objects/object.hpp>
#include <objects/camera.hpp>
#include <graph/renderer.hpp>
#include <io/user_input.hpp>
#include <io/data_loader.hpp>

#include <bgfx/bgfx.h>
#include <bx/math.h>

#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_transform.hpp>

#include <spdlog/spdlog.h>
#include <boost/ptr_container/ptr_vector.hpp>

using namespace nn;
using scene::GameScene;

GameScene::GameScene() {
    objects::Object* obj = new objects::Object("untitled.ply", "world", "wall");
    game_objects.push_back(obj);
    camera = new objects::Camera({ 0.0f, 0.0f, 5.0f }, { 1.0f, 1.0f, 1.0f });
    ms_tex_color = bgfx::createUniform("s_texColor", bgfx::UniformType::Sampler);
}

void GameScene::update(f32 delta) { 
    camera->input(delta);
}   

void GameScene::draw() {
    bgfx::setViewTransform(0, glm::value_ptr(camera->get_view_mat()), glm::value_ptr(graph::Renderer::get_proj_mat()));
    for (objects::Object &object : game_objects) {
        bgfx::setTransform(glm::value_ptr(object.get_model_mat()));
        bgfx::setState(0
        | BGFX_STATE_WRITE_RGB
        | BGFX_STATE_WRITE_A
        | BGFX_STATE_WRITE_Z
        | BGFX_STATE_DEPTH_TEST_LESS
        );
        object.draw_meshes(ms_tex_color);                                             
    }                                                                          
}

void GameScene::quit() {
    bgfx::destroy(ms_tex_color);
    for (objects::Object o : game_objects) {
        o.destroy_meshes();
    }
    game_objects.clear();
}
