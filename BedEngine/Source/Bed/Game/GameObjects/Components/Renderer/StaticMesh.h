#pragma once

#include <Bed/Game/GameObjects/Mesh/Mesh.h>

namespace Bed
{
    struct StaticMesh
    {
        StaticMesh(std::string Path) : Mesh(Path) {};

        Bed::Mesh Mesh;
    };
}