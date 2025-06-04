#pragma once

#include <Vector/Vector3.h>

namespace Mattress
{
    struct PhysicsObject
    {
        Pillow::Vector3f Position;
        Pillow::Vector3f Velocity;
        Pillow::Vector3f Force;

        float Mass;

        float InverseMass()
        {
            return 1.0f / Mass;
        }

        void AddForce(Pillow::Vector3f force)
        {
            Force += force;
        }
    };
}
