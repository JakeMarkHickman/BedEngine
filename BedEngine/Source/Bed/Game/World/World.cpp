#include "World.h"

#include <Math/Transform.h>
#include <Components/StaticMesh.h>
#include <Components/LightSources/AmbientLight.h>
#include <Components/LightSources/PointLight.h>
#include <Components/Camera.h>

#include <Systems/StaticMeshSystem.h>
#include <Systems/LightSources/AmbientLightSystem.h>
#include <Systems/LightSources/PointLightSystem.h>
#include <Systems/CameraSystem.h>

Bed::World::World()
{
    uint64_t Player = ecs.CreateEntity();
    ecs.AttachComponents(Player, Bed::Transform(Bed::Vector3(0.0f, 0.0f, 5.0f), Bed::Vector3(0.0f), Bed::Vector3(1.0f)),
                                 Bed::StaticMesh("Assets/Resources/Meshes/Cube.obj"));

    uint64_t Camera = ecs.CreateEntity();
    ecs.AttachComponents(Camera, Bed::Transform(Bed::Vector3(0.0f, 1.0f, -5.0f), Bed::Vector3(0.0f), Bed::Vector3(1.0f)),
                                 Bed::Camera(Bed::ProjectionType::Perspective));

    uint64_t Ent1 = ecs.CreateEntity();
    ecs.AttachComponents(Ent1, Bed::Transform(Bed::Vector3(-2.5f, 0.0f, 5.0f), Bed::Vector3(0.0f), Bed::Vector3(1.0f)),
                               Bed::StaticMesh("Assets/Resources/Meshes/Cube.obj"));

    uint64_t Ent2 = ecs.CreateEntity();
    ecs.AttachComponents(Ent2, Bed::Transform(Bed::Vector3(2.5f, 0.0f, 5.0f), Bed::Vector3(0.0f), Bed::Vector3(1.0f)),
                               Bed::StaticMesh("Assets/Resources/Meshes/Cube.obj"));

    uint64_t Ambient = ecs.CreateEntity();
    ecs.AttachComponents(Ambient, Bed::AmbientLight());

    uint64_t Point1 = ecs.CreateEntity();
    ecs.AttachComponents(Point1, Bed::Transform(Bed::Vector3(0.0f, 0.0f, 3.0f), 0.0f, 1.0f),
                                Bed::PointLight(1.0f, 1.0f, 1.0f));

    uint64_t Point2 = ecs.CreateEntity();
    ecs.AttachComponents(Point2, Bed::Transform(Bed::Vector3(-2.5f, 0.0f, 3.0f), 0.0f, 1.0f),
                                Bed::PointLight(Bed::Vector3(0.11f, 0.8f, 0.6f), 1.0f, 1.0f));

    uint64_t Point3 = ecs.CreateEntity();
    ecs.AttachComponents(Point3, Bed::Transform(Bed::Vector3(2.5f, 0.0f, 3.0f), 0.0f, 1.0f),
                                Bed::PointLight(Bed::Vector3(0.2f, 0.0f, 1.0f), 1.0f, 1.0f));

    ecs.AddSystem(Bed::StaticMeshSystem);
    ecs.AddSystem(Bed::AmbientLightSystem);
    ecs.AddSystem(Bed::PointLightSystem);
    ecs.AddSystem(Bed::CameraSystem);
}

Bed::World::~World()
{
    ecs.RemoveAllSystems();
}

bool Bed::World::LoadWorld(std::string path)
{
    BeginPlay();
    return false;
}

bool Bed::World::UnloadWorld()
{
    return false;
}

bool Bed::World::IsWorldLoaded()
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