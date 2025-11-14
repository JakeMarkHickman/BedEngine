#pragma once

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
}