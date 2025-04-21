#pragma once

#include <Math/Colour/Colour3.h>

namespace Bed
{
    struct AmbientLight
    {
        AmbientLight() : Colour(Bed::Colour3(1.0f)), Strength(0.1f) {};
        AmbientLight(Bed::Colour3 ligthColour, float lightStrength) : Colour(lightStrength), Strength(lightStrength) {};

        Bed::Colour3 Colour;
        float Strength;
    };
}