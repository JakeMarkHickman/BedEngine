#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

namespace Bed
{
    class Renderer
    {
    public:
        void Draw(const VertexArray* va, const IndexBuffer* ib, const Shader* shader) const;
        void Clear() const;
    };
}