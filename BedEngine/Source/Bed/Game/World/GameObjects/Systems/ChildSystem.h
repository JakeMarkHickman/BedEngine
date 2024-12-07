#pragma once

#include <Math/Transform.h>
#include <GameObjects/Components/ChildComponent.h>

namespace Bed
{
    void ChildSystem(Bed::ECS& ecs, float deltaTime)
    {
        for(uint64_t i = 0; ecs.GetAllEntities().size() > i; i++)
        {
            if(ecs.HasComponents<Bed::Child>(i))
            {
                Bed::Child child = ecs.GetComponent<Bed::Child>(i);

                if(ecs.HasComponents<Bed::Transform>(child.Parent))
                {
                    Bed::Transform parentTransform = ecs.GetComponent<Bed::Transform>(child.Parent);

                    if(!ecs.HasComponents<Bed::Transform>(i))
                    {
                        ecs.AttachComponents(i, Bed::Transform(0.0f));
                    }

                    //TODO : Use parents Transform to calculate the childs transform
                    
                }
            }
        }
    }
}