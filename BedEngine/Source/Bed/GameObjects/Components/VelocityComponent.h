#pragma once

#include <Bed/Math/Vector.h>

namespace Bed
{
    struct Velocity
    {
        Velocity(Bed::Vector3 velocity) : m_Velocity(velocity) {};

        Bed::Vector3 m_Velocity;
    };
}