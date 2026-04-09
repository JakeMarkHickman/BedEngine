#pragma once

#include <vector>

namespace Quilt
{
    struct CopyInfo
    {
        unsigned int ReadBuffer;
        unsigned int WriteBuffer;
        unsigned int ReadOffset;
        unsigned int WriteOffset;
        unsigned int Count;
    };

    enum class BufferType
    {
        Vertex,
        Index, 
        Instance,
        Storage
    };

    struct GPUBuffers
    {
        std::vector<Quilt::BufferType> Types;
        std::vector<unsigned int> DataSizes;
        std::vector<unsigned int> DataCounts;
        std::vector<unsigned int> OccipiedCounts;

        std::vector<int> BindingPoints;

        std::vector<unsigned int> Handles;
    };

    class BufferManager
    {
    public:
        unsigned int CreateBuffer(BufferType type, unsigned int dataSize, unsigned int dataCount, int bindingPoint = -1);

        void RemoveBuffer(unsigned int bufferID);
        void PopulateBuffer(unsigned int bufferID, const void* data, unsigned int size, unsigned int offset);
        void PopulateBuffer(unsigned int bufferID, const void* data, unsigned int size);
        void BindBuffer(unsigned int bufferID);

        unsigned int GetOccupiedCount(unsigned int bufferID);

        bool IsBufferEmpty(unsigned int bufferID);
        bool IsBufferFull(unsigned int bufferID);

        void CopyRegion(Quilt::CopyInfo copyInfo);
        void RemoveRegion(unsigned int bufferID, unsigned int count);
        

        GPUBuffers& GetBufferStorage() { return m_BufferStorage; };

    private:
        unsigned int AssignBuffer(BufferType type, unsigned int dataSize, unsigned int dataCount, int bindingPoint);
        unsigned int GetBufferType(BufferType type);

        GPUBuffers m_BufferStorage;
        unsigned int m_GPUBufferCount = 0;
        std::vector<unsigned int> m_RemovedBuffers;
    };
}