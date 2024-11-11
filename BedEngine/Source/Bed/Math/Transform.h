#pragma once

#include "Vector.h"

namespace Bed
{
    struct BED_API Transform
    {
        Transform() {};
        Transform(float value) : Position(value), Rotation(value), Scale(value) {};
        Transform(float position, float rotation, float scale) : Position(position), Rotation(rotation), Scale(scale) {};
        Transform(Bed::Vector3 value) : Position(value), Rotation(value), Scale(value) {};
        Transform(Bed::Vector3 position, Bed::Vector3 roataion, Bed::Vector scale) : Position(position), Rotation(rotation), Scale(scale) {};

        // TODO: change rotation to a quarternion
        Bed::Vector3 Position;
        Bed::Vector3 Rotation;
        Bed::Vector3 Scale;
    }
}