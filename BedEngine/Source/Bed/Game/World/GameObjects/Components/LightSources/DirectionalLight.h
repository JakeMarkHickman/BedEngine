#pragma once

#include <Math/Vector/Vector3.h>

namespace Bed
{
    struct DirectionalLight
    {
        DirectionalLight() {};

        Bed::Vector3 Colour;
        float Strength = 10;
    }
}
