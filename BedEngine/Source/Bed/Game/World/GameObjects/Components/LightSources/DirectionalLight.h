#pragma once

#include <Math/Vector/Vector3.h>

namespace Bed
{
    struct DirectionalLight
    {
        DirectionalLight() : Colour(1.0f), Direction(1.0f) {};

        Bed::Vector3 Colour;
        Bed::Vector3 Direction;
        float Strength = 10;
    }
}
