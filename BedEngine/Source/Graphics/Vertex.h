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

        bool operator==(const Vertex& other) const {
            return m_Position == other.m_Position &&
                   m_Colour == other.m_Colour &&
                   m_TexCoords == other.m_TexCoords &&
                   m_TexID == other.m_TexID;
        }
    }; 
}