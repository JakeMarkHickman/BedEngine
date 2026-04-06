#include "VertexArray.h"

unsigned int Quilt::VertexArrayManager::CreateVertexArray(const Quilt::VertexBufferLayout& layout)
{
    unsigned int createdArray;

    GLCall(glGenVertexArrays(1, &createdArray))
    GLCall(glBindVertexArray(createdArray));

    m_VertexHandles.emplace(layout, createdArray);

    m_NextArrayHandle++;

    AddBuffer(createdArray, layout);

    return createdArray;
}

unsigned int Quilt::VertexArrayManager::GetVertexArray(const Quilt::VertexBufferLayout& layout)
{
    return m_VertexHandles.at(layout);
}

bool Quilt::VertexArrayManager::IsVertexArray(const Quilt::VertexBufferLayout& layout)
{
    return m_VertexHandles.find(layout) != m_VertexHandles.end();
}

void Quilt::VertexArrayManager::AddBuffer(unsigned int vertexArrayID, const Quilt::VertexBufferLayout& layout)
{
    Bind(vertexArrayID);

    const std::vector<Quilt::VertexBufferLayoutElement> elements = layout.GetElements();
    unsigned int offset = 0;

    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const Quilt::VertexBufferLayoutElement element = elements[i];

        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(
            i,
            element.Count,
            element.Type,
            element.Normalised,
            layout.GetStride(),
            reinterpret_cast<const void*>(static_cast<uintptr_t>(offset))
        ));

        offset += element.Count * Quilt::VertexBufferLayoutElement::GetSizeOfType(element.Type);
    }
}

void Quilt::VertexArrayManager::Bind(unsigned int vertexArrayID)
{
    GLCall(glBindVertexArray(vertexArrayID));
}

void Quilt::VertexArrayManager::Unbind()
{
    GLCall(glBindVertexArray(0));
}