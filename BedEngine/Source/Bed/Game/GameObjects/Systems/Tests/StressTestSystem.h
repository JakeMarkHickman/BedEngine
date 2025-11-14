#pragma once

namespace Bed
{
    void StressTestSystem(Bed::World& world)
    {
        for(uint64_t i : world.GetAllEntities())
        {
            Bed::Transform* transform = world.GetComponent<Bed::Transform>(i);

            transform->Position += 5.0f;
        }
    }
}