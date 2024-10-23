#pragma once

#include <Bed/Math/Vector.h>
#include <Bed/Core.h>

namespace Bed
{
    struct BED_API Transform
    {
        Transform(Bed::Vector3 position, Bed::Vector3 rotation, Bed::Vector3 scale);

        Bed::Vector3 m_Position {0.0f, 0.0f, 0.0f};
        Bed::Vector3 m_Rotation {0.0f, 0.0f, 0.0f};
        Bed::Vector3 m_Scale {0.0f, 0.0f, 0.0f};
    };
}