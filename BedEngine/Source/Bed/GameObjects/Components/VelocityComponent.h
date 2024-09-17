#pragma once

#include "EntityComponent.h"
#include <Bed/Math/Vector.h>

namespace Bed
{
    struct Velocity : public EntityComponent
    {
        Velocity(Bed::Vector3 velocity) : Velocity(velocity) {};

        Bed::Vector3 Velocity;
    }
}