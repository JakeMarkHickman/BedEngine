#pragma once

#include <Math/Vector/Vector3.h>

namespace Bed
{
    struct Velocity
    {
        Velocity() : Direction(0.0f), Speed(0.0f) {};
        Velocity(Bed::Vector3 direction, float speed) : Direction(direction), Speed(speed) {};

        Bed::Vector3 Direction;
        float Speed;
    };
}