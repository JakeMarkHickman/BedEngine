#pragma once

#include <Math/Colour/Colour3.h>

namespace Bed
{
    struct Fog
    {
        Fog() : FogColour(1.0f, 1.0f, 1.0f) {};
        Fog(Bed::Colour3 fogColour, float near, float far) : FogColour(fogColour), FogNear(near), FogFar(far) {};

        Bed::Colour3 FogColour;
        float FogNear = 10.0f;
        float FogFar = 30.0f;
    };
}