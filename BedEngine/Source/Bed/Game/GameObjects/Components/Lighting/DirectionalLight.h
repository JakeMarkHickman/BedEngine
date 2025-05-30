#pragma once

#include <Math/Vector/Vector3.h>
#include <Math/Colour/Colour3.h>

namespace Bed
{
    struct DirectionalLight
    {
        DirectionalLight() : Colour(1.0f), Direction(0.0f, -1.0f, 0.0f) {};
        DirectionalLight(float lightColour, float lightDirection, float lightStrength) : Colour(lightColour), Direction(lightDirection), Strength(lightStrength) {}
        DirectionalLight(Bed::Colour3 lightColour, Pillow::Vector3f lightDirection, float lightStrength) : Colour(lightColour), Direction(lightDirection), Strength(lightStrength) {}

        //TODO: Direction can be based on the rotation
        Bed::Colour3 Colour;
        Pillow::Vector3f Direction;
        float Strength = 10;
    };
}
