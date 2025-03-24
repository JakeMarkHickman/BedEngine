#pragma once

#include <Components/LightSources/AmbientLight.h>
#include <Graphics/GraphicVariables.h>

namespace Bed
{
    void AmbientLightSystem(Bed::ECS& ecs)
    {
        for(int i = 0; ecs.GetAllEntities().size() > i; i++)
        {
            if(ecs.HasComponents<Bed::AmbientLight>(i))
            {
                Bed::AmbientLight* ambient = ecs.GetComponent<Bed::AmbientLight>(i);

                shader3D->SetUniform1f("u_ambientLightStrength", ambient->Strength);
                shader3D->SetUniform3f("u_ambientLightColour", ambient->Colour);
            }
        }
    }
}