#pragma once

#include "AABB.h"

namespace Mattress
{
    class CollisionChecks
    {
    public:
        static bool AABBOverlap(Mattress::AABB& a, Mattress::AABB& b);
    }
}