#pragma once

#include <Math/Vector.h>
#include <Bed/Core.h>

namespace Bed
{
    struct BED_API Velocity
    {
        Velocity(Bed::Vector3 velocity) : m_Velocity(velocity) {};

        Bed::Vector3 m_Velocity;
    };
}