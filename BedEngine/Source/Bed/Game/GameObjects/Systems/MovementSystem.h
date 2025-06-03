#pragma once

#include <Math/Vector/VectorMath.h>
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

                Pillow::Vector3f nomalisedDirection = Pillow::VectorMath::Normalise(velocity->Direction);

                //float strength = 0.01f;

                //float axis = Pillow::Hyperbolic::WarpOnAxis(transform->Position.x, strength);

                float speed = velocity->Speed /* axis*/;

                //std::cout << speed << "\n";

                //TODO: make this not use normalised velocity
                transform->Position += nomalisedDirection * speed * Bed::Time::GetDeltaTime();
            }
        }
    }
}