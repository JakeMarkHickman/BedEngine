#pragma once

#include <Math/Transform.h>
#include <Math/Vector/VectorMath.h>
#include <Components/Velocity.h>

namespace Bed
{
    void MovementSystem(Bed::ECS& ecs, float deltaTime)
    {
        for(int i = 0; ecs.GetAllEntities().size() > i; i++)
        {
            if(ecs.HasComponents<Bed::Transform, Bed::Velocity>(i))
            {
                Bed::Transform* transform = ecs.GetComponent<Bed::Transform>(i);
                Bed::Velocity* velocity = ecs.GetComponent<Bed::Velocity>(i);

                Bed::Vector3 nomalisedDirection = velocity->Direction;

                std::cout << nomalisedDirection.x << " " << nomalisedDirection.y << " " << nomalisedDirection.x << "\n";

                transform->Position += nomalisedDirection * deltaTime;
            }
        }
    }
}