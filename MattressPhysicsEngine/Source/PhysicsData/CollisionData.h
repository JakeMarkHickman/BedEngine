#pragma once

#include <vector>
#include <Vector/Vector3.h>

namespace Mattress
{
    enum CollisionType
    {
        Box = 0,
        Sphere = 1
    };

    struct AABBCollisionData
    {
        std::vector<Pillow::Vector3f> HalfExents;
        std::vector<uint64_t> BodyHandles;
    };

    struct ContactData
    {
        uint64_t BodyA;
        uint64_t BodyB;

        Pillow::Vector3f Normal;

        float Penetration;
    };
}