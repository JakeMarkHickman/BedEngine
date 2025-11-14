#include "StorageBuffer.h"

#include <Graphics/OpenGL/OpenDebugger.h>

Bed::StorageBuffer::StorageBuffer(unsigned int size)
{
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_SHADER_STORAGE_BUFFER, size, nullptr, GL_DYNAMIC_DRAW));
    //GLCall(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_RendererID));
}

Bed::StorageBuffer::~StorageBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void Bed::StorageBuffer::Bind(unsigned int bindingPoint) const
{
    GLCall(glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_RendererID));
    GLCall(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingPoint, m_RendererID));
}

void Bed::StorageBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0));
}

void Bed::StorageBuffer::PopulateBuffer(const void* data, unsigned int size, unsigned int offset)
{
    GLCall(glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_RendererID));
    GLCall(glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, size, data));
}