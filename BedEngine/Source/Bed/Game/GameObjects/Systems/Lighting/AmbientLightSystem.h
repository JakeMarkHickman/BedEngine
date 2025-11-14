#pragma once

#include <Graphics/GraphicVariables.h>

namespace Bed
{
    void AmbientLightSystem(Bed::World& world)
    {
        for(uint64_t i : world.GetAllEntities())
        {
            if(world.HasComponents<Bed::AmbientLight>(i))
            {
                Bed::AmbientLight* ambient = world.GetComponent<Bed::AmbientLight>(i);

                shader3D->SetUniform1f("u_ambientLightStrength", ambient->Strength);
                shader3D->SetUniform3f("u_ambientLightColour", ambient->Colour);
            }
        }
    }
}