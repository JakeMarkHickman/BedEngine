
#include "VertexArray.h"
#include <Graphics/OpenGL/OpenDebugger.h>
#include <cstdint>

Bed::VertexArray::VertexArray()
{
    glCreateVertexArrays(1, &m_RendererID);
    glBindVertexArray(m_RendererID);
}

Bed::VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_RendererID);
}

void Bed::VertexArray::AddBuffer(const Bed::VertexBuffer& vb, const Bed::VertexBufferLayout& layout)
{
    Bind();
    vb.Bind();
    const std::vector<VertexBufferLayoutElement> elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const Bed::VertexBufferLayoutElement element = elements[i];

        //TODO: Make this not be a cast
        glVertexAttribPointer(i, element.count, element.type, element.normalised, layout.GetStride(), reinterpret_cast<const void*>(uintptr_t(offset))); // This is what links the Array buffer to the Vertex Array
        glEnableVertexAttribArray(i);
        offset += element.count * Bed::VertexBufferLayoutElement::GetSizeOfType(element.type);
    }
}

void Bed::VertexArray::Bind() const
{
    glBindVertexArray(m_RendererID);
}

void Bed::VertexArray::Unbind() const
{
    glBindVertexArray(0);
}