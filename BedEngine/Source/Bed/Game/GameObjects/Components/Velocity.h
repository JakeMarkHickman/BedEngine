#pragma once

#include <Math/Vector/Vector3.h>

namespace Bed
{
    struct Velocity
    {
        Velocity() : Direction(0.0f), Speed(0.0f) {};
        Velocity(Pillow::Vector3f direction, float speed) : Direction(direction), Speed(speed) {};

        Pillow::Vector3f Direction;
        float Speed;
    };
}