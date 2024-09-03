#pragma once

#include "Vector.h"

namespace Bed
{
    struct Transform
    {
        Bed::Vector3 Position;
        Bed::Vector3 Rotation;
        Bed::Vector3 Scale;
    };
}