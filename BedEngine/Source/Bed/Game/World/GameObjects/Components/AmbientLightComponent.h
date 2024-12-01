#pragma once

#include <Math/Vector/Vector3.h>
#include <Bed/Core.h>

namespace Bed
{
    struct BED_API AmbientLight
    {
        AmbientLight(float strength, Bed::Vector3 colour) : Strength(strength), Colour(colour) {};

        float Strength = 0.1f;
        Bed::Vector3 Colour;
    };
}