#pragma once

#include <vector>
#include <Graphics/GraphicVariables.h>

namespace Bed
{

    struct SpotData
    {
        Bed::Vector3 Position;
        float Padding1;
        Bed::Colour3 Colour;
        float Padding2;
        Bed::Vector3 Direction;
        float Padding3;
        float Strength;
        float CutOff;
        float OuterCutOff;
        float Radius;
        float padding4[4];
    };

    void SpotLightSystem(Bed::World& world)
    {
        std::vector<Bed::SpotData> spotData;

        for(int i = 0; world.GetAllEntities().size() > i; i++)
        {
            if(world.HasComponents<Bed::SpotLight>(i))
            {
                Bed::SpotLight* spotLight = world.GetComponent<Bed::SpotLight>(i);

                if(!world.HasComponents<Bed::Transform>(i))
                {
                    world.AttachComponents(i, Bed::Transform(0.0f, 0.0f, 1.0f));
                }

                Bed::Transform* transform = world.GetComponent<Bed::Transform>(i);

                Bed::SpotData data;
                    data.Position = transform->Position;
                    data.Colour = spotLight->Colour;
                    data.Direction = spotLight->Direction;
                    data.Strength = spotLight->Strength;
                    data.CutOff = spotLight->CutOff;
                    data.OuterCutOff = spotLight->OuterCutOff;
                    data.Radius = spotLight->Radius;

                spotData.emplace_back(data);
            }
        }
        spotLightBuffer->Bind(1);
        spotLightBuffer->PopulateBuffer(spotData.data(), spotData.size() * sizeof(SpotData), 0);
    }
}