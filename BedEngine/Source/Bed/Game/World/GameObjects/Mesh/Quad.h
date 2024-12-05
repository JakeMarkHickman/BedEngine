#pragma once

#include <Graphics/Vertex.h>
#include <Math/Vector.h>
#include <array>

namespace Bed
{
    static std::array<Bed::Vertex, 4> CreateQuad(Bed::Vector2 position, Bed::Vector4 colour, Bed::Vector2 size, float textureID)
    {

        Bed::Vertex v0;
        v0.m_Position = { position.x - (size.x/2), position.y + (size.y/2), 0.0f};
        v0.m_Normal = { 0.0f, 0.0f, 0.0f };
        v0.m_Colour = { colour };
        v0.m_TexCoords = { 0.0f,  1.0f };
        v0.m_TexID = textureID;

        Bed::Vertex v1;
        v1.m_Position = { position.x + (size.x/2), position.y + (size.y/2), 0.0f};
        v1.m_Normal = { 0.0f, 0.0f, 0.0f };
        v1.m_Colour = { colour };
        v1.m_TexCoords = { 1.0f,  1.0f };
        v1.m_TexID = textureID;

        Bed::Vertex v2;
        v2.m_Position = { position.x - (size.x/2), position.y - (size.y/2), 0.0f};
        v2.m_Normal = { 0.0f, 0.0f, 0.0f };
        v2.m_Colour = { colour };
        v2.m_TexCoords = { 0.0f,  0.0f };
        v2.m_TexID = textureID;

        Bed::Vertex v3;
        v3.m_Position = { position.x + (size.x/2), position.y - (size.y/2), 0.0f};
        v3.m_Normal = { 0.0f, 0.0f, 0.0f };
        v3.m_Colour = { colour };
        v3.m_TexCoords = { 1.0f,  0.0f };
        v3.m_TexID = textureID;


        return { v0, v1, v2, v3 };
    }
}