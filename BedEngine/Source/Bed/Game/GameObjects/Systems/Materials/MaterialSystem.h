#pragma once

#include <Bed/Game/GameObjects/TextureManager.h>

//TODO: This needs to change
#include <Graphics/GraphicVariables.h>

#include <iostream>

namespace Bed
{
    void MaterialSystem(Bed::World& world)
    {
        for(int i = 0; world.GetAllEntities().size() > i; i++)
        {
            if(world.HasComponents<Bed::Material>(i))
            {
                Bed::Material* mat = world.GetComponent<Bed::Material>(i);

                //TODO: change this as the texture may change
                if(mat->Texture == nullptr)
                {
                    std::cout << "Texture: " << mat->TexturePath << " is being loaded\n";
                    mat->Texture = Bed::TextureManager::LoadTexture(mat->TexturePath);
                    std::cout << "Texture: " << mat->TexturePath << " has been loaded\n";
                }

                shader3D->Bind();

                mat->Texture->Bind(1);
            }
        }
    }
}