#pragma once

namespace Test
{
    void CollisionEnterTestSystem(Bed::World& world)
    {
        for(uint64_t i : world.GetAllEntities())
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
        for(uint64_t i : world.GetAllEntities())
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
        for(uint64_t i : world.GetAllEntities())
        {
            if(world.HasComponents<Bed::CollisionStay, Bed::EnemyTag, Bed::Texture>(i))
            {
                
            }
        }
    }

    void ClickableHoverTest(Bed::World& world)
    {
        for(uint64_t i : world.GetAllEntities())
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
        for(uint64_t i : world.GetAllEntities())
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
        for(uint64_t i : world.GetAllEntities())
        {
            if(world.HasComponents<Bed::ClickableClicked>(i))
            {
                if(world.HasComponents<Test::AddEntityTag>(i))
                {
                    uint64_t ent = world.CreateEntity();
                    world.AttachComponents(ent, Bed::Transform(Pillow::Vector3f(0.0f, 0.0f, 0.0f), Pillow::Vector3f(0.0f), Pillow::Vector3f(1.0f)),
                                                Bed::Sprite(),
                                                Bed::Texture("Assets/Resources/Textures/LittleGuy.png", Bed::TextureFiltering::Nearest),
                                                Bed::SubTexture(),
                                                Bed::Timer(0.5f, true, true),
                                                Bed::EnemyTag());
                }

                if(world.HasComponents<Test::RemoveEntityTag>(i))
                {
                    std::vector<uint64_t> entites = world.GetAllEntities();

                    for(uint64_t j : entites)
                    {
                        if(world.HasComponents<Bed::Sprite>(j))
                        {
                            world.DestroyEntity(j);
                        }
                    }
                }
            }
        }
    }

    void ClickableReleasedTest(Bed::World& world)
    {
        for(uint64_t i : world.GetAllEntities())
        {
            if(world.HasComponents<Bed::ClickableReleased, Bed::EnemyTag, Bed::Texture>(i))
            {

            }
        }
    }
}