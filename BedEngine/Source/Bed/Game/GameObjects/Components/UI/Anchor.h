#pragma once

#include <Math/Vector/Vector2.h>

namespace Bed
{
    struct Anchor
    {
        Anchor() : Position(0.0f) {};
        Anchor(float value) : Position(value) {};
        Anchor(Pillow::Vector2f value) : Position(value) {};

        Pillow::Vector2f Position;
    };
}