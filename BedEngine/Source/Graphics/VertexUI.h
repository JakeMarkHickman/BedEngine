#pragma once

#include <Math/Vector.h>

namespace Bed
{
    struct VertexUI
    {
        VertexUI() {};

        Bed::Vector2 m_Position;
        Bed::Vector4 m_Colour;
        Bed::Vector2 m_TexCoords;
        float m_TexID;

        bool operator==(const VertexUI& other) const {
            return m_Position == other.m_Position &&
                   m_Colour == other.m_Colour &&
                   m_TexCoords == other.m_TexCoords &&
                   m_TexID == other.m_TexID;
        }
    };
}