#include "GPUBuffer.h"
#include "OpenGl/OpenDebugger.h"

unsigned int Quilt::BufferManager::CreateBuffer(BufferType type, unsigned int dataSize, unsigned int dataCount)
{
    uint32_t buffer = m_GPUBufferCount;
    m_GPUBufferCount++;

    m_BufferStorage.Types.resize(m_GPUBufferCount);
    m_BufferStorage.DataSizes.resize(m_GPUBufferCount);
    m_BufferStorage.DataCounts.resize(m_GPUBufferCount);
    m_BufferStorage.Handles.resize(m_GPUBufferCount);

    m_BufferStorage.Types[buffer] = type;
    m_BufferStorage.DataSizes[buffer] = dataSize;
    m_BufferStorage.DataCounts[buffer] = dataCount;

    unsigned int bufferType = GetBufferType(type);

    GLCall(glGenBuffers(1, &m_BufferStorage.Handles[buffer]));
    GLCall(glBindBuffer(bufferType, m_BufferStorage.Handles[buffer]));
    
    GLCall(glBufferData(bufferType, m_BufferStorage.DataSizes[buffer] * m_BufferStorage.DataCounts[buffer], nullptr, GL_DYNAMIC_DRAW)); //TODO: This needs to change later to support shader storage and instances

    return buffer;
}

void Quilt::BufferManager::RemoveBuffer(unsigned int bufferID)
{
    
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