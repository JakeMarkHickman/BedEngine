#include "OpenRenderer.h"

void Bed::OpenRenderer::Draw(const VertexArray* va, const IndexBuffer* ib, const Shader* shader)
{
    va->Bind();
    ib->Bind();
    shader->Bind();

    glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Bed::OpenRenderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}