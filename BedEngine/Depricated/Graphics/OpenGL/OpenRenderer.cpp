#include "OpenRenderer.h"
#include "OpenDebugger.h"

void Bed::OpenRenderer::Draw(const VertexArray* va, const IndexBuffer* ib, const ShaderAsset* shader) const
{
    va->Bind();
    ib->Bind();
    shader->Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Bed::OpenRenderer::DrawInstanced(const VertexArray* va, const IndexBuffer* ib, const InstanceBuffer* ivb, const ShaderAsset* shader) const
{
    va->Bind();
    ib->Bind();
    ivb->Bind();
    shader->Bind();

    GLCall(glDrawElementsInstanced(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr, ivb->GetInstanceCount()));
}

void Bed::OpenRenderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}