#pragma once

#include <Bed/Game/GameObjects/Collision/Collision.h>
#include <Bed/Game/GameObjects/Collision/AABB.h>
#include <Bed/Game/GameObjects/Components/AABBCollision.h>


//TODO: Remove
#include <iostream>

namespace Bed
{
    void AABBCollisionSystem(Bed::World& world)
    {
        //TODO: This can be way more efficient
        for(int i = 0; world.GetAllEntities().size() > i; i++)
        {
            if(!world.HasComponents<Bed::AABBCollision, Bed::Transform>(i))
            {
                continue;
            }

            Bed::Transform* transformA = world.GetComponent<Bed::Transform>(i);
            Bed::AABBCollision* collisionA = world.GetComponent<Bed::AABBCollision>(i);

            Bed::AABB updatedCollisionA;
            updatedCollisionA.Min = collisionA->BoundingBox.Min + transformA->Position;
            updatedCollisionA.Max = collisionA->BoundingBox.Max + transformA->Position;

            for(int j = i + 1; world.GetAllEntities().size() > j; j++)
            {
                if(!world.HasComponents<Bed::AABBCollision, Bed::Transform>(j))
                {
                    continue;
                }

                Bed::Transform* transformB = world.GetComponent<Bed::Transform>(j);
                Bed::AABBCollision* collisionB = world.GetComponent<Bed::AABBCollision>(j);

                Bed::AABB updatedCollisionB;
                updatedCollisionB.Min = collisionB->BoundingBox.Min + transformB->Position;
                updatedCollisionB.Max = collisionB->BoundingBox.Max + transformB->Position;

                if(i != j && Bed::Collision::AABBOverlap(updatedCollisionA, updatedCollisionB))
                {
                    std::cout << "Collision between " << i << " and " << j << "\n";
                }

                /*std::cout << "Collision Box A: " << updatedCollisionA.Min.x << " " << updatedCollisionA.Max.x << "\n";
                std::cout << "Collision Box A: " << updatedCollisionA.Min.y << " " << updatedCollisionA.Max.y << "\n";
                std::cout << "Collision Box A: " << updatedCollisionA.Min.z << " " << updatedCollisionA.Max.z << "\n";

                std::cout << "Collision Box B: " << updatedCollisionB.Min.x << " " << updatedCollisionB.Max.x << "\n";
                std::cout << "Collision Box B: " << updatedCollisionB.Min.y << " " << updatedCollisionB.Max.y << "\n";
                std::cout << "Collision Box B: " << updatedCollisionB.Min.z << " " << updatedCollisionB.Max.z << "\n";*/
            }
        }
    }
}