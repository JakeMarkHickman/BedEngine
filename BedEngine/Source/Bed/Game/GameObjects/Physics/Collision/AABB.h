#pragma once

#include <Vector/Vector3.h>

namespace Bed
{
    struct AABB
    {
        AABB() : Min(0.0f), Max(1.0f) {};
        AABB(float min, float max) : Min(min), Max(max) {};
        AABB(Pillow::Vector3f min, Pillow::Vector3f max) : Min(min), Max(max) {};

        Pillow::Vector3f Min;
        Pillow::Vector3f Max;
    };
}