#pragma once

#include <vector>

namespace Bed
{
    struct SpriteInstanceData
    {
        glm::mat4 MatTransform;
        float TextureID;
        Bed::Vector2 UVMin;
        Bed::Vector2 UVMax;
    };

    void SpriteSystem(World& world)
    {
        std::vector<SpriteInstanceData> instances;

        shader2D->Bind();

        for(int i = 0; i < world.GetAllEntities().size(); i++)
        {

        }

        Bed::ivbUI->PopulateBuffer(instances.data(), instances.size());
    }
}