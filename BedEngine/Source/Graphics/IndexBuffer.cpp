#include "IndexBuffer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "OpenGL/OpenDebugger.h"

Bed::IndexBuffer::IndexBuffer(unsigned int size) : m_Count(size)
{
    GLCall(glCreateBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(unsigned int), nullptr, GL_DYNAMIC_DRAW));
}

Bed::IndexBuffer::IndexBuffer(const void* data, unsigned int size) : m_Count(size)
{
    GLCall(glCreateBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
}

Bed::IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void Bed::IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void Bed::IndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void Bed::IndexBuffer::PopulateBuffer(const void* indices, unsigned int size, unsigned int offset)
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, indices));
}