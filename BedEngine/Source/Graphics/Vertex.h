#pragma once

#include <Math/Vector.h>

namespace Bed
{
    struct Vertex
    {
        Vertex() {};

        Pillow::Vector3f m_Position;
        Pillow::Vector3f m_Normal;
        Bed::Vector4 m_Colour;
        Pillow::Vector2f m_TexCoords;
        float m_TexID;

        bool operator==(const Vertex& other) const {
            return m_Position == other.m_Position &&
                   m_Normal == other.m_Normal &&
                   m_Colour == other.m_Colour &&
                   m_TexCoords == other.m_TexCoords &&
                   m_TexID == other.m_TexID;
        }
    };
}