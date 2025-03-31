#pragma once

#include <Math/Vector/Vector3.h>

namespace Bed
{
    struct PointLight
    {
        PointLight() : Colour(Bed::Vector3(1.0f)) {};
        PointLight(float lightColour, float lightStrength, float lightRadius) : Colour(lightColour), Strength(lightStrength), Radius(lightRadius) {};
        PointLight(Bed::Vector3 lightColour, float lightStrength, float lightRadius) : Colour(lightColour), Strength(lightStrength), Radius(lightRadius) {};

        Bed::Vector3 Colour;
        float Strength = 1.0f;
        float Radius = 10.0f;
    };
}