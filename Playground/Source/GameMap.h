#pragma once

#include <Bed/GameObjects/Map.h>
#include <Bed/Math/Vector.h>
#include <Graphics/GraphicVariables.h>
#include <Bed/GameObjects/Components/TransformComponent.h>
#include <Bed/GameObjects/Components/VelocityComponent.h>
#include <Bed/GameObjects/Components/CameraComponent.h>
#include <Bed/GameObjects/Components/RenderComponent.h>

#include <Bed/GameObjects/Systems/MovementSystem.h>
#include <Bed/GameObjects/Systems/CameraSystem.h>
#include <Bed/GameObjects/Systems/RenderSystem.h>

#include <Bed/Math/Matrix.h>


namespace Game
{
    class GameMap : public Bed::Map
    {
    public:
        GameMap() {
            uint64_t cam = ecs.CreateEntity();
            ecs.AttachComponents(cam, Bed::Transform(Bed::Vector3(), Bed::Vector3(), Bed::Vector3()),
                                      Bed::Camera(Bed::RenderType::Projection));

            uint64_t ent1 = ecs.CreateEntity();
            ecs.AttachComponents(ent1, Bed::Transform(Bed::Vector3(3.0f, 0.0f, -2.0f), Bed::Vector3(), Bed::Vector3(1.0f)),
                                       Bed::Velocity(Bed::Vector3(0.0f, 0.5f, 0.0f)),
                                       Bed::Render("Assets/Resources/Meshes/Tri.obj"));

            uint64_t ent2 = ecs.CreateEntity();
            ecs.AttachComponents(ent2, Bed::Transform(Bed::Vector3(-3.0f, 0.0f, -2.0f), Bed::Vector3(), Bed::Vector3(1.0f)),
                                       Bed::Velocity(Bed::Vector3(0.0f, -0.5f, 0.0f)),
                                       Bed::Render("Assets/Resources/Meshes/Untitled.obj"));

            uint64_t ent3 = ecs.CreateEntity();
            ecs.AttachComponents(ent3, Bed::Transform(Bed::Vector3(0.0f, 0.0f, -2.0f), Bed::Vector3(), Bed::Vector3(1.0f)),
                                       Bed::Render("Assets/Resources/Meshes/Cube.obj"));

            ecs.AddSystem(Bed::MoveSystem);
            ecs.AddSystem(Bed::RenderSystem);
            ecs.AddSystem(Bed::CameraSystem);
        };

        void BeginPlay() override
        {
            Bed::Matrix3x3 V1;
            
            Bed::Matrix3x3 V2 = V1 - V1;

            for(int i = 0; i < 3; i++)
            {
                for(int j = 0; j < 3; j++)
                {
                    std::cout << "V2.element[" << i << "][" << j << "] = " << V2.element[i][j] << std::endl;
                    
                }
            }
        }
    };
}
