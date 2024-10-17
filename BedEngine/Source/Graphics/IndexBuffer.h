#pragma once

namespace Bed
{
    class IndexBuffer
    {  
    public:
        IndexBuffer(unsigned int size);
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;

        void PopulateBuffer(const void* indices, unsigned int size, unsigned int offset);

        inline unsigned int GetCount() const { return m_Count; };

    private:
        unsigned int m_RendererID;
        unsigned int m_Count;
    };
}

