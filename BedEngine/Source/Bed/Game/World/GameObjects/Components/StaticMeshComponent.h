#pragma once

#include <Graphics/Texture.h>
//TODO: Shorten this with inclusion file
#include <Bed/Game/World/GameObjects/Mesh/Mesh.h>
#include <Bed/Core.h>

namespace Bed
{
    struct BED_API StaticMesh
    {
        StaticMesh(const std::string& meshPath) : m_Mesh(meshPath) {};

        Bed::Mesh m_Mesh;
    };
}
