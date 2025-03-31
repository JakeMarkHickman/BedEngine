#pragma once

#include "AABB.h"

namespace Bed
{
    class Collision
    {
    public:
        static bool AABBOverlap(const Bed::AABB& a, const Bed::AABB& b);

    private:
    }; 
}