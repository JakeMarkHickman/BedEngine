#pragma once

#include <Vector/Vector3.h>

namespace Mattress
{
    struct AABB
    {
        Pillow::Vector3f Min;
        Pillow::Vector3f Max;
    };
}