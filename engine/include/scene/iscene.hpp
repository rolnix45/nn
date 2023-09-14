#pragma once

#include <prerequisites.hpp>

namespace nn::scene {

class IScene {
public:
    virtual ~IScene();
    virtual void update(f32 delta);
    virtual void draw();
    virtual void quit();
};

} // end namespace