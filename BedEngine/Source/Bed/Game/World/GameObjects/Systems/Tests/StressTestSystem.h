#pragma once

#include <Math/Transform.h>

namespace Bed
{
    void StressTestSystem(Bed::World& world)
    {
        for(int i = 0; i < world.GetAllEntities().size() > i; i++)
        {
            Bed::Transform* transform = world.GetComponent<Bed::Transform>(i);

            transform->Position += 5.0f;
        }
    }
}