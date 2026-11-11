#pragma once

#include <SleepTrace.h>

namespace Bed
{
    void ParentSystem(Bed::World& world)
    {
        for(uint64_t entity : world.GetAllEntities())
        {
            if(world.HasComponents<Pillow::Transform, Bed::Parent>(entity))
            {
                Bed::Parent* parent = world.GetComponent<Bed::Parent>(entity);
                Pillow::Transform* childTransform = world.GetComponent<Pillow::Transform>(entity);

                if(world.HasComponents<Pillow::Transform>(parent->Entity))
                {
                    childTransform->Position = world.GetComponent<Pillow::Transform>(parent->Entity)->Position + parent->LocalOffset;
                }
            }
        }
    }
}