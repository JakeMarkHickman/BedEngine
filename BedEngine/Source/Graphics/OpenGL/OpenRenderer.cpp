#include "OpenRenderer.h"
#include "OpenDebugger.h"

void Bed::OpenRenderer::Draw(const VertexArray* va, const IndexBuffer* ib, const Shader* shader)
{
    va->Bind();
    ib->Bind();
    shader->Bind();

    //for (int i = 0; i < ib->GetCount(); i++) {
    //    std::cout << "Index " << i << ": " << indices[i] << std::endl;
    //}

    GLCall(glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Bed::OpenRenderer::Clear()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}