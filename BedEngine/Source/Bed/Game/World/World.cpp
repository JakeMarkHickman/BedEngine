#include "World.h"

#include <Math/Transform.h>
#include <Bed/Game/World/GameObjects/Components/VelocityComponent.h>

#include <Bed/Game/World/GameObjects/Systems/MovementSystem.h>

Bed::World::World()
{
    uint64_t Player = ecs.CreateEntity();
    ecs.AttachComponents(Player, Bed::Transform(1.0f), Bed::Velocity(0.1f));

    uint64_t Camera = ecs.CreateEntity();
    ecs.AttachComponents(Camera, Bed::Transform(0.0f));

    ecs.AddSystem(MoveSystem);
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