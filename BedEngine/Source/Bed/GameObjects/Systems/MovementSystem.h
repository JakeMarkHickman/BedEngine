#pragma once

#include <Bed/GameObjects/Components/TransformComponent.h>
#include <Bed/GameObjects/Components/VelocityComponent.h>

namespace Bed
{
    void MoveSystem(Bed::ECS& ecs, float deltaTime)
    {
        for(uint64_t i = 0; ecs.GetAllEntities().size() > i; i++)
        {
            std::cout << "Here" << std::endl;

            //TODO: Check Crashes
            
            /*if(ecs.HasComponents<Bed::Transform, Bed::Velocity>(i))
            {
                
            }*/
        }
    }
}