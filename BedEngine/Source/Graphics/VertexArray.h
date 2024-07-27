#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"


namespace Bed
{
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        void AddBuffer(const Bed::VertexBuffer& vb, const Bed::VertexBufferLayout& layout);

        void Bind() const;
        void Unbind() const;

    private:
        unsigned int m_RendererID;
    };
}