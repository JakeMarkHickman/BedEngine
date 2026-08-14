#pragma once

#include <SleepTrace.h>

namespace Bed
{
    class PhysicsObjectSystems
    {
    public:
        void OnPhysicsObjectComponentAttached(Bed::World& world, uint64_t entity)
        {
            if(world.HasComponents<Pillow::Transform, Bed::PhysicsObject>(entity))
            {
                Pillow::Transform* transform = world.GetComponent<Pillow::Transform>(entity);
                Bed::PhysicsObject* object = world.GetComponent<Bed::PhysicsObject>(entity);
                float mass = object->Mass;

                object->Handle = world.GetWorldPhysics().AddPhysicsBody(transform->Position, mass);
            }
        }

        void OnPhysicsObjectComponentRemoved(Bed::World& world, uint64_t entity)
        {
            if(world.HasComponents<Pillow::Transform, Mattress::PhysicsObject>(entity))
            {
                
            }
        }

        void PhysicsObjectSystem(Bed::World& world)
        {
            for(uint64_t entity : world.GetAllEntities())
            {
                if(world.HasComponents<Mattress::PhysicsObject, Pillow::Transform>(entity))
                {
                    
                }
            }
        }
    };
}