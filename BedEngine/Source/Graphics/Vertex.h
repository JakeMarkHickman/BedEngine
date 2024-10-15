#pragma once

#include <Bed/Math/Vector.h>

namespace Bed
{
    struct Vertex
    {
        Vertex() {};

        Bed::Vector3 m_Position = Bed::Vector3(0.0f, 0.0f, 0.0f);
        Bed::Vector4 m_Colour = Bed::Vector4(0.0f, 0.0f, 0.0f, 0.0f);
        Bed::Vector2 m_TexCoords = Bed::Vector2(0.0f, 0.0f);
        float m_TexID;
    }; 
}