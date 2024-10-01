#pragma once

#include <Graphics/Texture.h>
#include <Graphics/Shader.h>

namespace Bed
{
    struct TwoDimensionalRender
    {
        TwoDimensionalRender(Bed::Texture* texture, int zOrder) : m_Texture(texture), m_ZOrder(zOrder) {};

        Bed::Texture* m_Texture;
        int m_ZOrder;
    };
}
