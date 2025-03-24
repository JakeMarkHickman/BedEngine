#pragma once

#include <Components/LightSources/SpotLight.h>
#include <Math/Transform.h>
#include <vector>
#include <Graphics/GraphicVariables.h>

namespace Bed
{

    struct SpotData
    {
        Bed::Vector3 Position;
        float Padding1;
        Bed::Vector3 Colour;
        float Padding2;
        Bed::Vector3 Direction;
        float Padding3;
        float Strength;
        float CutOff;
        float OuterCutOff;
        float Radius;
        float padding4[4];
    };

    void SpotLightSystem(Bed::ECS& ecs)
    {
        std::vector<Bed::SpotData> spotData;

        for(int i = 0; ecs.GetAllEntities().size() > i; i++)
        {
            if(ecs.HasComponents<Bed::SpotLight>(i))
            {
                Bed::SpotLight* spotLight = ecs.GetComponent<Bed::SpotLight>(i);

                if(!ecs.HasComponents<Bed::Transform>(i))
                {
                    ecs.AttachComponents(i, Bed::Transform(0.0f, 0.0f, 1.0f));
                }

                Bed::Transform* transform = ecs.GetComponent<Bed::Transform>(i);

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