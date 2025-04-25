#pragma once

#include <Graphics/GraphicVariables.h>

namespace Bed
{
    void FogSystem(Bed::World& world)
    {
        static bool IsCurrentlyEnabled = false;
        bool SetFog = false;

        for(int i = 0; i < world.GetAllEntities().size(); i++)
        {
            if(world.HasComponents<Bed::Fog>(i))
            {
                Bed::Fog* fog = world.GetComponent<Bed::Fog>(i);

                SetFog = true;
                shader3D->SetUniform3f("u_FogColour", fog->FogColour);
                shader3D->SetUniform1f("u_FogNear", fog->FogNear);
                shader3D->SetUniform1f("u_FogFar", fog->FogFar);
            }
        }

        if(IsCurrentlyEnabled != SetFog) // Disable/Enable Fog in shader
        {
            IsCurrentlyEnabled = SetFog;
            shader3D->SetUniform1i("u_EnableFog", SetFog);
        }
    }
}