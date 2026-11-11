#pragma once

#include "../PhysicsData/CollisionData.h"
#include <SleepTrace.h>

namespace Mattress
{
    class CollisionChecks
    {
    public:
        static bool AABBOverlap(const Pillow::Vector3f& bodyPositionA, const Pillow::Vector3f& halfExtentA, const Pillow::Vector3f& bodyPositionB, const Pillow::Vector3f& halfExtentB, Mattress::ContactData& outContact);
    };
}