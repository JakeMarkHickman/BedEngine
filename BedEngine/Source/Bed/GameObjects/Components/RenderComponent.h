#pragma once

#include <Graphics/Texture.h>
#include <Bed/GameObjects/Mesh/Mesh.h>
#include <Bed/Core.h>

namespace Bed
{
    struct BED_API Render
    {
        Render(const std::string& meshPath);

        Bed::Mesh m_Mesh;
    };
}
