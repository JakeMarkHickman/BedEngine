#pragma once

#include <Bed/Game/GameObjects/TextureManager.h>

//TODO: This needs to change
#include <Graphics/GraphicVariables.h>

#include <iostream>

namespace Bed
{
    void MaterialSystem(Bed::World& world)
    {
        for(int i = 0; world.GetAllEntities().size() > i; i++)
        {
            if(world.HasComponents<Bed::Material>(i))
            {
                Bed::Material* mat = world.GetComponent<Bed::Material>(i);
                
            }
        }
    }
}