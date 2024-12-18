#pragma once

#include <stdexcept>
#include <cstddef>

namespace Bed
{
    class MemoryPool
    {
    public:
        MemoryPool(size_t chunkSize, size_t chunkCount);
        ~MemoryPool();

        void* Allocate();
        void Deallocate(void* chunk);
    private:

        size_t m_ChunkSize;
        size_t m_ChunkCount;
        void* m_Memory;
        void* m_FreeChunkList;

        void FreeChunkListInit();
    };
}