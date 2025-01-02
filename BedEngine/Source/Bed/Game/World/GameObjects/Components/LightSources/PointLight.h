#pragma once

#include <Math/Vector/Vector3.h>

namespace Bed
{
    struct PointLight
    {
        PointLight() : Colour(Bed::Vector3(1.0f)) {};

        Bed::Vector3 Colour;
        float Strength = 1;
        float Radius = 1;
    };
}