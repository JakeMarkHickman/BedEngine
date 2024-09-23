#pragma once

#include <Bed/Core.h>
#include "ECS/ECS.h"
#include "Components/TransformComponent.h"
#include "Systems/MovementSystem.h"

// TODO: BED_API
namespace Bed
{
    class Map
    {
    public:
        Map() 
        {
            // TODO: Remove this

            //Entity 1
            uint64_t newEntity = ecs.CreateEntity();
            ecs.AttachComponents(newEntity, Bed::Transform(Bed::Vector3(1.0f, 1.0f, 1.0f), Bed::Vector3(1.0f, 1.0f, 1.0f), Bed::Vector3(1.0f, 1.0f, 1.0f)),
                                            Bed::Velocity(Bed::Vector3(0.5f, 0.5f, 0.5f)));

            //Entity 2
            uint64_t newerEnt = ecs.CreateEntity();
            ecs.AttachComponents(newerEnt, Bed::Transform(Bed::Vector3(1.0f, 1.0f, 1.0f), Bed::Vector3(1.0f, 1.0f, 1.0f), Bed::Vector3(1.0f, 1.0f, 1.0f)),
                                            Bed::Vector3(1.0f, 1.0f, 1.0f));

            ecs.AddSystem(Bed::MoveSystem);
        };
        virtual ~Map() {};

        virtual void BeginPlay() {};
        virtual void Update(float DeltaTime) 
        {
            ecs.UpdateSystems(DeltaTime);
        };

    protected:
        ECS ecs;

    private:
    };
}