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
}