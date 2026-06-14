#pragma once

#include <Duvet.h>

namespace Bed
{
    struct TextureSystems
    {
        Quilt::Duvet renderer;

        void OnTextureComponentAttached(Bed::World& world, uint64_t entity)
        {
            //if(world.HasComponents<Bed::Texture>(entity))
            //{
            //    Bed::Texture* texture = world.GetComponent<Bed::Texture>(entity);
            //    texture->Handle = renderer.CreateTexture(entity, texture->TexturePath, Quilt::TextureFiltering::Nearest);
            //}
        }

        void OnTextureComponentRemoved(Bed::World& world, uint64_t entity)
        {
            
        }

        void TextureSystem(Bed::World& world)
        {
            for(uint64_t entity : world.GetAllEntities())
            {
                if(world.HasComponents<Bed::Texture>(entity))
                {
                    Bed::Texture* texture = world.GetComponent<Bed::Texture>(entity);

                    if(texture->TexturePath == "None")
                    {
                        texture->Handle = renderer.GetDefaultTexture();
                        continue;
                    }

                    if(!renderer.IsRegisteredTexture(texture->TexturePath))
                    {
                        renderer.RegisterTexture(texture->TexturePath, texture->Filter);
                    }
                    
                    texture->Handle = renderer.GetTexture(texture->TexturePath);
                }
            }
        }
    };
}