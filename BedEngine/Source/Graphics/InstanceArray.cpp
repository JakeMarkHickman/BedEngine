#include "InstanceArray.h"
#include <cstdint>
#include <string>
#include "OpenGL/OpenDebugger.h"


#include <glm.hpp>

Bed::InstanceArray::InstanceArray()
{
    GLCall(glGenVertexArrays(1, &m_RendererID));
    GLCall(glBindVertexArray(m_RendererID));
}

Bed::InstanceArray::~InstanceArray()
{
    GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void Bed::InstanceArray::AddBuffer(const Bed::InstanceBuffer* ivb, const Bed::VertexBufferLayout& layout, unsigned int baseIndex)
{
    if(ivb != nullptr)
    {
        ivb->Bind();
    }

    const std::vector<VertexBufferLayoutElement> elements = layout.GetElements();
    unsigned int offset = 0;

    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const Bed::VertexBufferLayoutElement element = elements[i];

        GLCall(glEnableVertexAttribArray(baseIndex + i));
        GLCall(glVertexAttribPointer(
            baseIndex + i,
            element.count,
            element.type,
            element.normalised,
            layout.GetStride(),
            reinterpret_cast<const void*>(static_cast<uintptr_t>(element.Offset))
        ));

        GLCall(glVertexAttribDivisor(baseIndex + i, 1));

        offset += element.count + baseIndex * Bed::VertexBufferLayoutElement::GetSizeOfType(element.type);
    }
}

void Bed::InstanceArray::Bind() const
{
    GLCall(glBindVertexArray(m_RendererID));
}

void Bed::InstanceArray::Unbind() const
{
    GLCall(glBindVertexArray(0));
}