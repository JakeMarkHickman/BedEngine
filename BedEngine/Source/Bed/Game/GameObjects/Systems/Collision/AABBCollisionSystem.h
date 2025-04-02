#pragma once

#include <Bed/Game/GameObjects/Collision/Collision.h>
#include <Bed/Game/GameObjects/Collision/AABB.h>
#include <Components/Collision/AABBCollision.h>

#include <Components/Collision/CollisionResponse/CollisionEnter.h>
#include <Components/Collision/CollisionResponse/CollisionExit.h>
#include <Components/Collision/CollisionResponse/CollisionStay.h>

#include <algorithm>
#include <vector>


namespace Bed
{
    void AABBCollisionSystem(Bed::World& world)
    {
        uint64_t entCount = world.GetAllEntities().size();

        std::vector<std::vector<uint64_t>> curCollisions(entCount);

        //TODO: This can be way more efficient
        for(int i = 0; entCount > i; i++)
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

            for(int j = i + 1; entCount > j; j++)
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

                if(Bed::Collision::AABBOverlap(updatedCollisionA, updatedCollisionB))
                {
                    curCollisions[i].push_back(j);
                    curCollisions[j].push_back(i);
                }

                /*std::cout << "Collision Box A: " << updatedCollisionA.Min.x << " " << updatedCollisionA.Max.x << "\n";
                std::cout << "Collision Box A: " << updatedCollisionA.Min.y << " " << updatedCollisionA.Max.y << "\n";
                std::cout << "Collision Box A: " << updatedCollisionA.Min.z << " " << updatedCollisionA.Max.z << "\n";

                std::cout << "Collision Box B: " << updatedCollisionB.Min.x << " " << updatedCollisionB.Max.x << "\n";
                std::cout << "Collision Box B: " << updatedCollisionB.Min.y << " " << updatedCollisionB.Max.y << "\n";
                std::cout << "Collision Box B: " << updatedCollisionB.Min.z << " " << updatedCollisionB.Max.z << "\n";*/
            }
        }

        for (int i = 0; i < entCount; i++)
        {
            if (!world.HasComponents<Bed::AABBCollision, Bed::Transform>(i))
                continue;

            std::vector<uint64_t> newCollisions = curCollisions[i];

            std::vector<uint64_t> prevCollisions;
            if(world.HasComponents<Bed::CollisionEnter>(i))
            {
                prevCollisions = world.GetComponent<Bed::CollisionEnter>(i)->collidedEntity;
            }
            else if (world.HasComponents<Bed::CollisionStay>(i))
            {
                prevCollisions = world.GetComponent<Bed::CollisionStay>(i)->collidedEntity;
            }

            std::vector<uint64_t> enterCollisions;
            for (int other : newCollisions)
            {
                if (std::find(prevCollisions.begin(), prevCollisions.end(), other) == prevCollisions.end())
                {
                    enterCollisions.push_back(other);
                }
            }

            // Find ongoing collisions (CollisionStay)
            std::vector<uint64_t> stayCollisions;
            for (int other : newCollisions)
            {
                if (std::find(prevCollisions.begin(), prevCollisions.end(), other) != prevCollisions.end())
                {
                    stayCollisions.push_back(other);
                }
            }

            // Find lost collisions (CollisionExit)
            std::vector<uint64_t> exitCollisions;
            for (int other : prevCollisions)
            {
                if (std::find(newCollisions.begin(), newCollisions.end(), other) == newCollisions.end())
                {
                    exitCollisions.push_back(other);
                }
            }

            world.RemoveComponents<Bed::CollisionExit>(i);

            // Update Components

            //TODO: Move towards a buffer for when all systems are over
            if (!enterCollisions.empty())
            {
                world.RemoveComponents<Bed::CollisionEnter>(i);
                world.AttachComponents(i, Bed::CollisionEnter(enterCollisions));
            }

            if (!stayCollisions.empty())
            {
                //TODO: Crashes (Exception thrown at 0x00007FFFD585AB6A in Playground.exe: Microsoft C++ exception: std::bad_alloc at memory location 0x0000006799D7F3F8.)
                world.RemoveComponents<Bed::CollisionEnter, Bed::CollisionStay>(i);
                world.AttachComponents(i, Bed::CollisionStay(stayCollisions));
            }

            if (!exitCollisions.empty())
            {
                world.RemoveComponents<Bed::CollisionEnter, Bed::CollisionStay>(i);
                world.AttachComponents(i, Bed::CollisionExit(exitCollisions));
            }
        }
    }
}