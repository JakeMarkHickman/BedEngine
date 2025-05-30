#pragma once

#include <vector>

namespace Bed
{
    struct SpriteInstanceData
    {
        glm::mat4 MatTransform;
        float TextureID;
        Pillow::Vector2f UVMin;
        Pillow::Vector2f UVMax;
    };

    void SpriteSystem(World& world)
    {
        std::vector<SpriteInstanceData> instances;

        shader2D->Bind();

        for(int i = 0; i < world.GetAllEntities().size(); i++)
        {
            if(world.HasComponents<Bed::Sprite>(i))
            {
                Bed::Sprite* sprite = world.GetComponent<Bed::Sprite>(i);

                if(!world.HasComponents<Bed::Transform>(i)) // Check for Transform
                {
                    world.AttachComponents(i, Bed::Transform(0.0f, 0.0f, 0.1f));
                }
                if(!world.HasComponents<Bed::Texture>(i)) // Check for Texture
                {
                    world.AttachComponents(i, Bed::Texture());
                }

                Bed::Transform* transform = world.GetComponent<Bed::Transform>(i);
                Bed::Texture* texture = world.GetComponent<Bed::Texture>(i);

                SpriteInstanceData instance;
                instance.MatTransform = transform->GetMatrix();
                instance.TextureID = texture->TextureSlot;

                Pillow::Vector2f Min(0.0f, 0.0f);
                Pillow::Vector2f Max(1.0f, 1.0f);

                if(world.HasComponents<Bed::SubTexture>(i))
                {
                    Bed::SubTexture* subTexture = world.GetComponent<Bed::SubTexture>(i);
                    
                    Min = subTexture->UVTopLeft;
                    Max = subTexture->UVBottomRight;
                }

                instance.UVMin = Min;
                instance.UVMax = Max;

                instances.push_back(instance);
            }
        }

        Bed::ivb2D->PopulateBuffer(instances.data(), instances.size());
    }
}