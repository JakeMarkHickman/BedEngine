#pragma once

#include <Graphics/Vertex.h>
#include <Bed/Math/Vector.h>
#include <array>

namespace Bed
{
    static std::array<Bed::Vertex, 4> CreateQuad(Bed::Vector3 position, Bed::Vector4 colour, float size, float textureID)
    {
        float s = size/2;

        Bed::Vertex v0;
        v0.m_Position = { position.x - s, position.y + s, position.z};
        v0.m_Colour = { colour };
        v0.m_TexCoords = { 0.0f,  1.0f };
        v0.m_TexID = textureID;

        Bed::Vertex v1;
        v1.m_Position = { position.x + s, position.y + s, position.z};
        v1.m_Colour = { colour };
        v1.m_TexCoords = { 1.0f,  1.0f };
        v1.m_TexID = textureID;

        Bed::Vertex v2;
        v2.m_Position = { position.x - s, position.y - s, position.z};
        v2.m_Colour = { colour };
        v2.m_TexCoords = { 0.0f,  0.0f };
        v2.m_TexID = textureID;

        Bed::Vertex v3;
        v3.m_Position = { position.x + s, position.y - s, position.z};
        v3.m_Colour = { colour };
        v3.m_TexCoords = { 1.0f,  0.0f };
        v3.m_TexID = textureID;


        return { v0, v1, v2, v3 };

    }
}