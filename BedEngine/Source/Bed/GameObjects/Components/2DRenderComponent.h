#pragma once

#include <Graphics/Texture.h>
#include <Graphics/Shader.h>
#include <Bed/Core.h>

namespace Bed
{
    struct BED_API TwoDimensionalRender
    {
        TwoDimensionalRender(Bed::Texture* texture, int zOrder);

        Bed::Texture* m_Texture;
        int m_ZOrder;
    };
}
