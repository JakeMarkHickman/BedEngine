#pragma once

#include <Bed/Game/GameObjects/Physics/Collision/AABB.h>

namespace Bed
{
    struct AABBCollision
    {
        AABBCollision() : BoundingBox() {};
        AABBCollision(float min, float max) : BoundingBox(min, max) {};
        AABBCollision(Pillow::Vector3f min, Pillow::Vector3f max) : BoundingBox(min, max) {};

        AABB BoundingBox;
    };
}