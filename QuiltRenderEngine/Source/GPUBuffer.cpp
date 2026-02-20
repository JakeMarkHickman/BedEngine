#include "GPUBuffer.h"
#include "OpenGl/OpenDebugger.h"

unsigned int Quilt::BufferManager::CreateBuffer(BufferType type, unsigned int dataSize, unsigned int dataCount)
{
    uint32_t bufferID;

    if(!m_RemovedBuffers.empty())
    {
        bufferID = m_RemovedBuffers.back();
        m_RemovedBuffers.pop_back();

        LOG_INFO("Recycled Buffer: ", bufferID);
    }
    else
    {
        bufferID = m_GPUBufferCount;
        m_GPUBufferCount++;

        m_BufferStorage.Types.resize(m_GPUBufferCount);
        m_BufferStorage.DataSizes.resize(m_GPUBufferCount);
        m_BufferStorage.DataCounts.resize(m_GPUBufferCount);
        m_BufferStorage.Handles.resize(m_GPUBufferCount);

        LOG_INFO("Created Buffer: ", bufferID);
    }

    m_BufferStorage.Types[bufferID] = type;
    m_BufferStorage.DataSizes[bufferID] = dataSize;
    m_BufferStorage.DataCounts[bufferID] = dataCount;

    unsigned int bufferType = GetBufferType(type);

    GLCall(glGenBuffers(1, &m_BufferStorage.Handles[bufferID]));
    GLCall(glBindBuffer(bufferType, m_BufferStorage.Handles[bufferID]));
    
    GLCall(glBufferData(bufferType, m_BufferStorage.DataSizes[bufferID] * m_BufferStorage.DataCounts[bufferID], nullptr, GL_DYNAMIC_DRAW)); //TODO: This needs to change later to support shader storage and instances

    return bufferID;
}

void Quilt::BufferManager::RemoveBuffer(unsigned int bufferID)
{
    LOG_INFO("Removing Buffer: ", bufferID);

    GLCall(glDeleteBuffers(1, &m_BufferStorage.Handles[bufferID]));
    m_RemovedBuffers.push_back(bufferID);
}

void Quilt::BufferManager::PopulateBuffer(unsigned int bufferID, const void* data, unsigned int size, unsigned int offset)
{
    unsigned int type = GetBufferType(m_BufferStorage.Types[bufferID]);

    GLCall(glBindBuffer(type, m_BufferStorage.Handles[bufferID]));
    GLCall(glBufferSubData(type, offset * m_BufferStorage.DataSizes[bufferID], size * m_BufferStorage.DataSizes[bufferID], data));
}

void Quilt::BufferManager::BindBuffer(unsigned int bufferID)
{
    unsigned int type = GetBufferType(m_BufferStorage.Types[bufferID]);
    GLCall(glBindBuffer(type, m_BufferStorage.Handles[bufferID]));
}

unsigned int Quilt::BufferManager::GetBufferType(BufferType type)
{
    unsigned int bufferType = 0;

    switch (type)
    {
    case Quilt::BufferType::Vertex:
        bufferType = GL_ARRAY_BUFFER;
        break;

    case Quilt::BufferType::Index:
        bufferType = GL_ELEMENT_ARRAY_BUFFER;
        break;

    case Quilt::BufferType::Instance:
        bufferType = GL_ARRAY_BUFFER;
        break;

    case Quilt::BufferType::Storage:
        bufferType = GL_SHADER_STORAGE_BUFFER;
        break;
    
    default:
        LOG_FATAL("Undefined buffer type");
        break;
    }

    return bufferType;
}