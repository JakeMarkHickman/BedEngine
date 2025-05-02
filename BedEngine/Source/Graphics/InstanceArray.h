#pragma once

#include "VertexBufferLayout.h"
#include "Vertex.h"
#include "InstanceBuffer.h"

namespace Bed
{
    class InstanceArray
    {
    public:
        InstanceArray();
        ~InstanceArray();

        void AddBuffer(const Bed::InstanceBuffer* ivb, const Bed::VertexBufferLayout& layout, unsigned int baseIndex);

        void PopulateBuffer(const void* verts, unsigned int offset);

        void Bind() const;
        void Unbind() const;

    private:
        unsigned int m_RendererID;
    };
}