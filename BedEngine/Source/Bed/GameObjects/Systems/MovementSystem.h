#pragma once

#include <Bed/GameObjects/Components/TransformComponent.h>
#include <Bed/GameObjects/Components/VelocityComponent.h>

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

                transform.m_Position += Vel.m_Velocity * deltaTime;

                ecs.SetComponent<>(i, transform);

                std::cout << "~~~~ Entity: " << i << " position is: x: " << transform.m_Position.x << " y: " << transform.m_Position.y << " z: " << transform.m_Position.z << std::endl; 
            }
        }
    }
}