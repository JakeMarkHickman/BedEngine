#pragma once

#include <Math/Vector/Vector3.h>

namespace Bed
{
    struct Velocity
    {
        Velocity() : Direction(0.0f) {};
        Velocity(Bed::Vector3 direction) : Direction(direction) {};

        Bed::Vector3 Direction;
    };
}