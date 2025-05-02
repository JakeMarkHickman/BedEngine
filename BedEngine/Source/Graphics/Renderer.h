#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "InstanceBuffer.h"
#include "ShaderAsset.h"

namespace Bed
{
    class Renderer
    {
    public:
        virtual void Draw(const VertexArray* va, const IndexBuffer* ib, const ShaderAsset* shader) const {};
        virtual void DrawInstanced(const VertexArray* va, const IndexBuffer* ib, const InstanceBuffer* ivb, const ShaderAsset* shader) const {};
        virtual void Clear() const {};
    };
}