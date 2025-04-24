#pragma once

#include <Graphics/TextureManager.h>

//TODO: This needs to change
#include <Graphics/GraphicVariables.h>

#include <iostream>

namespace Bed
{
    void TextureSystem(Bed::World& world)
    {
        for(int i = 0; world.GetAllEntities().size() > i; i++)
        {
            if(world.HasComponents<Bed::Texture>(i))
            {
                Bed::Texture* texture = world.GetComponent<Bed::Texture>(i);

                //TODO: some textures may change from being locked to not being locked or visa versa

                if(texture->TextureAsset == nullptr || texture->TextureSlot != Bed::TextureManager::GetSlot(texture->TexturePath))
                {
                    texture->TextureAsset = Bed::TextureManager::LoadTexture(texture->TexturePath);
                    texture->TextureSlot = Bed::TextureManager::GetSlot(texture->TexturePath);
                }
                texture->TextureAsset->Bind(texture->TextureSlot);
            }
        }
    }
}