#include "Renderer.h"
#include "OpenGL/OpenRenderer.h"

void Bed::Renderer::Draw(const VertexArray* va, const IndexBuffer* ib, const Shader* shader) const
{
    Bed::OpenRenderer::Draw(va, ib, shader);
}

void Bed::Renderer::Clear() const
{
    Bed::OpenRenderer::Clear();
}