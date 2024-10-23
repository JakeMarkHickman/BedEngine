
#include "VertexArray.h"
#include <cstdint>
#include "OpenGL/OpenDebugger.h"

Bed::VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_RendererID));
    GLCall(glBindVertexArray(m_RendererID));
}

Bed::VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void Bed::VertexArray::AddBuffer(const Bed::VertexBuffer* vb, const Bed::VertexBufferLayout& layout)
{
    Bind();
    vb->Bind();
    const std::vector<VertexBufferLayoutElement> elements = layout.GetElements();
    unsigned int offset = 0;


    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const Bed::VertexBufferLayoutElement element = elements[i];

        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(
            i,
            element.count,
            element.type,
            element.normalised,
            layout.GetStride(),
            reinterpret_cast<const void*>(static_cast<uintptr_t>(offset))
        ));

        offset += element.count * Bed::VertexBufferLayoutElement::GetSizeOfType(element.type);
    }
}

void Bed::VertexArray::Bind() const
{
    GLCall(glBindVertexArray(m_RendererID));
}

void Bed::VertexArray::Unbind() const
{
    GLCall(glBindVertexArray(0));
}