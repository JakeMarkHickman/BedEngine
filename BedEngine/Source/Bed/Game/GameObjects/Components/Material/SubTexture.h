#pragma once

#include <Math/Vector/Vector2.h>

namespace Bed
{
    struct SubTexture
    {
        SubTexture() : TextureSize(16.0f, 16.0f), UVTopLeft(0.0f, 0.0f), UVBottomRight(1.0f, 1.0f), FrameIndex(0) {};
        SubTexture(Pillow::Vector2f textureSize, int frame = 0) : TextureSize(textureSize), UVTopLeft(0.0f, 0.0f), UVBottomRight(1.0f, 1.0f), FrameIndex(frame) {};

        Pillow::Vector2f TextureSize;
        int FrameIndex;

        int LastFrame = 0;

        Pillow::Vector2f UVTopLeft;
        Pillow::Vector2f UVBottomRight;
    };
}