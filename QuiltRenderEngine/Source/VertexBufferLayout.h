#pragma once

#include <vector>
#include <SleepTrace.h>
#include "OpenGl/OpenDebugger.h"

namespace Quilt
{
    struct VertexBufferLayoutElement
    {
        unsigned int Type;
        unsigned int Count;
        unsigned char Normalised;
        unsigned int Offset;

        static unsigned int GetSizeOfType(unsigned int type)
        {
            switch (type)
            {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
            }
            return 0;
        }

        bool operator==(const VertexBufferLayoutElement& other) const
        {
            return Type == other.Type &&
            Count == other.Count &&
            Normalised == other.Normalised &&
            Offset == other.Offset;
        }

        const VertexBufferLayoutElement& operator=(const VertexBufferLayoutElement& other)
        {
            Type = other.Type;
            Count = other.Count;
            Normalised = other.Normalised;
            Offset = other.Offset;

            return *this;
        }
    };

    class VertexBufferLayout
    {
    public:
        VertexBufferLayout() : m_Stride(0) {};

        template<typename T>
        void Push(unsigned int count)
        {
            LOG_FATAL("Type is unsupported");
        }

        template<>
        void Push<float>(unsigned int count)
        {
            m_Elements.push_back({GL_FLOAT, count, GL_FALSE, m_Stride});
            m_Stride += count * Quilt::VertexBufferLayoutElement::GetSizeOfType(GL_FLOAT);
            RehashLayout();
        }

        template<>
        void Push<unsigned int>(unsigned int count)
        {
            m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE, m_Stride});
            m_Stride += count * Quilt::VertexBufferLayoutElement::GetSizeOfType(GL_UNSIGNED_INT);
            RehashLayout();
        }

        template<>
        void Push<unsigned char>(unsigned int count)
        {
            m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE, m_Stride});
            m_Stride += count * Quilt::VertexBufferLayoutElement::GetSizeOfType(GL_UNSIGNED_BYTE);
            RehashLayout();
        }

        size_t GetHash() const { return m_Hash; }
        inline const std::vector<VertexBufferLayoutElement> GetElements() const& { return m_Elements; }
        inline unsigned int GetStride() const { return m_Stride; }

        bool operator==(const VertexBufferLayout& other) const
        {
            return m_Stride == other.GetStride() &&
            m_Elements == other.GetElements();
        }

        const VertexBufferLayout& operator=(const VertexBufferLayout& other)
        {
            m_Stride = other.GetStride();
            m_Elements = other.GetElements();

            return *this;
        }

    private:
        void RehashLayout()
        {
            m_Hash = 0;
            for(const VertexBufferLayoutElement& e : m_Elements)
            {
                m_Hash ^= std::hash<unsigned int>()(e.Type) + 0x9e3779b9 + (m_Hash << 6) + (m_Hash >> 2);
                m_Hash ^= std::hash<unsigned int>()(e.Count) + 0x9e3779b9 + (m_Hash << 6) + (m_Hash >> 2);
                m_Hash ^= std::hash<unsigned char>()(e.Normalised) + 0x9e3779b9 + (m_Hash << 6) + (m_Hash >> 2);
                m_Hash ^= std::hash<unsigned int>()(e.Offset) + 0x9e3779b9 + (m_Hash << 6) + (m_Hash >> 2);
            }
        }

        std::vector<VertexBufferLayoutElement> m_Elements;
        unsigned int m_Stride;
        size_t m_Hash;
    };
}