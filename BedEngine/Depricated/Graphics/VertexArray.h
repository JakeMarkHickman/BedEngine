#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Vertex.h"

namespace Bed
{
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        void AddBuffer(const Bed::VertexBuffer* vb, const Bed::VertexBufferLayout& layout);

        void PopulateBuffer(const void* verts, unsigned int offset);

        void Bind() const;
        void Unbind() const;

    private:
        unsigned int m_RendererID;
    };
}