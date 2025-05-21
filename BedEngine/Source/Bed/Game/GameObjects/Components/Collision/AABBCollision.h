#pragma once

#include <Bed/Game/GameObjects/Physics/Collision/AABB.h>

namespace Bed
{
    struct AABBCollision
    {
        AABBCollision() : BoundingBox() {};
        AABBCollision(float min, float max) : BoundingBox(min, max) {};
        AABBCollision(Bed::Vector3 min, Bed::Vector3 max) : BoundingBox(min, max) {};

        AABB BoundingBox;
    };
}