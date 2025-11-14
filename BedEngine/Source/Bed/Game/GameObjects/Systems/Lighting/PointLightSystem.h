#pragma once

#include <vector>
#include <Graphics/GraphicVariables.h>

namespace Bed
{

    struct PointData
    {
        Pillow::Vector3f Position;
        float Padding1; // padding is needed for vectors
        Bed::Colour3 Colour;
        float Padding2;
        float Strength = 1.0f;
        float Radius = 10.0f;
        float padding3[2];
    };

    void PointLightSystem(Bed::World& world)
    {
        std::vector<Bed::PointData> pointData;

        for(uint64_t i : world.GetAllEntities())
        {
            if(world.HasComponents<Bed::PointLight>(i))
            {
                Bed::PointLight* pointLight = world.GetComponent<Bed::PointLight>(i);

                if(!world.HasComponents<Bed::Transform>(i))
                {
                    world.AttachComponents(i, Bed::Transform(0.0f, 0.0f, 1.0f));
                }

                Bed::Transform* transform = world.GetComponent<Bed::Transform>(i);

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