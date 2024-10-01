#pragma once

#include <Bed/GameObjects/Components/2DRenderComponent.h>
#include <Bed/GameObjects/Components/TransformComponent.h>

namespace Bed
{
    void 2DRenderSystem(Bed::ECS& ecs, float deltaTime)
    {
        for(int i = 0; ecs.GetAllEntities().size() > i; i++)
        {
            //TODO: Change this as i should be used to check index of a value as
            if (ecs.HasComponents<Bed::TwoDimensionalRender>(i))
            {
                Bed::Transform transform;

                Bed::TwoDimensionalRender renderer = ecs.GetComponent<Bed::TwoDimensionalRender>(i);

                if(ecs.HasComponents<Bed::Transform>(i)) // Checks for a Transform for renderering
                {
                    transform = ecs.GetComponent<Bed::Transform>(i);
                }

                //TODO: Do rendering stuffs for components

                renderer.m_Texture->Bind();
            }
        }
    }
}