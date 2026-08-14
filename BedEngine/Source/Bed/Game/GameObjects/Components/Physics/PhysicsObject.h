#pragma once

namespace Bed
{
    struct PhysicsObject
    {
        PhysicsObject() {};

        uint64_t Handle;

        float Mass = 10.0f;
    };
}