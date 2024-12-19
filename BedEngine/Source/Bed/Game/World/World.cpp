#include "World.h"

#include <Math/Transform.h>
#include <GameObjects/Components/CameraComponent.h>
#include <GameObjects/Components/RenderComponent.h>
#include <Bed/Game/World/GameObjects/Components/VelocityComponent.h>

#include <GameObjects/Systems/CameraSystem.h>
#include <GameObjects/Systems/RenderSystem.h>
#include <Bed/Game/World/GameObjects/Systems/MovementSystem.h>

Bed::World::World()
{

    //TODO: Needs fixing
    uint64_t Player = ecs.CreateEntity();
    ecs.AttachComponents(Player, Bed::Transform(Bed::Vector3(0.0f, 0.0f, -5.0f), Bed::Vector3(0.0f), Bed::Vector3(1.0f)),
                                 Bed::Render("Assets/Resources/Meshes/Cube.obj"));

    uint64_t Camera = ecs.CreateEntity();
    ecs.AttachComponents(Camera, Bed::Transform(Bed::Vector3(0.0f, 0.0f, 0.0f), Bed::Vector3(0.0f), Bed::Vector3(1.0f))/*,
                                 Bed::Camera(Bed::RenderType::Orthographic)*/);

    ecs.AddSystem(MoveSystem);
    ecs.AddSystem(CameraSystem);
    ecs.AddSystem(RenderSystem);
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