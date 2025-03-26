#include "Game.h"

#include <Math/Transform.h>
#include <Components/Camera.h>
#include <Components/StaticMesh.h>
#include <Components/LightSources/AmbientLight.h>
#include <Components/LightSources/DirectionalLight.h>

#include <Systems/CameraSystem.h>
#include <Systems/StaticMeshSystem.h>
#include <Systems/LightSources/AmbientLightSystem.h>
#include <Systems/LightSources/DirectionalLightSystem.h>



Bed::Game::Game()
{
    //World 1
    uint64_t world1 = m_ecs.CreateWorld();
    uint64_t w1Player = m_ecs.CreateEntity(world1);
    m_ecs.AttachComponents(world1, w1Player, Bed::Transform(Bed::Vector3(0.0f, 0.0f, 5.0f), Bed::Vector3(0.0f), Bed::Vector3(1.0f)),
                                           Bed::StaticMesh("Assets/Resources/Meshes/Cube.obj"));
                                        
    uint64_t w1Camera = m_ecs.CreateEntity(world1);
    m_ecs.AttachComponents(world1, w1Camera, Bed::Transform(Bed::Vector3(0.0f, 5.0f, -5.0f), Bed::Vector3(0.0f), Bed::Vector3(1.0f)),
                                           Bed::Camera(Bed::ProjectionType::Perspective));

    uint64_t w1Ambient = m_ecs.CreateEntity(world1);
    m_ecs.AttachComponents(world1, w1Ambient, Bed::AmbientLight());
    
    uint64_t w1Directional = m_ecs.CreateEntity(world1);
    m_ecs.AttachComponents(world1, w1Ambient, DirectionalLight(Bed::Vector3(1.0f, 1.0f, 1.0f), Bed::Vector3(0.0f, -1.0f, 1.0f), 0.5f));

    m_ecs.AddSystem(world1, Bed::CameraSystem);
    m_ecs.AddSystem(world1, Bed::StaticMeshSystem);
    m_ecs.AddSystem(world1, Bed::AmbientLightSystem);
    m_ecs.AddSystem(world1, Bed::DirectionalLightSystem);


    //World 2
    uint64_t world2 = m_ecs.CreateWorld();
    uint64_t w2ent1 = m_ecs.CreateEntity(world2);
    uint64_t w2ent2 = m_ecs.CreateEntity(world2);
}

void Bed::Game::Update() 
{ 
    m_ecs.UpdateSystems();
};