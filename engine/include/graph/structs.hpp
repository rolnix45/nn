#pragma once

#include <prerequisites.hpp>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace nn::graph {

typedef struct Vertex {
    glm::vec3 position;
    glm::vec2 tex_coord;
    glm::vec3 normal;
} Vertex;

} // end namespace