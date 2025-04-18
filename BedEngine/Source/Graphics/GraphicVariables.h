#pragma once

//TODO: Completely restructure this, no gobal variables!!

#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include "StorageBuffer.h"

#include <Bed/Core.h>

namespace Bed
{
    //3D
    extern Bed::Shader* shader3D;
    extern Bed::VertexBuffer* vb3D;
    extern Bed::IndexBuffer* ib3D;
    extern Bed::VertexArray* va3D;
    extern Bed::StorageBuffer* pointLightBuffer;
    extern Bed::StorageBuffer* directionalLightBuffer;
    extern Bed::StorageBuffer* spotLightBuffer;

    //2D
    extern Bed::Shader* shader2D;
    extern Bed::VertexBuffer* vb2D;
    extern Bed::IndexBuffer* ib2D;
    extern Bed::VertexArray* va2D;

    //UI
    extern Bed::Shader* shaderUI;
    extern Bed::VertexBuffer* vbUI;
    extern Bed::IndexBuffer* ibUI;
    extern Bed::VertexArray* vaUI;

    //shared
    extern Bed::Renderer* renderer;
}