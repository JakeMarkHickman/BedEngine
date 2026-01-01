#pragma once

#include <vector>

namespace Quilt
{
    enum class BufferType
    {
        Vertex,
        Index, 
        Instance,
        Storage
    };

    struct GPUBuffer
    {
        BufferType Type;
        unsigned int DataSize;
        unsigned int DataCount;

        unsigned int Handle = 0; //This allows for storage of (Vulkans, OpenGL(GLInt), Metal and DirectX data)
    };

    struct GPUBuffers
    {
        std::vector<Quilt::BufferType> Types;
        std::vector<unsigned int> DataSizes;
        std::vector<unsigned int> DataCounts;

        std::vector<unsigned int> Handles;
    };

    class BufferManager
    {
    public:
        unsigned int CreateBuffer(BufferType type, unsigned int dataSize, unsigned int dataCount);
        void RemoveBuffer(unsigned int bufferID);
        void PopulateBuffer(unsigned int bufferID, const void* data, unsigned int size, unsigned int offset);
        void BindBuffer(unsigned int bufferID);
        

        GPUBuffers& GetBufferStorage() { return m_BufferStorage; };

    private:
        unsigned int GetBufferType(BufferType type);

        GPUBuffers m_BufferStorage;
        unsigned int m_GPUBufferCount = 0;
        std::vector<unsigned int> m_UnusedBuffers;
    };
}