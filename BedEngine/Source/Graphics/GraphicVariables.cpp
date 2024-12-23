#include "GraphicVariables.h"

namespace Bed
{
    //3D
    extern Bed::Shader* shader3D = nullptr;
    extern Bed::VertexBuffer* vb3D = nullptr;
    extern Bed::IndexBuffer* ib3D = nullptr;
    extern Bed::VertexArray* va3D = nullptr;

    //2D
    extern Bed::Shader* shader2D = nullptr;
    extern Bed::VertexBuffer* vb2D = nullptr;
    extern Bed::IndexBuffer* ib2D = nullptr;
    extern Bed::VertexArray* va2D = nullptr;

    //UI
    extern Bed::Shader* shaderUI = nullptr;
    extern Bed::VertexBuffer* vbUI = nullptr;
    extern Bed::IndexBuffer* ibUI = nullptr;
    extern Bed::VertexArray* vaUI = nullptr;

    //shared
    extern Bed::Renderer* renderer = nullptr;
    extern Bed::Texture* texture = nullptr;
}