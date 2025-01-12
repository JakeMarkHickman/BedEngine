#pragma once

#include <Math/Vector/Vector3.h>

namespace Bed
{
    struct SpotLight
    {
        SpotLight() : Colour(1.0f) {};

        //TODO: Direction will be based on the rotation
        Bed::Vector3 Colour;
        float Strength;
        float CutOff;
        float OuterCutOff;
        float Radius;
    }
}