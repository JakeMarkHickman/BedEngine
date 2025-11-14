#pragma once

#include <SleepTrace.h>
#include <Components/Renderer/Sprite.h>
#include <Components/Material/Texture.h>

struct EnemyTag {};

void SpawnerSystem(Bed::World& world)
{
    for(uint64_t i : world.GetAllEntities())
    {
        if(world.HasComponents<Bed::Input>(i))
        {
            Bed::Input* input = world.GetComponent<Bed::Input>(i);

            if(input->KeyData[GLFW_KEY_J] == Bed::KeyState::Pressed)
            {
                uint64_t createdEnt = world.CreateEntity();

                world.AttachComponents(createdEnt, Bed::Sprite(),
                                                    Pillow::Transform(0.0f, 0.0f, 0.5f),
                                                    Bed::Texture("Assets/Resources/Textures/TestBedEngineIcon.png"),
                                                    EnemyTag());
            }

            if(input->KeyData[GLFW_KEY_K] == Bed::KeyState::Pressed)
            {
                for(uint64_t j : world.GetAllEntities())
                {
                    if(world.HasComponents<EnemyTag>(j))
                    {
                        world.RemoveComponents<EnemyTag, Bed::Sprite, Pillow::Transform, Bed::Texture>(j);
                        world.DestroyEntity(j);
                    }
                }
            }
        }
    }
}