#pragma once

#include <Graphics/Renderer.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Bed
{
    class OpenRenderer : public Bed::Renderer
    {
    public:
        void Draw(const VertexArray* va, const IndexBuffer* ib, const ShaderAsset* shader) const override;
        void DrawInstanced(const VertexArray* va, const IndexBuffer* ib, const InstanceBuffer* ivb, const ShaderAsset* shader) const override;
        void Clear() const override;
    };
}