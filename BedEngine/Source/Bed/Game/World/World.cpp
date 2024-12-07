#include "World.h"

//TODO: Remove this
#include <Math/Transform.h>
#include <GameObjects/Components/ChildComponent.h>
#include <GameObjects/Components/CameraComponent.h>
#include <GameObjects/Components/RenderComponent.h>
#include <GameObjects/Components/AmbientLightComponent.h>
#include <GameObjects/Components/DiffuseLightComponent.h>
#include <Bed/Game/World/GameObjects/Components/VelocityComponent.h>
#include <Bed/Game/World/GameObjects/Components/UIRenderComponent.h>

#include <GameObjects/Systems/ChildSystem.h>
#include <GameObjects/Systems/CameraSystem.h>
#include <GameObjects/Systems/RenderSystem.h>
#include <GameObjects/Systems/LightingSystem.h>
#include <Bed/Game/World/GameObjects/Systems/UIRenderSystem.h>
#include <Bed/Game/World/GameObjects/Systems/MovementSystem.h>

Bed::World::World()
{
    //TODO: this is meant to all be loaded from JSON
    uint64_t player = ecs.CreateEntity();
    ecs.AttachComponents(player, Bed::Transform(Bed::Vector3(0.0f, 0.0f, -2.0f), Bed::Vector3(), Bed::Vector3(1.0f)),
                               Bed::Render("Assets/Resources/Meshes/Cube.obj"));
    
    uint64_t cam = ecs.CreateEntity();
    ecs.AttachComponents(cam, Bed::Transform(),
                              Bed::Camera(Bed::RenderType::Projection));

    uint64_t ent1 = ecs.CreateEntity();
    ecs.AttachComponents(ent1, Bed::Transform(Bed::Vector3(3.0f, 0.0f, -2.0f), Bed::Vector3(), Bed::Vector3(1.0f)),
                               Bed::Velocity(Bed::Vector3(0.0f, 0.5f, 0.0f)),
                               Bed::Render("Assets/Resources/Meshes/Cube.obj"));

    uint64_t ent2 = ecs.CreateEntity();
    ecs.AttachComponents(ent2, Bed::Transform(Bed::Vector3(-3.0f, 0.0f, -2.0f), Bed::Vector3(), Bed::Vector3(1.0f)),
                               Bed::Velocity(Bed::Vector3(0.0f, -0.5f, 0.0f)),
                               Bed::Render("Assets/Resources/Meshes/Camera.obj"),
                               Bed::Child(ent1));

    uint64_t spriteEnt = ecs.CreateEntity();
    ecs.AttachComponents(spriteEnt, Bed::Transform(Bed::Vector3(-3.0f, 0.0f, -2.0f), Bed::Vector3(), Bed::Vector3(1.0f)));

    uint64_t Ui = ecs.CreateEntity();
    ecs.AttachComponents(Ui, Bed::Transform(Bed::Vector3(0.5f, 0.5f, 0.0f), Bed::Vector3(), Bed::Vector3(0.5f)),
                               Bed::UIRender());

    uint64_t ambientLight = ecs.CreateEntity();
    ecs.AttachComponents(ambientLight, Bed::AmbientLight(0.1f, Bed::Vector3(1.0f, 1.0f, 1.0f)));

    uint64_t pointLight = ecs.CreateEntity();
    ecs.AttachComponents(pointLight, Bed::DiffuseLight(Bed::Vector3(1.0f, 0.0f, 0.6f)));

    ecs.AddSystem(Bed::ChildSystem);
    ecs.AddSystem(Bed::MoveSystem);
    ecs.AddSystem(Bed::RenderSystem);
    ecs.AddSystem(Bed::UIRenderSystem);
    ecs.AddSystem(Bed::CameraSystem);
    ecs.AddSystem(Bed::LightingSystem);
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