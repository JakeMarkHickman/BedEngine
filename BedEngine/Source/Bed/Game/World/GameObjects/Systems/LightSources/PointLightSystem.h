#pragma once

#include <Components/LightSources/PointLight.h>
#include <Math/Transform.h>
#include <vector>
#include <Graphics/GraphicVariables.h>

namespace Bed
{

    struct PointData
    {
        Bed::Vector3 Position;
        float Padding1; // padding is needed for vectors
        Bed::Vector3 Colour;
        float Padding2;
        float Strength = 1.0f;
        float Radius = 10.0f;
        float padding3[2];
    };

    void PointLightSystem(Bed::ECS& ecs, float deltaTime)
    {
        std::vector<Bed::PointData> pointData;

        for(int i = 0; ecs.GetAllEntities().size() > i; i++)
        {
            if(ecs.HasComponents<Bed::PointLight>(i))
            {
                Bed::PointLight* pointLight = ecs.GetComponent<Bed::PointLight>(i);

                if(!ecs.HasComponents<Bed::Transform>(i))
                {
                    ecs.AttachComponents(i, Bed::Transform(0.0f, 0.0f, 1.0f));
                }

                Bed::Transform* transform = ecs.GetComponent<Bed::Transform>(i);

                Bed::PointData data;
                    data.Position = transform->Position;
                    data.Colour = pointLight->Colour;
                    data.Strength = pointLight->Strength;
                    data.Radius = pointLight->Radius;

                pointData.emplace_back(data);
            }
        }
        pointLightBuffer->Bind(0);
        pointLightBuffer->PopulateBuffer(pointData.data(), pointData.size() * sizeof(PointData), 0);
    }
}