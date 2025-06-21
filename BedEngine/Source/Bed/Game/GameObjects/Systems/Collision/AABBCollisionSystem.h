#pragma once

#include <Bed/Game/GameObjects/Physics/Collision/Collision.h>
#include <Bed/Game/GameObjects/Physics/Collision/AABB.h>

#include <Components/Event/CollisionResponse/CollisionEnter.h>
#include <Components/Event/CollisionResponse/CollisionExit.h>
#include <Components/Event/CollisionResponse/CollisionStay.h>

#include <algorithm>
#include <vector>


namespace Bed
{
    void AABBCollisionSystem(Bed::World& world)
    {
        std::vector<uint64_t>& allEntities = world.GetAllEntities();
        std::vector<std::vector<uint64_t>> curCollisions(allEntities.size());

        //TODO: This can be way more efficient
        for(uint64_t i : allEntities)
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

            for(uint64_t j : allEntities)
            {
                if(i >= j) // Only Check Every entity once against counter entity
                {
                    continue;
                }

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
            }
        }

        for (uint64_t i : allEntities)
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