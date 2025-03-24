#pragma once

#include <Components/LightSources/DirectionalLight.h>
#include <vector>
#include <Graphics/GraphicVariables.h>

namespace Bed
{
    struct DirectionalData
    {
        Bed::Vector3 Colour;
        float Padding1;
        Bed::Vector3 Direction;
        float Padding2;
        float Strength;
        float Padding3;
    };

    void DirectionalLightSystem(Bed::ECS& ecs)
    {
        std::vector<Bed::DirectionalData> directionalData;

        for(int i = 0; ecs.GetAllEntities().size() > i; i++)
        {
            if(ecs.HasComponents<Bed::DirectionalLight>(i))
            {
                Bed::DirectionalLight* dirLight = ecs.GetComponent<Bed::DirectionalLight>(i);

                Bed::DirectionalData data;
                    data.Colour = dirLight->Colour;
                    data.Direction = dirLight->Direction;
                    data.Strength = dirLight->Strength;

                directionalData.emplace_back(data);
            }
        }

        directionalLightBuffer->Bind(2);
        directionalLightBuffer->PopulateBuffer(directionalData.data(), directionalData.size() * sizeof(DirectionalData), 0);
    }
}