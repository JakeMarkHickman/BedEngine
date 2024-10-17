#pragma once

#include <Bed/Core.h>
#include "ECS/ECS.h"
#include "Components/TransformComponent.h"
#include "Systems/MovementSystem.h"
#include "Systems/2DRenderSystem.h"
#include "Components/2DRenderComponent.h"
#include "Components/CameraComponent.h"

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
            uint64_t Player = ecs.CreateEntity();
            ecs.AttachComponents(Player, Bed::Transform(Bed::Vector3(0.0f, 0.0f, 0.0f), Bed::Vector3(0.0f, 0.0f, 0.0f), Bed::Vector3(1.5f, 1.5f, 1.5f)),
                                            Bed::Velocity(Bed::Vector3(0.005f, 0.005f, 0.005f)), 
                                            Bed::TwoDimensionalRender(new Bed::Texture("C:/Users/Jake/Documents/GitHub/BedEngine/BedEngine/Resources/Textures/TestBedEngineIcon.png"), 0));

            //Entity 2
            uint64_t newerEnt = ecs.CreateEntity();
            ecs.AttachComponents(newerEnt, Bed::Transform(Bed::Vector3(-0.5f, 1.0f, 0.0f), Bed::Vector3(0.0f, 0.0f, 0.0f), Bed::Vector3(0.5f, 0.5f, 0.5f)),
                                        Bed::TwoDimensionalRender(new Bed::Texture("C:/Users/Jake/Documents/GitHub/BedEngine/BedEngine/Resources/Textures/TestBedEngineIcon.png"), 0));

            uint64_t GreatEntity = ecs.CreateEntity();
            ecs.AttachComponents(GreatEntity, Bed::Transform(Bed::Vector3(0.0f, 0.0f, 0.0f), Bed::Vector3(0.0f, 0.0f, 0.0f), Bed::Vector3(1.0f, 1.0f, 1.0f)),
                                              Bed::Velocity(Bed::Vector3(-0.001f, -0.001f, -0.001f)),
                                              Bed::TwoDimensionalRender(new Bed::Texture("C:/Users/Jake/Documents/GitHub/BedEngine/BedEngine/Resources/Textures/TestImage.png"), 0));

            uint64_t Camera = ecs.CreateEntity();
            ecs.AttachComponents(Camera, Bed::Camera(Bed::RenderType::Orthographic));

            ecs.AddSystem(Bed::MoveSystem);
            ecs.AddSystem(Bed::TwoDimensionalRenderSystem);
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