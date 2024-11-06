#pragma once

#include <Graphics/Vertex.h>

namespace Bed
{
    struct MeshFace
    {
        Bed::Vertex m_Vertices[4];
        int m_Indices[4];
    };
}