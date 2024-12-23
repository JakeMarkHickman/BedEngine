#pragma once

#include <Bed/Game/World/GameObjects/Mesh/Mesh.h>

namespace Bed
{
    struct StaticMesh
    {
        StaticMesh(std::string Path) : Mesh(Path) {};

        Bed::Mesh Mesh;
    };
}