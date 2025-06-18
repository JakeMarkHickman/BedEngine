#pragma once

#include <Vector/Vector3.h>
#include <vector>

namespace Mattress
{
    struct PhysicsObject
    {
        Pillow::Vector3f Position;
        Pillow::Vector3f Velocity;
        Pillow::Vector3f Force;

        float Mass = 1.0f;

        float InverseMass()
        {
            return 1.0f / Mass;
        }

        void AddForce(Pillow::Vector3f force)
        {
            Force += force;
        }

        std::vector<Pillow::Vector3f> Positions;
        std::vector<Pillow::Vector3f> Velocities;
        std::vector<Pillow::Vector3f> Forces;

        std::vector<float> Masses;
    };
}
