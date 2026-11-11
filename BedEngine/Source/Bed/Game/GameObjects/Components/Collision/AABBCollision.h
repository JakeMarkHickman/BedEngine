#pragma once

#include <Bed/Game/GameObjects/Physics/Collision/AABB.h>

#include <Vector/Vector3.h>

namespace Bed
{
    struct AABBCollision
    {
        AABBCollision(bool showExtent = false) : HalfExtent(0.5f, 0.5f, 0.5f), ShowExtent(showExtent), IsTrigger(false) {};
        AABBCollision(float halfExtent, bool showExtent = false) : HalfExtent(halfExtent), ShowExtent(showExtent) {};
        AABBCollision(float x, float y, float z, bool showExtent = false) : HalfExtent(x, y, z), ShowExtent(showExtent) {};
        AABBCollision(Pillow::Vector3f halfExtent, bool showExtent = false) : HalfExtent(halfExtent), ShowExtent(showExtent) {};

        Pillow::Vector3f HalfExtent;
        bool IsTrigger;
        bool ShowExtent;

        uint64_t Handle;
    };
}