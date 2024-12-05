#include "GraphicVariables.h"

namespace Bed
{
    //3D
    extern Bed::Shader* shader = nullptr;
    extern Bed::IndexBuffer* ib = nullptr;
    extern Bed::VertexArray* va = nullptr;

    //UI
    extern Bed::Shader* shaderUI = nullptr;
    extern Bed::VertexBuffer* vbUI = nullptr;
    extern Bed::IndexBuffer* ibUI = nullptr;
    extern Bed::VertexArray* vaUI = nullptr;

    //shared
    extern Bed::Renderer* renderer = nullptr;
    extern Bed::VertexBuffer* vb = nullptr;
    extern Bed::Texture* texture = nullptr;
}