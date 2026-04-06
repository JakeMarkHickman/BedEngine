#pragma once

#include "VertexBufferLayout.h"

#include <vector>
#include <unordered_map>

namespace std
{
    template<>
    struct hash<Quilt::VertexBufferLayout>
    {
        size_t operator()(const Quilt::VertexBufferLayout& data) const noexcept
        {
            return data.GetHash();
        }
    };
}

namespace Quilt
{
    class VertexArrayManager
    {
    public:
        unsigned int CreateVertexArray(const Quilt::VertexBufferLayout& layout);
        unsigned int GetVertexArray(const Quilt::VertexBufferLayout& layout);
        bool IsVertexArray(const Quilt::VertexBufferLayout& layout);

        void AddBuffer(unsigned int vertexArrayID, const Quilt::VertexBufferLayout& layout);
        void Bind(unsigned int vertexArrayID);
        void Unbind();

    private:
        unsigned int m_NextArrayHandle = 0;
        std::unordered_map<Quilt::VertexBufferLayout, unsigned int> m_VertexHandles;
        std::vector<unsigned int> m_VertexArrayHandles;
    };
}