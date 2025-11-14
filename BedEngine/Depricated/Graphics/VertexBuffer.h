#pragma once

#include <Bed/Core.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Bed
{
    class BED_API VertexBuffer
    {
    public:
        VertexBuffer(unsigned int size);
        VertexBuffer(const void* data, unsigned int size);
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;

        void PopulateBuffer(const void* verts, unsigned int size, unsigned int offset);

    private:
        unsigned int m_RendererID;
    };
}