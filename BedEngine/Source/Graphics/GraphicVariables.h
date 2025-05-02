#pragma once

//TODO: Completely restructure this, no gobal variables!!

#include "ShaderAsset.h"
#include "Renderer.h"
#include "StorageBuffer.h"
#include "InstanceArray.h"

#include <Bed/Core.h>

namespace Bed
{
    //3D
    extern Bed::ShaderAsset* shader3D;
    extern Bed::VertexBuffer* vb3D;
    extern Bed::IndexBuffer* ib3D;
    extern Bed::VertexArray* va3D;
    extern Bed::InstanceBuffer* ivb3D;
    extern Bed::StorageBuffer* pointLightBuffer;
    extern Bed::StorageBuffer* directionalLightBuffer;
    extern Bed::StorageBuffer* spotLightBuffer;

    //2D
    extern Bed::ShaderAsset* shader2D;
    extern Bed::VertexBuffer* vb2D;
    extern Bed::IndexBuffer* ib2D;
    extern Bed::VertexArray* va2D;
    extern Bed::InstanceBuffer* ivb2D;

    //UI
    extern Bed::ShaderAsset* shaderUI;
    extern Bed::VertexBuffer* vbUI;
    extern Bed::IndexBuffer* ibUI;
    extern Bed::VertexArray* vaUI;
    extern Bed::InstanceBuffer* ivbUI;
    extern Bed::InstanceArray* ivaUI;

    //shared
    extern Bed::Renderer* renderer;
}