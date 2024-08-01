#include "Renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void Bed::Renderer::Draw(const VertexArray* va, const IndexBuffer* ib, const Shader* shader) const
{
    va->Bind();
    ib->Bind();
    shader->Bind();

    glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Bed::Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}