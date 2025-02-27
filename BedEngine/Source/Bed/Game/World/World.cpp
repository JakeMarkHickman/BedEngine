#include "World.h"

#include <Math/Transform.h>
#include <Components/StaticMesh.h>
#include <Components/LightSources/AmbientLight.h>
#include <Components/LightSources/PointLight.h>
#include <Components/LightSources/SpotLight.h>
#include <Components/LightSources/DirectionalLight.h>
#include <Components/Camera.h>
#include <Components/Velocity.h>
#include <Bed/Game/World/GameObjects/Components/PlayerController.h>

#include <Systems/StaticMeshSystem.h>
#include <Systems/LightSources/AmbientLightSystem.h>
#include <Systems/LightSources/PointLightSystem.h>
#include <Systems/LightSources/SpotLightSystem.h>
#include <Systems/LightSources/DirectionalLightSystem.h>
#include <Systems/CameraSystem.h>
#include <Systems/MovementSystem.h>
#include <Bed/Game/World/GameObjects/Systems/PlayerControllerSystem.h>

#include <Bed/Game/World/GameObjects/Systems/Tests/StressTestSystem.h>

Bed::World::World()
{
    uint64_t Camera = ecs.CreateEntity();
    ecs.AttachComponents(Camera, Bed::Transform(Bed::Vector3(0.0f, 5.0f, -5.0f), Bed::Vector3(0.0f), Bed::Vector3(1.0f)),
                                 Bed::Camera(Bed::ProjectionType::Perspective));

    for(int i = 0; i < 1000; i++)
    {
        uint64_t ent = ecs.CreateEntity();
        ecs.AttachComponents(ent, Bed::Transform(0.0f, 0.0f, 1.0f));
    }

    ecs.AddSystem(Bed::StressTestSystem);
}

Bed::World::~World()
{
    ecs.RemoveAllSystems();
}

bool Bed::World::LoadWorld(std::string path)
{
    nlohmann::json jsonWorld = Bed::JsonRW::ReadFromFile(path);

    if(!jsonWorld.contains("World"))
    {
        std::cout << path << " is not a world file" << "\n";
        return false;
    }

    //TODO: Register Components to the engine, once registred use to figure out intput :)
    
    /* Read Data from file */


    m_LoadedWorldName = jsonWorld["World"]["WorldName"];
    std::cout << "Loaded World: " << m_LoadedWorldName << "\n";
    BeginPlay();
    return true;
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
    /*uint64_t Player = ecs.CreateEntity();
    ecs.AttachComponents(Player, Bed::Transform(Bed::Vector3(0.0f, 0.0f, 5.0f), Bed::Vector3(0.0f), Bed::Vector3(1.0f)),
                                 Bed::StaticMesh("Assets/Resources/Meshes/Cube.obj"),
                                 Bed::PlayerController());

    uint64_t Camera = ecs.CreateEntity();
    ecs.AttachComponents(Camera, Bed::Transform(Bed::Vector3(0.0f, 5.0f, -5.0f), Bed::Vector3(0.0f), Bed::Vector3(1.0f)),
                                 Bed::Camera(Bed::ProjectionType::Perspective));

    uint64_t Ent1 = ecs.CreateEntity();
    ecs.AttachComponents(Ent1, Bed::Transform(Bed::Vector3(-2.5f, 0.0f, 5.0f), Bed::Vector3(0.0f), Bed::Vector3(1.0f)),
                               Bed::StaticMesh("Assets/Resources/Meshes/Cube.obj"));

    uint64_t Ent2 = ecs.CreateEntity();
    ecs.AttachComponents(Ent2, Bed::Transform(Bed::Vector3(2.5f, 0.0f, 5.0f), Bed::Vector3(0.0f), Bed::Vector3(1.0f)),
                               Bed::StaticMesh("Assets/Resources/Meshes/Cube.obj"));

    uint64_t floor = ecs.CreateEntity();
    ecs.AttachComponents(floor, Bed::Transform(Bed::Vector3(0.0f, -2.5f, 5.0f), Bed::Vector3(0.0f), Bed::Vector3(20.0f, 0.5f, 20.0f)),
                               Bed::StaticMesh("Assets/Resources/Meshes/Cube.obj"));

    uint64_t Ambient = ecs.CreateEntity();
    ecs.AttachComponents(Ambient, Bed::AmbientLight());

    uint64_t Directional = ecs.CreateEntity();
    ecs.AttachComponents(Directional, DirectionalLight(Bed::Vector3(1.0f, 1.0f, 1.0f), Bed::Vector3(0.0f, -1.0f, 1.0f), 0.5f));

    uint64_t Spot = ecs.CreateEntity();
    ecs.AttachComponents(Spot, Bed::Transform(Bed::Vector3(0.0f, 3.0f, 5.0f), Bed::Vector3(0.0f), Bed::Vector3(1.0f)),
                                Bed::SpotLight(Bed::Vector3(1.0f, 0.0f, 0.0f), Bed::Vector3(0.0f, -1.0f, 0.0f), 1.0f, 28.0f, 30.0f, 2.0f));

    uint64_t Point1 = ecs.CreateEntity();
    ecs.AttachComponents(Point1, Bed::Transform(Bed::Vector3(0.0f, 0.0f, 3.0f), 0.0f, 1.0f),
                                Bed::PointLight(1.0f, 1.0f, 1.0f));

    uint64_t Point2 = ecs.CreateEntity();
    ecs.AttachComponents(Point2, Bed::Transform(Bed::Vector3(-2.5f, 0.0f, 3.0f), 0.0f, 1.0f),
                                Bed::PointLight(Bed::Vector3(0.11f, 0.8f, 0.6f), 1.0f, 1.0f));

    uint64_t Point3 = ecs.CreateEntity();
    ecs.AttachComponents(Point3, Bed::Transform(Bed::Vector3(2.5f, 0.0f, 3.0f), 0.0f, 1.0f),
                                Bed::PointLight(Bed::Vector3(0.2f, 0.0f, 1.0f), 1.0f, 1.0f));

    ecs.AddSystem(Bed::PlayerControllerSystem);
    ecs.AddSystem(Bed::MovementSystem);
    ecs.AddSystem(Bed::StaticMeshSystem);
    ecs.AddSystem(Bed::AmbientLightSystem);
    ecs.AddSystem(Bed::PointLightSystem);
    ecs.AddSystem(Bed::SpotLightSystem);
    ecs.AddSystem(Bed::DirectionalLightSystem);
    ecs.AddSystem(Bed::CameraSystem);*/
}

void Bed::World::Update(float deltaTime)
{
    ecs.UpdateSystems(deltaTime);
}