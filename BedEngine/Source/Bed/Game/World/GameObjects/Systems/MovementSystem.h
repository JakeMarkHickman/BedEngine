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

            /*if(ecs.HasComponents<Bed::Transform, Bed::Velocity>(i))
            {
                Bed::Transform* transform = ecs.GetComponent<Bed::Transform>(i);

                if (!transform) {
                    std::cerr << "Transform component for entity " << i << " is null.\n";
                    continue;
                }

                std::cout << "Position for entity: " << i << " is x: " << transform->Position.x << " y: " << transform->Position.y << " z: " << transform->Position.z << "\n";
                std::cout << "Rotation for entity: " << i << " is x: " << transform->Rotation.x << " y: " << transform->Rotation.y << " z: " << transform->Rotation.z << "\n";
                std::cout << "Scale for entity: " << i << " is x: " << transform->Scale.x << " y: " << transform->Scale.y << " z: " << transform->Scale.z << "\n";

                std::cout << "Component Pointer: " << transform << "\n";
                //Bed::Velocity Vel = ecs.GetComponent<Bed::Velocity>(i);
                //transform.Position += Vel.m_Velocity * deltaTime;
                //ecs.SetComponent<>(i, transform);
            }*/
        }
    }
}