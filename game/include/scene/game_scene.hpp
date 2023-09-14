#pragma once

#include <objects/object.hpp>
#include <objects/camera.hpp>
#include <prerequisites.hpp>
#include <scene/iscene.hpp>
#include <graph/mesh.hpp>

#include <bgfx/bgfx.h>
#include <boost/ptr_container/ptr_vector.hpp>

using namespace nn;

namespace nn::scene {


class GameScene : public IScene {
public:
    GameScene();
    void update(f32 delta) override;
    void draw() override;
    void quit() override;
private:
    boost::ptr_vector<objects::Object> game_objects;
    objects::Camera* camera;
    bgfx::UniformHandle ms_tex_color;
};

} // end namespace