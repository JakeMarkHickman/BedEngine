#pragma once

#include <Components/LightSources/DirectionalLight.h>

namespace Bed
{
    void DirectionalLightSystem(Bed::ECS& ecs, float deltaTime)
    {
        for(int i = 0; ecs.GetAllEntities().size() > i; i++)
        {
            if(ecs.HasComponents<Bed::DirectionalLight>(i))
            {
                std::cout << i << " has Directional Light comp" << "\n";
            }
        }
    }
}