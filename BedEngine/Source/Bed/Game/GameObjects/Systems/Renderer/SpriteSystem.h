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

                renderer.CreateRenderableObject(entity, meshID, shader);
            }
        }

        void OnSpriteComponentRemoved(Bed::World& world, uint64_t entity)
        {
            if(world.HasComponents<Pillow::Transform, Bed::Sprite>(entity))
            {
                renderer.RemoveRenderableObject(entity);
            }
        }

        void SpriteSystem(Bed::World& world)
        {
            for(uint64_t entity : world.GetAllEntities())
            {
                if(world.HasComponents<Bed::Sprite, Pillow::Transform>(entity))
                {
                    Pillow::Transform* transform = world.GetComponent<Pillow::Transform>(entity);

                    Quilt::SpriteInstanceData data;

                    data.Colour = Pillow::Vector4f(1.0f);
                    data.TransfomMatrix = transform->GetMatrix();

                    if(world.HasComponents<Bed::Texture>(entity))
                    {
                        Bed::Texture* texture = world.GetComponent<Bed::Texture>(entity);

                        data.TextureID = texture->Handle;
                        data.UVMin = texture->MinUV;
                        data.UVMax = texture->MaxUV;
                    }
                    else
                    {
                        data.TextureID = renderer.GetDefaultTexture();
                        data.UVMin = Pillow::Vector2f(0.0f);
                        data.UVMax = Pillow::Vector2f(1.0f);
                    }

                    //TODO: Update Transform only;
                    //renderer.UpdateTransform(entity, *transform);
                    renderer.QueueInstance(entity, data);
                }
            }
        }
    };
}