#pragma once

#include <Math/Vector/Vector3.h>
#include <Math/Colour/Colour3.h>

namespace Bed
{
    struct SpotLight
    {
        SpotLight() : Colour(1.0f), Direction(Pillow::Vector3f(0.0f, -1.0f, 0.0f)){};
        SpotLight(Bed::Colour3 lightColour, Pillow::Vector3f lightDirection, float lightStrength, float lightCutOff, float lightOuterCutOff, float radius):
            Colour(lightColour), Direction(lightDirection), Strength(lightStrength), CutOff(lightCutOff), OuterCutOff(lightOuterCutOff), Radius(radius) {};
        SpotLight(float lightColour, float lightDirection, float lightStrength, float lightCutOff, float lightOuterCutOff, float radius):
            Colour(lightColour), Direction(lightDirection), Strength(lightStrength), CutOff(lightCutOff), OuterCutOff(lightOuterCutOff), Radius(radius) {};

        //TODO: Direction will be based on the rotation
        Bed::Colour3 Colour;
        Pillow::Vector3f Direction;
        float Strength = 1.0f;
        float CutOff = 1.0f;
        float OuterCutOff = 1.0f;
        float Radius = 1.0f;
    };
}