#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ShaderAsset.h"

namespace Bed
{
    class Renderer
    {
    public:
        void Draw(const VertexArray* va, const IndexBuffer* ib, const ShaderAsset* shader) const;
        void Clear() const;
    };
}