#pragma once

#include <iostream>



namespace Bed
{
    void CollisionEnterTestSystem(Bed::World& world)
    {
        for(int i = 0; world.GetAllEntities().size() > i; i++)
        {
            if(world.HasComponents<Bed::CollisionEnter, Bed::EnemyTag, Bed::Texture>(i))
            {
                Bed::Texture* texture = world.GetComponent<Bed::Texture>(i);

                texture->TexturePath = "Assets/Resources/Textures/TestBedEngineIcon.png";
            }
        }
    }

    void CollisionExitTestSystem(Bed::World& world)
    {
        for(int i = 0; world.GetAllEntities().size() > i; i++)
        {
            if(world.HasComponents<Bed::CollisionExit, Bed::EnemyTag, Bed::Texture>(i))
            {
                Bed::Texture* texture = world.GetComponent<Bed::Texture>(i);

                texture->TexturePath = "Assets/Resources/Textures/256xMissingTexture.png";
            }
        }
    }

    void CollisionStayTestSystem(Bed::World& world)
    {
        for(int i = 0; world.GetAllEntities().size() > i; i++)
        {
            if(world.HasComponents<Bed::CollisionStay, Bed::EnemyTag, Bed::Texture>(i))
            {
                
            }
        }
    }

    void ClickableHoverTest(Bed::World& world)
    {
        for(int i = 0; world.GetAllEntities().size() > i; i++)
        {
            if(world.HasComponents<Bed::ClickableHovered, Bed::EnemyTag, Bed::Texture>(i))
            {
                Bed::Texture* texture = world.GetComponent<Bed::Texture>(i);

                texture->TexturePath = "Assets/Resources/Textures/TestBedEngineIcon.png";
            }
        }
    }

    void ClickableUnhoveredTest(Bed::World& world)
    {
        for(int i = 0; world.GetAllEntities().size() > i; i++)
        {
            if(world.HasComponents<Bed::ClickableUnhovered, Bed::EnemyTag, Bed::Texture>(i))
            {
                Bed::Texture* texture = world.GetComponent<Bed::Texture>(i);

                texture->TexturePath = "Assets/Resources/Textures/256xMissingTexture.png";
            }
        }
    }

    void ClickableClickedTest(Bed::World& world)
    {
        for(int i = 0; i < world.GetAllEntities().size(); i++)
        {
            if(world.HasComponents<Bed::ClickableClicked, Bed::EnemyTag, Bed::Texture>(i))
            {
                uint64_t ent = world.CreateEntity();
                world.AttachComponents(ent, Bed::Transform(Pillow::Vector3f(0.0f, 0.0f, 5.0f), Pillow::Vector3f(0.0f), Pillow::Vector3f(1.0f)),
                Bed::StaticMesh("Assets/Resources/Meshes/Cube.obj"),
                Bed::Texture("Assets/Resources/Textures/TestBedEngineIcon.png"),
                Bed::Input(),
                Bed::PlayerTag(),
                Bed::AABBCollision(-1.0f, 1.0f));
            }
        }
    }

    void ClickableReleasedTest(Bed::World& world)
    {
        for(int i = 0; world.GetAllEntities().size() > i; i++)
        {
            if(world.HasComponents<Bed::ClickableReleased, Bed::EnemyTag, Bed::Texture>(i))
            {

            }
        }
    }
}