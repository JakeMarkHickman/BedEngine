#pragma once

namespace Bed
{
    struct PhysicsObject
    {
        PhysicsObject() : Mass(10.0f) {};
        PhysicsObject(float mass) : Mass(mass) {};

        uint64_t Handle;

        float Mass;
    };
}