#pragma once

// Needed Components
#include <GameObjects/Components/AmbientLightComponent.h>
#include <GameObjects/Components/DiffuseLightComponent.h>
#include <Math/Transform.h>

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
                Bed::AmbientLight* ambient = ecs.GetComponent<Bed::AmbientLight>(i);
                shader->SetUniform1f("u_ambientLightStrenght", ambient->Strength);
                shader->SetUniform3f("u_ambientLightColour", ambient->Colour);
            }

            if(ecs.HasComponents<Bed::DiffuseLight>(i))
            {
                Bed::DiffuseLight* diffuse = ecs.GetComponent<Bed::DiffuseLight>(i);
                Bed::Transform* transform = new Bed::Transform(0.0f);

                if(ecs.HasComponents<Bed::Transform>(i))
                {
                    transform = ecs.GetComponent<Bed::Transform>(i);
                }

                shader->SetUniform3f("u_DiffuseLightPos", transform->Position);
                shader->SetUniform3f("u_DiffuseLightColour", diffuse->Colour);
            }
        }
    }
}
