#pragma once

#include <vector>
#include <Graphics/GraphicVariables.h>

namespace Bed
{
    struct DirectionalData
    {
        Bed::Colour3 Colour;
        float Padding1;
        Pillow::Vector3f Direction;
        float Padding2;
        float Strength;
        float Padding3;
    };

    void DirectionalLightSystem(Bed::World& world)
    {
        std::vector<Bed::DirectionalData> directionalData;

        for(uint64_t i : world.GetAllEntities())
        {
            if(world.HasComponents<Bed::DirectionalLight>(i))
            {
                Bed::DirectionalLight* dirLight = world.GetComponent<Bed::DirectionalLight>(i);

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