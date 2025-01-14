#pragma once

#include <Math/Vector/Vector3.h>

namespace Bed
{
    struct DirectionalLight
    {
        DirectionalLight() : Colour(1.0f), Direction(0.0f, -1.0f, 0.0f) {};
        DirectionalLight(float lightColour, float lightDirection, float lightStrength) : Colour(lightColour), Direction(lightDirection), Strength(lightStrength) {}
        DirectionalLight(Bed::Vector3 lightColour, Bed::Vector3 lightDirection, float lightStrength) : Colour(lightColour), Direction(lightDirection), Strength(lightStrength) {}

        //TODO: Direction can be based on the rotation
        Bed::Vector3 Colour;
        Bed::Vector3 Direction;
        float Strength = 10;
    };
}
