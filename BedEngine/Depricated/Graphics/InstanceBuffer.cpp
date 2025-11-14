#include "InstanceBuffer.h"

#include "OpenGL/OpenDebugger.h"

Bed::InstanceBuffer::InstanceBuffer(unsigned int maxInstances, unsigned int dataSize) : m_MaxInstanced(maxInstances), m_DataSize(dataSize)
{
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, maxInstances * m_DataSize, nullptr, GL_DYNAMIC_DRAW));
}

Bed::InstanceBuffer::~InstanceBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void Bed::InstanceBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void Bed::InstanceBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void Bed::InstanceBuffer::PopulateBuffer(const void* data, unsigned int count)
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));

    /*std::cout << "DataSize: " << m_DataSize << ", Count: " << count << ", Total Size: " << (count * m_DataSize) << "\n";

    if(count <= 0 || m_DataSize <= 0)
    {
        GLCall(glBufferData(GL_ARRAY_BUFFER, count * m_DataSize, nullptr, GL_DYNAMIC_DRAW));
        std::cout << "Data Skiped\n";
        return;
    }

    GLCall(glBufferData(GL_ARRAY_BUFFER, count * m_DataSize, data, GL_DYNAMIC_DRAW));*/

    GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, count * m_DataSize, data));
} 