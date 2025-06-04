#pragma once

#include <PhysicsObject.h>

namespace Bed
{
    struct RegisteredToPhysics;

    void ForceSystem(Bed::World& world)
    {
        for(int i = 0; world.GetAllEntities().size() > i; i++)
        {
            if(world.HasComponents<RegisteredToPhysics>(i))
            {
                continue;
            }

            if(world.HasComponents<Bed::Transform, Mattress::PhysicsObject>(i))
            {
                Mattress::PhysicsObject* physicsObject = world.GetComponent<Mattress::PhysicsObject>(i);
                Bed::Transform* transform = world.GetComponent<Bed::Transform>(i);

                physicsObject->Position = transform->Position;

                world.GetWorldPhysics().AddPhysicsObject(physicsObject);

                world.AttachComponents(i, RegisteredToPhysics());
            
            }
        }
    }
}