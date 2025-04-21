#include "GraphicVariables.h"

namespace Bed
{
    //3D
    Bed::ShaderAsset* shader3D = nullptr;
    Bed::VertexBuffer* vb3D = nullptr;
    Bed::IndexBuffer* ib3D = nullptr;
    Bed::VertexArray* va3D = nullptr;
    Bed::StorageBuffer* pointLightBuffer = nullptr;
    Bed::StorageBuffer* directionalLightBuffer = nullptr;
    Bed::StorageBuffer* spotLightBuffer = nullptr;

    //2D
    Bed::ShaderAsset* shader2D = nullptr;
    Bed::VertexBuffer* vb2D = nullptr;
    Bed::IndexBuffer* ib2D = nullptr;
    Bed::VertexArray* va2D = nullptr;

    //UI
    Bed::ShaderAsset* shaderUI = nullptr;
    Bed::VertexBuffer* vbUI = nullptr;
    Bed::IndexBuffer* ibUI = nullptr;
    Bed::VertexArray* vaUI = nullptr;

    //shared
    Bed::Renderer* renderer = nullptr;
}