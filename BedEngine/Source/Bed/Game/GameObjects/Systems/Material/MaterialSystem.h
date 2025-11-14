#pragma once

//TODO: This needs to change
#include <Graphics/GraphicVariables.h>

#include <iostream>

namespace Bed
{
    void MaterialSystem(Bed::World& world)
    {
        for(uint64_t i : world.GetAllEntities())
        {
            if(world.HasComponents<Bed::Material>(i))
            {
                Bed::Material* mat = world.GetComponent<Bed::Material>(i);
                
            }
        }
    }
}