#pragma once

#include <Bed/Math/Vector.h>
#include <Bed/Core.h>

namespace Bed
{
    struct BED_API Velocity
    {
        Velocity(Bed::Vector3 velocity);

        Bed::Vector3 m_Velocity {0.0f, 0.0f, 0.0f};
    };
}