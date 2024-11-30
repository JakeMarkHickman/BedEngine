#pragma once

//TODO: Completely restructure this, no gobal variables!!

#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"

#include <Bed/Core.h>

namespace Bed
{
    extern Bed::Shader* shader;
    extern Bed::Renderer* renderer;
    extern Bed::IndexBuffer* ib;
    extern Bed::VertexArray* va;
    extern Bed::VertexBuffer* vb;
    extern Bed::Texture* texture;
}