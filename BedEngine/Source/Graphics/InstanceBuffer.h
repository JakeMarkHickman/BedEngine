#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Bed
{
    class InstanceBuffer
    {
    public:
        InstanceBuffer(unsigned int maxInstances, unsigned int dataSize);
        ~InstanceBuffer();

        void Bind() const;
        void Unbind() const;

        void PopulateBuffer(const void* data, unsigned int count);

        unsigned int GetInstanceCount() const { return m_MaxInstanced; };

    private:
        unsigned int m_RendererID;

        unsigned int m_MaxInstanced;
        unsigned int m_DataSize;
    };
}