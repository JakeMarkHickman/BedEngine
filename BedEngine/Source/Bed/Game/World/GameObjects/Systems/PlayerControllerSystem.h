#pragma once

#include <Bed/Game/World/GameObjects/Components/PlayerController.h>
#include <Bed/Input/Input.h>

namespace Bed
{
    void MoveForward(Bed::InputData data)
    {
        
    };

    void PlayerControllerSystem(Bed::ECS& ecs, float deltaTime)
    {
        for(int i = 0; ecs.GetAllEntities().size() > i; i++)
        {
            if(ecs.HasComponents<Bed::PlayerController>(i))
            {

            }
        }
    };
}