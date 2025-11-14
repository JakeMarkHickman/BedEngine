#pragma once

#include <PhysicsObject.h>

namespace Bed
{
    struct RegisteredToPhysics {};

    //TODO: Move this into a hook when a component gets added!
    void PhysicsRegisterSystem(Bed::World& world)
    {
        for(uint64_t i : world.GetAllEntities())
        {
            if(world.HasComponents<RegisteredToPhysics>(i))
            {
                continue;
            }

            if(world.HasComponents<Pillow::Transform, Mattress::PhysicsObject>(i))
            {
                Mattress::PhysicsObject* physicsObject = world.GetComponent<Mattress::PhysicsObject>(i);
                Pillow::Transform* transform = world.GetComponent<Pillow::Transform>(i);

                physicsObject->Position = transform->Position;

                world.GetWorldPhysics().AddPhysicsObject(physicsObject);

                world.AttachComponents(i, Bed::RegisteredToPhysics());
            
            }
        }
    }
}