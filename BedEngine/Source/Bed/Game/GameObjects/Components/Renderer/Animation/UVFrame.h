#pragma once

#include <string>
#include <Vector/Vector2.h>

namespace Bed
{
    struct UVFrame
    {
        UVFrame(std::string texturePath, Pillow::Vector2f uvMin, Pillow::Vector2f uvMax) : TexturePath(texturePath), UVMin(uvMin), UVMax(uvMax) {};

        std::string TexturePath;
        Pillow::Vector2f UVMin;
        Pillow::Vector2f UVMax;
    };
}