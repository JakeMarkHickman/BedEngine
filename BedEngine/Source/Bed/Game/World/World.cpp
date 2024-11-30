#include "World.h"

//TODO: Remove this
#include <Math/Transform.h>
#include <GameObjects/Components/CameraComponent.h>
#include <GameObjects/Components/RenderComponent.h>
#include <Bed/Game/World/GameObjects/Components/VelocityComponent.h>

#include <GameObjects/Systems/CameraSystem.h>
#include <GameObjects/Systems/RenderSystem.h>
#include <Bed/Game/World/GameObjects/Systems/MovementSystem.h>

Bed::World::World()
{
    //TODO: this is meant to all be loaded from JSON
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

    uint64_t player = ecs.CreateEntity();
    ecs.AttachComponents(player, Bed::Transform(Bed::Vector3(0.0f, 0.0f, -2.0f), Bed::Vector3(), Bed::Vector3(1.0f)),
                               Bed::Render("Assets/Resources/Meshes/Cube.obj"));

    ecs.AddSystem(Bed::MoveSystem);
    ecs.AddSystem(Bed::RenderSystem);
    ecs.AddSystem(Bed::CameraSystem);
}

Bed::World::~World()
{
    
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