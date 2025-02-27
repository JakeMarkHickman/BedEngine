#include "VertexBuffer.h"
#include "Vertex.h"
#include <Graphics/OpenGL/OpenDebugger.h>

Bed::VertexBuffer::VertexBuffer(unsigned int size)
{
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size * sizeof(Bed::Vertex), nullptr, GL_DYNAMIC_DRAW));
}

Bed::VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void Bed::VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void Bed::VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void Bed::VertexBuffer::PopulateBuffer(const void* verts, unsigned int size, unsigned int offset)
{
    std::cout << size << "\n";
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, offset, size, verts));
}