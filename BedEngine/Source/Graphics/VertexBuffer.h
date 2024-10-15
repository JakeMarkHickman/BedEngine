#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Bed
{
    class VertexBuffer
    {
    public:
        VertexBuffer(unsigned int size);
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;

        void PopulateBuffer(const void* verts, unsigned int size, unsigned int offset);

    private:
        unsigned int m_RendererID;
    };
}