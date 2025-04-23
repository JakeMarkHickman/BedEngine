#pragma once

#include <Math/Transform.h>
#include <Math/Vector/VectorMath.h>
#include <Components/Velocity.h>

#include <App/Time.h>

namespace Bed
{
    void MovementSystem(Bed::World& world)
    {
        for(int i = 0; world.GetAllEntities().size() > i; i++)
        {
            if(world.HasComponents<Bed::Transform, Bed::Velocity>(i))
            {
                Bed::Transform* transform = world.GetComponent<Bed::Transform>(i);
                Bed::Velocity* velocity = world.GetComponent<Bed::Velocity>(i);

                Bed::Vector3 nomalisedDirection = Bed::VectorMath::Normalise(velocity->Direction);

                //TODO: make this not use normalised velocity
                transform->Position += nomalisedDirection * velocity->Speed * Bed::Time::GetDeltaTime();
            }
        }
    }
}