#include "MemoryPool.h"

Bed::MemoryPool::MemoryPool(size_t chunkSize, size_t chunkCount) : m_ChunkSize(chunkSize), m_ChunkCount(chunkCount)
{
    // Ensures that each memory chunk can store an object with correct alignments
    m_ChunkSize = (chunkSize + alignof(std::max_align_t) - 1) & ~(alignof(std::max_align_t) - 1);

    // Allocate a memory block
    m_Memory = ::operator new(m_ChunkSize * m_ChunkCount);

    // Initialise Free Chunk List
    FreeChunkListInit();
}

Bed::MemoryPool::~MemoryPool()
{
    m_Memory = nullptr;
}

void Bed::MemoryPool::FreeChunkListInit()
{
    m_FreeChunkList = m_Memory;

    char* current = static_cast<char*>(m_Memory);

    for (size_t i = 0; i < m_ChunkCount - 1; i++)
    {
        *reinterpret_cast<void**>(current) = current + m_ChunkSize; // chunk stores data of next chunk in list
        current += m_ChunkSize;
    }

    *reinterpret_cast<void**>(current) = nullptr; // Set last pointer to null to mark end of list
}

void* Bed::MemoryPool::Allocate()
{
    if(!m_FreeChunkList) // If there are no free chunks
    {
        throw std::bad_alloc();
    }

    void* chunk = m_FreeChunkList;

    m_FreeChunkList = *reinterpret_cast<void**>(m_FreeChunkList);

    return chunk;
}

void Bed::MemoryPool::Deallocate(void* chunk)
{
    *reinterpret_cast<void**>(chunk) = m_FreeChunkList;
    m_FreeChunkList = chunk;
}