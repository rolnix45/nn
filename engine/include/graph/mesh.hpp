#pragma once

#include <prerequisites.hpp>
#include <graph/structs.hpp>

#include <bgfx/bgfx.h>
#include <string>

namespace nn::graph {

class Mesh {
public:
    Mesh(
        const std::vector<Vertex> &vertices, 
        const std::vector<u16> &indices, 
        const std::string &shader,
        const std::string &texture
    );
    void draw(const bgfx::UniformHandle &sampler);
    bgfx::VertexBufferHandle* get_vbh();
    bgfx::IndexBufferHandle* get_ibh();
    bgfx::TextureHandle* get_texture();
    void destroy();
private:
    bgfx::VertexBufferHandle m_vbh;
    bgfx::IndexBufferHandle m_ibh;
    bgfx::ProgramHandle m_program;
    bgfx::TextureHandle m_texh;
};

} // end namespace