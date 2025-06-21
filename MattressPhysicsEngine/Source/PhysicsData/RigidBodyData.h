#pragma once

#include <vector>

#include <Vector/Vector3.h>

namespace Mattress
{
    struct RigidBodyData
    {
        std::vector<Pillow::Vector3f> Positions;
        std::vector<float> Masses;
        std::vector<Pillow::Vector3f> Velocities;

        //Forces can be moved out of here as it may not be used for movement
        std::vector<Pillow::Vector3f> Forces;
    };
}