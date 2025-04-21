#pragma once

#include <Math/Vector/Vector3.h>
#include <Math/Colour/Colour3.h>

namespace Bed
{
    struct PointLight
    {
        PointLight() : Colour(Bed::Colour3(1.0f)) {};
        PointLight(float lightColour, float lightStrength, float lightRadius) : Colour(lightColour), Strength(lightStrength), Radius(lightRadius) {};
        PointLight(Bed::Colour3 lightColour, float lightStrength, float lightRadius) : Colour(lightColour), Strength(lightStrength), Radius(lightRadius) {};

        Bed::Colour3 Colour;
        float Strength = 1.0f;
        float Radius = 10.0f;
    };
}