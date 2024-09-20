#pragma once

#include <Bed/Math/Vector.h>

namespace Bed
{
    struct Transform
    {
        Transform(Bed::Vector3 position, Bed::Vector3 rotation, Bed::Vector3 scale) : m_Position(position), m_Rotation(rotation), m_Scale(scale) {};

        Bed::Vector3 m_Position;
        Bed::Vector3 m_Rotation;
        Bed::Vector3 m_Scale;
    };
}