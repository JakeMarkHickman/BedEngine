#pragma once

#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"

#include <Bed/Core.h>

namespace Bed
{
    BED_API Bed::Shader* shader;
    BED_API Bed::Renderer* renderer;
    BED_API Bed::IndexBuffer* ib;
    BED_API Bed::VertexArray* va;
    BED_API Bed::VertexBuffer* vb;
    BED_API Bed::Texture* texture;
}