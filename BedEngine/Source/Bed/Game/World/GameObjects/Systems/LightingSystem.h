#pragma once

#include <GameObjects/Components/AmbientLightComponent.h>
#include <Math/Vector/Vector3.h>
#include <Graphics/GraphicVariables.h>

namespace Bed
{
    void LightingSystem(Bed::ECS& ecs, float deltaTime)
    {
        for(uint64_t i = 0; ecs.GetAllEntities().size() > i; i++)
        {
            if(ecs.HasComponents<Bed::AmbientLight>(i))
            {
                Bed::AmbientLight ambient = ecs.GetComponent<Bed::AmbientLight>(i);
                shader->SetUniform1f("u_ambientLightStrenght", ambient.Strength);
                shader->SetUniform3f("u_ambientLightColour", ambient.Colour);
            }
        }
    }
}
