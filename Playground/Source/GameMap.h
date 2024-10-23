#pragma once

#include <Bed/GameObjects/Map.h>
#include <Bed/Math/Vector.h>
#include <Graphics/GraphicVariables.h>
#include <Bed/GameObjects/Components/TransformComponent.h>
#include <Bed/GameObjects/Components/VelocityComponent.h>
#include <Bed/GameObjects/Components/CameraComponent.h>
#include <Bed/GameObjects/Components/2DRenderComponent.h>

#include <Bed/GameObjects/Systems/MovementSystem.h>
#include <Bed/GameObjects/Systems/CameraSystem.h>
#include <Bed/GameObjects/Systems/2DRenderSystem.h>


namespace Game
{
    class GameMap : public Bed::Map
    {
    public:
        GameMap() {
            std::cout << "Map Instanciated" << std::endl;
            std::cout << "Creating Cam" << std::endl;
            uint64_t cam = ecs.CreateEntity();
            ecs.AttachComponents(cam, Bed::Transform(Bed::Vector3(0.0f, 0.0f, 0.0f), Bed::Vector3(0.0f, 0.0f, 0.0f), Bed::Vector3(0.0f, 0.0f, 0.0f)),
                                      Bed::Camera(Bed::RenderType::Orthographic));

            std::cout << "Creating ent1" << std::endl;
            uint64_t ent1 = ecs.CreateEntity();
            std::cout << "Populating ent1" << std::endl;
            ecs.AttachComponents(ent1, Bed::Transform(Bed::Vector3(0.0f, 0.0f, 0.0f), Bed::Vector3(0.0f, 0.0f, 0.0f), Bed::Vector3(1.0f, 1.0f, 1.0f)),
                                       Bed::Velocity(Bed::Vector3(0.0f, 0.0f, 0.0f)),
                                       Bed::TwoDimensionalRender(Bed::texture, 0));

            std::cout << "Adding systems" << std::endl;
            ecs.AddSystem(Bed::MoveSystem);
            ecs.AddSystem(Bed::TwoDimensionalRenderSystem);
            ecs.AddSystem(Bed::CameraSystem);

        };
    };
}
