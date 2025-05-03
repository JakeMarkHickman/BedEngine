#pragma once

#include <Math/Vector/Vector2.h>

namespace Bed
{
    struct SubTexture
    {
        SubTexture() : TextureSize(16.0f, 16.0f), UVTopLeft(0.0f, 0.0f), UVBottomRight(1.0f, 1.0f), FrameIndex(0) {};
        SubTexture(Bed::Vector2 textureSize, int frame = 0) : TextureSize(textureSize), UVTopLeft(0.0f, 0.0f), UVBottomRight(1.0f, 1.0f), FrameIndex(frame) {};

        Bed::Vector2 TextureSize;
        int FrameIndex;

        int LastFrame = 0;

        Bed::Vector2 UVTopLeft;
        Bed::Vector2 UVBottomRight;
    };
}