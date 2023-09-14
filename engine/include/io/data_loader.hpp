#pragma once

#include <graph/mesh.hpp>

#include <bgfx/bgfx.h>
#include <string>
#include <vector>

bgfx::ShaderHandle load_shader(const std::string &filename);
bgfx::TextureHandle load_texture(const std::string &filename);
std::vector<nn::graph::Mesh> load_mesh(const std::string &filename, const std::string &shader, const std::string &texture);