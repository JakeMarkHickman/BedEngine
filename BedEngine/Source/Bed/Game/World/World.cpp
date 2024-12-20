#include "World.h"

#include <Math/Transform.h>
#include <GameObjects/Components/CameraComponent.h>
#include <GameObjects/Components/RenderComponent.h>
#include <GameObjects/Components/AmbientLightComponent.h>
#include <GameObjects/Components/DiffuseLightComponent.h>
#include <GameObjects/Components/ChildComponent.h>
#include <Bed/Game/World/GameObjects/Components/VelocityComponent.h>

#include <GameObjects/Systems/CameraSystem.h>
#include <GameObjects/Systems/RenderSystem.h>
#include <GameObjects/Systems/LightingSystem.h>
#include <GameObjects/Systems/ChildSystem.h>
#include <Bed/Game/World/GameObjects/Systems/MovementSystem.h>

Bed::World::World()
{
    uint64_t Player = ecs.CreateEntity();
    ecs.AttachComponents(Player, Bed::Transform(Bed::Vector3(0.0f, 0.0f, -2.0f), Bed::Vector3(0.0f), Bed::Vector3(1.0f)),
                                 Bed::Render("Assets/Resources/Meshes/Cube.obj"));

    uint64_t Camera = ecs.CreateEntity();
    ecs.AttachComponents(Camera, Bed::Transform(Bed::Vector3(0.0f, 0.0f, -15.0f), Bed::Vector3(0.0f), Bed::Vector3(1.0f)),
                                 Bed::Camera(Bed::RenderType::Projection));

    uint64_t Ent1 = ecs.CreateEntity();
    ecs.AttachComponents(Ent1, Bed::Transform(Bed::Vector3(3.0f, 0.0f, -2.0f), Bed::Vector3(0.0f), Bed::Vector3(1.0f)),
                              Bed::Render("Assets/Resources/Meshes/Cube.obj"),
                              Bed::Velocity(Bed::Vector3(0.0f, 0.5f, 0.0f)));

    uint64_t Ent2 = ecs.CreateEntity();
    ecs.AttachComponents(Ent2, Bed::Transform(Bed::Vector3(-3.0f, 0.0f, -2.0f), Bed::Vector3(0.0f), Bed::Vector3(1.0f)),
                               Bed::Render("Assets/Resources/Meshes/Cube.obj"),
                               Bed::Child(Ent1));

    uint64_t Ambient = ecs.CreateEntity();
    ecs.AttachComponents(Ambient, Bed::AmbientLight(0.1f, Bed::Vector3(1.0f, 1.0f, 1.0f)));

    uint64_t Diffuse = ecs.CreateEntity();
    ecs.AttachComponents(Diffuse, Bed::DiffuseLight(Bed::Vector3(1.0f, 1.0f, 1.0f)));

    ecs.AddSystem(MoveSystem);
    ecs.AddSystem(CameraSystem);
    ecs.AddSystem(RenderSystem);
    ecs.AddSystem(LightingSystem);
    ecs.AddSystem(ChildSystem);
}

Bed::World::~World()
{
    ecs.RemoveAllSystems();
}

bool Bed::World::LoadWorld(std::string path)
{
    return false;
}

void Bed::World::BeginPlay()
{

}

void Bed::World::Update(float deltaTime)
{
    ecs.UpdateSystems(deltaTime);
}