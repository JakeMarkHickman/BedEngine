#pragma once

//TODO: Completely restructure this, no gobal variables!!

#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"

#include <Bed/Core.h>

namespace Bed
{
    //3D
    extern Bed::Shader* shader;
    extern Bed::VertexBuffer* vb;
    extern Bed::IndexBuffer* ib;
    extern Bed::VertexArray* va;

    //UI
    extern Bed::Shader* shaderUI;
    extern Bed::VertexBuffer* vbUI;
    extern Bed::IndexBuffer* ibUI;
    extern Bed::VertexArray* vaUI;

    //shared
    extern Bed::Renderer* renderer;
    extern Bed::Texture* texture;
}