#pragma once

#include <Duvet.h>

namespace Bed
{
    struct TextureSystems
    {
        Quilt::Duvet renderer;

        void OnTextureComponentAttached(Bed::World& world, uint64_t entity)
        {
            if(world.HasComponents<Bed::Texture>(entity))
            {
                Bed::Texture* texture = world.GetComponent<Bed::Texture>(entity);
                renderer.CreateTexture(texture->TexturePath, Quilt::TextureFiltering::Nearest, entity);
            }
        }

        void OnTextureComponentRemoved(Bed::World& world, uint64_t entity)
        {
            
        }

        void TextureSystem(Bed::World& world)
        {
            /*for(uint64_t i : world.GetAllEntities())
            {
                if(world.HasComponents<Bed::Texture>(i))
                {
                    Bed::Texture* texture = world.GetComponent<Bed::Texture>(i);

                    //TODO: some textures may change from being locked to not being locked or visa versa

                    if(texture->TextureAsset == nullptr || texture->TextureSlot != Bed::TextureManager::GetSlot(texture->TexturePath))
                    {
                        texture->TextureAsset = Bed::TextureManager::LoadTexture(texture->TexturePath, texture->TextureFiltering);
                        texture->TextureSlot = Bed::TextureManager::GetSlot(texture->TexturePath);
                        texture->TextureSize = Pillow::Vector2f(texture->TextureAsset->GetWidth(), texture->TextureAsset->GetHeight());
                    }
                    texture->TextureAsset->Bind(texture->TextureSlot);
                }
            }*/
        }
    };
}