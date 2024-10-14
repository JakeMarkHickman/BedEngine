
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

        glEnableVertexAttribArray(i);
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cerr << "Error enabling vertex attribute at index " << i << ": " << error << std::endl;
        }


        glVertexAttribPointer(
            i,
            element.count,
            element.type,
            element.normalised,
            layout.GetStride(),
            reinterpret_cast<const void*>(static_cast<uintptr_t>(offset))
        );
        error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cerr << "Error setting vertex attribute pointer at index " << i << ": " << error << std::endl;
        }

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