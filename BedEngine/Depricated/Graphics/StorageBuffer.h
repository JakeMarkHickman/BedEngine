#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Bed
{
    class StorageBuffer
    {
    public:
        StorageBuffer(unsigned int size);
        ~StorageBuffer();

        void Bind(unsigned int bindingPoint) const;
        void Unbind() const;

        void PopulateBuffer(const void* data, unsigned int size, unsigned int offset);

    private:
        unsigned int m_RendererID;
    };
}