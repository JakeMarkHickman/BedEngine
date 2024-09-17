#pragma once

#include "EntityComponent.h"
#include <Bed/Math/Vector.h>

namespace Bed
{
    struct Transform : public EntityComponent
    {
        Transform(Bed::Vector3 position, Bed::Vector3 rotation, Bed::Vector3 scale) : Position(position), Rotation(rotation), Scale(scale) {};

        Bed::Vector3 Position;
        Bed::Vector3 Rotation;
        Bed::Vector3 Scale;
    };
}