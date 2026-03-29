#pragma once
#include <SleepTrace.h>

#include <Duvet.h>
#include <BasicShapes.h>

namespace Bed
{
    struct SpriteSystems
    {
        Quilt::Duvet renderer;

        void OnSpriteComponentAttached(Bed::World& world, uint64_t entity)
        {
            if(world.HasComponents<Pillow::Transform, Bed::Sprite>(entity))
            {
                Quilt::Plane plane;
                Bed::Sprite* sprite = world.GetComponent<Bed::Sprite>(entity);
                Pillow::Transform* transform = world.GetComponent<Pillow::Transform>(entity);

                unsigned int shader = renderer.GetShader("2D Shader");
                unsigned int meshID = renderer.CreateMesh("plane", plane.Vertices, plane.Indices);

                renderer.CreateRenderableObject(entity, meshID, shader, transform);
            }
        }

        void OnSpriteComponentRemoved(Bed::World& world, uint64_t entity)
        {
            if(world.HasComponents<Pillow::Transform, Bed::Sprite>(entity))
            {
                //Bed::Sprite* sprite = world.GetComponent<Bed::Sprite>(entity);
                //renderer.RemoveMesh(sprite->Handle);
            }
        }

        void OnSpriteComponentChanged(Bed::World& world, uint64_t entity)
        {
            
        }

        void SpriteSystem(Bed::World& world)
        {
            for(uint64_t i : world.GetAllEntities())
            {
                /*Bed::Sprite* sprite = world.GetComponent<Bed::Sprite>(i);

                Quilt::Batch& batch = Quilt::Duvet::GetBatch(sprite->Handle);
                Quilt::Mesh& mesh = Quilt::Duvet::GetMesh(sprite->Handle);

                LOG_DEBUG("Entity: ", i);
                LOG_DEBUG("Position, X: ", batch.Transforms[mesh.LocalIndex].Position.x, " Y: ", batch.Transforms[mesh.LocalIndex].Position.y, " Z: ", batch.Transforms[mesh.LocalIndex].Position.z);
                LOG_DEBUG("Rotation, X: ", batch.Transforms[mesh.LocalIndex].Rotation.x, " Y: ", batch.Transforms[mesh.LocalIndex].Rotation.y, " Z: ", batch.Transforms[mesh.LocalIndex].Rotation.z);
                LOG_DEBUG("Scale, X: ", batch.Transforms[mesh.LocalIndex].Scale.x, " Y: ", batch.Transforms[mesh.LocalIndex].Scale.y, " Z: ", batch.Transforms[mesh.LocalIndex].Scale.z);*/
            }
        }
    };

    /*struct SpriteInstanceData
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

        for(uint64_t i : world.GetAllEntities())
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
    }*/
}