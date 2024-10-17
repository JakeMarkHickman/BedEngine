#include "IndexBuffer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "OpenGL/OpenDebugger.h"

Bed::IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : m_Count(count)
{
    GLCall(glCreateBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_DYNAMIC_DRAW));
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