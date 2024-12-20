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
                Bed::Child* child = ecs.GetComponent<Bed::Child>(i);

                if(ecs.HasComponents<Bed::Transform>(child->Parent))
                {
                    Bed::Transform* parentTransform = ecs.GetComponent<Bed::Transform>(child->Parent);

                    if(!ecs.HasComponents<Bed::Transform>(i))
                    {
                        ecs.AttachComponents(i, Bed::Transform(0.0f));
                    }

                    Bed::Transform* transform = ecs.GetComponent<Bed::Transform>(i);

                    transform->Position = parentTransform->Position + transform->LocalPosition;
                    
                    //TODO: Rotation needs to rotate from parents local position
                    transform->Rotation = parentTransform->Rotation + transform->LocalRotation;
                    transform->Scale = parentTransform->Scale * transform->LocalScale;

                    std::cout << "Child x = " << transform->Position.x << " y = " << transform->Position.y << " z = " << transform->Position.z << "\n";
                    std::cout << "Parent x = " << parentTransform->Position.x << " y = " << parentTransform->Position.y << " z = " << parentTransform->Position.z << "\n";
                }
            }
        }
    }
}