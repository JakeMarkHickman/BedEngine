#pragma once

#include <Math/Vector/Vector2.h>

namespace Bed
{
    struct Anchor
    {
        Anchor() : Position(0.0f) {};
        Anchor(float value) : Position(value) {};
        Anchor(Bed::Vector2 value) : Position(value) {};

        Bed::Vector2 Position;
    };
}