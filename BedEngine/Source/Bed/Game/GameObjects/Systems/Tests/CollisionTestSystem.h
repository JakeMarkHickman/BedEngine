#pragma once

#include <iostream>

namespace Bed
{
    void CollisionEnterTestSystem(Bed::World& world)
    {
        for(int i = 0; world.GetAllEntities().size() > i; i++)
        {
            if(world.HasComponents<Bed::CollisionEnter>(i))
            {
                std::cout << "Entity: " << i << " Started a collision\n";
            }
        }
    }

    void CollisionExitTestSystem(Bed::World& world)
    {
        for(int i = 0; world.GetAllEntities().size() > i; i++)
        {
            if(world.HasComponents<Bed::CollisionExit>(i))
            {
                std::cout << "Entity: " << i << " Ended a collision\n";
            }
        }
    }

    void CollisionStayTestSystem(Bed::World& world)
    {
        for(int i = 0; world.GetAllEntities().size() > i; i++)
        {
            if(world.HasComponents<Bed::CollisionStay>(i))
            {
                std::cout << "Entity: " << i << " stayed in a collision\n";
            }
        }
    }
}