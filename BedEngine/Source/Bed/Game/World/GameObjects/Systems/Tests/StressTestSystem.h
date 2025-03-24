#pragma once

#include <Math/Transform.h>

namespace Bed
{
    void StressTestSystem(ECS& ecs)
    {
        for(int i = 0; i < ecs.GetAllEntities().size() > i; i++)
        {
            Bed::Transform* transform = ecs.GetComponent<Bed::Transform>(i);

            transform->Position += 5.0f;
        }
    }
}