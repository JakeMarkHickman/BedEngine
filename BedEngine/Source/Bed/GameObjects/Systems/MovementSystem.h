#pragma once

#include <Bed/GameObjects/Components/TransformComponent.h>
#include <Bed/GameObjects/Components/VelocityComponent.h>

namespace Bed
{
    void MoveSystem(Bed::ECS& ecs, float deltaTime)
    {
        for(uint64_t i = 0; ecs.GetAllEntities().size() > i; i++)
        {
            std::cout << "Entity: " << i << " Checked" << std::endl;

            //TODO: Check Crashes when there is no entities with one of the components
            
            if(ecs.HasComponents<Bed::Transform, Bed::Velocity>(i))
            {
                std::cout << "~~~~ Entity: " << i << " Has Transform and Velocity! ~~~~" << std::endl;
                Bed::Transform Trans = ecs.GetComponent<Bed::Transform>(i);
                Bed::Velocity Vel = ecs.GetComponent<Bed::Velocity>(i);

                Trans.m_Position = Bed::Vector3(Trans.m_Position.x + Vel.m_Velocity.x, Trans.m_Position.y + Vel.m_Velocity.y, Trans.m_Position.z + Vel.m_Velocity.z);

                ecs.SetComponent<>(i, Trans);

                std::cout << "~~~~ Entity: " << i << " position is: x: " << Trans.m_Position.x << " y: " << Trans.m_Position.y << " z: " << Trans.m_Position.z << std::endl; 
            }
        }
    }
}