#pragma once

#include <Math/Transform.h>
#include <Bed/Game/World/GameObjects/Components/VelocityComponent.h>

namespace Bed
{
    void MoveSystem(Bed::ECS& ecs, float deltaTime)
    {
        for(uint64_t i = 0; ecs.GetAllEntities().size() > i; i++)
        {
            //TODO: Check Crashes when there is no entities with one of the components
            
            if(ecs.HasComponents<Bed::Transform, Bed::Velocity>(i))
            {
                Bed::Transform transform = ecs.GetComponent<Bed::Transform>(i);
                Bed::Velocity Vel = ecs.GetComponent<Bed::Velocity>(i);
                transform.Position += Vel.m_Velocity * deltaTime;
                ecs.SetComponent<>(i, transform);
            }
        }
    }
}