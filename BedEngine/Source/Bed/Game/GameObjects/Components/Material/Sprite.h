#pragma once

#include <Math/Vector/Vector2.h>

namespace Bed
{
    struct Sprite
    {
        Sprite() : SpriteSize(16.0f, 16.0f), UVTopLeft(0.0f, 0.0f), UVBottomRight(1.0f, 1.0f), FrameIndex(0) {};
        Sprite(Bed::Vector2 spriteSize, int frame = 0) : SpriteSize(spriteSize), UVTopLeft(0.0f, 0.0f), UVBottomRight(1.0f, 1.0f), FrameIndex(frame) {};

        Bed::Vector2 SpriteSize;
        int FrameIndex;

        int LastFrame = 0;

        Bed::Vector2 UVTopLeft;
        Bed::Vector2 UVBottomRight;
    };
}