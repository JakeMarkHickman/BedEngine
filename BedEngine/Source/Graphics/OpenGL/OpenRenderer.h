#pragma once

#include <Graphics/VertexArray.h>
#include <Graphics/IndexBuffer.h>
#include <Graphics/Shader.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Bed
{
    class OpenRenderer
    {
    public:
        static void Draw(const VertexArray* va, const IndexBuffer* ib, const Shader* shader);
        static void Clear();
    };
}