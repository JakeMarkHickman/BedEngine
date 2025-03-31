#pragma once

#include <Math/Vector/Vector3.h>

namespace Bed
{
    struct AABB
    {
        AABB() : Min(0.0f), Max(1.0f) {};
        AABB(float min, float max) : Min(min), Max(max) {};
        AABB(Bed::Vector3 min, Bed::Vector3 max) : Min(min), Max(max) {};

        Bed::Vector3 Min;
        Bed::Vector3 Max;
    };
}