#pragma once

#include <Math/Vector/Vector3.h>

namespace Bed
{
    struct AmbientLight
    {
        AmbientLight() : Colour(Bed::Vector3(1.0f)), Strength(0.1f) {};
        AmbientLight(Bed::Vector3 ligthColour, float lightStrength) : Colour(lightStrength), Strength(lightStrength) {};

        Bed::Vector3 Colour;
        float Strength;
    };
}