#include "Game.h"

#include <Math/Colour.h>

#include <Math/Transform.h>
#include <Components/Input/Input.h>
#include <Components/Camera.h>
#include <Components/StaticMesh.h>
#include <Components/Lighting/AmbientLight.h>
#include <Components/Lighting/DirectionalLight.h>
#include <Components/Lighting/PointLight.h>
#include <Components/Lighting/SpotLight.h>
#include <Components/Collision/AABBCollision.h>
#include <Components/Collision/Clickable.h>
#include <Components/Material/Texture.h>
#include <Components/Material/Material.h>
#include <Components/Enviroment/Fog.h>
#include <Components/Tag/PlayerTag.h>
#include <Components/Tag/EnemyTag.h>

#include <Bed/Game/GameObjects/Components/UI/UIElement.h>
#include <Bed/Game/GameObjects/Components/UI/Anchor.h>

#include <Systems/Input/InputSystem.h>
#include <Systems/CameraSystem.h>
#include <Systems/StaticMeshSystem.h>
#include <Systems/Lighting/AmbientLightSystem.h>
#include <Systems/Lighting/DirectionalLightSystem.h>
#include <Systems/Lighting/PointLightSystem.h>
#include <Systems/Lighting/SpotLightSystem.h>
#include <Systems/Collision/AABBCollisionSystem.h>
#include <Systems/Material/TextureSystem.h>
#include <Systems/Material/MaterialSystem.h>
#include <Systems/Enviroment/FogSystem.h>
#include <Systems/UI/UISystem.h>
#include <Systems/Collision/ClickableSystem.h>
#include <Bed/Game/GameObjects/Systems/PlayerControllerSystem.h>
#include <Bed/Game/GameObjects/Systems/MovementSystem.h>
#include <Bed/Game/GameObjects/Systems/Tests/CollisionTestSystem.h>


Bed::Game::Game()
{
    //World 1
    uint64_t world1 = m_ecs.CreateWorld();

    uint64_t w1Hud1 = m_ecs.CreateEntity(world1);
    m_ecs.AttachComponents(world1, w1Hud1, Bed::Transform(Bed::Vector3(0.0f, 0.0f, 0.0f), Bed::Vector3(0.0f), Bed::Vector3(0.1f)),
                                        Bed::UIElement(),
                                        Bed::Anchor(0.0f),
                                        Bed::Texture("Assets/Resources/Textures/256xWhite.png"));

    uint64_t w1Hud2 = m_ecs.CreateEntity(world1);
    m_ecs.AttachComponents(world1, w1Hud2, Bed::Transform(Bed::Vector3(0.0f, 0.0f, 0.0f), Bed::Vector3(0.0f), Bed::Vector3(0.1f)),
                                        Bed::UIElement(),
                                        Bed::Texture("Assets/Resources/Textures/256xMissingTexture.png"),
                                        Bed::Clickable(),
                                        Bed::Anchor(Bed::Vector2(0.7f, 0.4f)),
                                        Bed::Input(),
                                        Bed::EnemyTag());

    uint64_t w1Player = m_ecs.CreateEntity(world1);
    m_ecs.AttachComponents(world1, w1Player, Bed::Transform(Bed::Vector3(0.0f, 0.0f, 5.0f), Bed::Vector3(0.0f), Bed::Vector3(1.0f)),
                                        Bed::StaticMesh("Assets/Resources/Meshes/Cube.obj"),
                                        Bed::Texture("Assets/Resources/Textures/TestBedEngineIcon.png"),
                                        Bed::Input(),
                                        Bed::PlayerTag(),
                                        Bed::AABBCollision(-1.0f, 1.0f));
                                        
    uint64_t w1Camera = m_ecs.CreateEntity(world1);
    m_ecs.AttachComponents(world1, w1Camera, Bed::Transform(Bed::Vector3(0.0f, 5.0f, -5.0f), Bed::Vector3(0.0f), Bed::Vector3(1.0f)),
                                           Bed::Camera(Bed::ProjectionType::Perspective),
                                           Bed::Input(),
                                           Bed::PlayerTag());

    uint64_t w1Ent1 = m_ecs.CreateEntity(world1);
    m_ecs.AttachComponents(world1, w1Ent1, Bed::Transform(Bed::Vector3(-2.5, 0.0, 5.0), Bed::Vector3(0.0f), Bed::Vector3(1.0f)),
                                             Bed::StaticMesh("Assets/Resources/Meshes/Cube.obj"),
                                             Bed::Texture("Assets/Resources/Textures/256xMissingTexture.png"),
                                             Bed::AABBCollision(-1.0f, 1.0f),
                                             Bed::EnemyTag());

    uint64_t w1Ent2 = m_ecs.CreateEntity(world1);
    m_ecs.AttachComponents(world1, w1Ent2, Bed::Transform(Bed::Vector3(2.5, 0.0, 5.0), Bed::Vector3(0.0f), Bed::Vector3(1.0f)),
                                           Bed::StaticMesh("Assets/Resources/Meshes/Cube.obj"),
                                           Bed::Texture("Assets/Resources/Textures/256xMissingTexture.png"),
                                           Bed::AABBCollision(-1.0f, 1.0f),
                                           Bed::EnemyTag());

    uint64_t w1Floor = m_ecs.CreateEntity(world1);
    m_ecs.AttachComponents(world1, w1Floor, Bed::Transform(Bed::Vector3(0.0, -2.5, 5.0), Bed::Vector3(0.0f), Bed::Vector3(50.0, 0.5, 50.0)),
                                           Bed::StaticMesh("Assets/Resources/Meshes/Cube.obj"),
                                           Bed::Texture("Assets/Resources/Textures/256xWhite.png")/*,
                                           Bed::AABBCollision(-20.0f, 20.0f)*/);

    uint64_t w1Fog = m_ecs.CreateEntity(world1);
    m_ecs.AttachComponents(world1, w1Fog, Bed::Fog(Bed::Colour3(0.0f, 0.0f, 0.0f), 10.0f, 45.0f));
                                        
    uint64_t w1Ambient = m_ecs.CreateEntity(world1);
    m_ecs.AttachComponents(world1, w1Ambient, Bed::AmbientLight());
    
    uint64_t w1Directional = m_ecs.CreateEntity(world1);
    m_ecs.AttachComponents(world1, w1Ambient, DirectionalLight(Bed::Colour3(1.0f, 1.0f, 1.0f), Bed::Vector3(0.0f, -1.0f, 1.0f), 0.5f));

    uint64_t w1Spot = m_ecs.CreateEntity(world1);
    m_ecs.AttachComponents(world1, w1Spot, Bed::Transform(Bed::Vector3(0.0f, 3.0f, 5.0f), Bed::Vector3(0.0f), Bed::Vector3(1.0f)),
                                Bed::SpotLight(Bed::Colour3(1.0f, 0.0f, 0.0f), Bed::Vector3(0.0f, -1.0f, 0.0f), 1.0f, 28.0f, 30.0f, 2.0f));

    uint64_t w1Point1 = m_ecs.CreateEntity(world1);
    m_ecs.AttachComponents(world1, w1Point1, Bed::Transform(Bed::Vector3(0.0f, 0.0f, 3.0f), 0.0f, 1.0f),
                                Bed::PointLight(1.0f, 1.0f, 1.0f));

    uint64_t w1Point2 = m_ecs.CreateEntity(world1);
    m_ecs.AttachComponents(world1, w1Point2, Bed::Transform(Bed::Vector3(-2.5f, 0.0f, 3.0f), 0.0f, 1.0f),
                                Bed::PointLight(Bed::Colour3(0.11f, 0.8f, 0.6f), 1.0f, 1.0f));

    uint64_t w1Point3 = m_ecs.CreateEntity(world1);
    m_ecs.AttachComponents(world1, w1Point3, Bed::Transform(Bed::Vector3(2.5f, 0.0f, 3.0f), 0.0f, 1.0f),
                                Bed::PointLight(Bed::Colour3(0.2f, 0.0f, 1.0f), 1.0f, 1.0f));

    m_ecs.AddSystem(world1, Bed::InputSystem);
    m_ecs.AddSystem(world1, Bed::ClickableSystem);
    m_ecs.AddSystem(world1, Bed::CameraSystem);
    m_ecs.AddSystem(world1, Bed::TextureSystem);
    m_ecs.AddSystem(world1, Bed::UISystem);
    m_ecs.AddSystem(world1, Bed::StaticMeshSystem);
    m_ecs.AddSystem(world1, Bed::FogSystem);
    m_ecs.AddSystem(world1, Bed::AmbientLightSystem);
    m_ecs.AddSystem(world1, Bed::SpotLightSystem);
    m_ecs.AddSystem(world1, Bed::PointLightSystem);
    m_ecs.AddSystem(world1, Bed::DirectionalLightSystem);
    m_ecs.AddSystem(world1, Bed::PlayerControllerSystem);
    m_ecs.AddSystem(world1, Bed::MovementSystem);
    m_ecs.AddSystem(world1, Bed::AABBCollisionSystem);
    m_ecs.AddSystem(world1, Bed::CollisionEnterTestSystem);
    m_ecs.AddSystem(world1, Bed::CollisionExitTestSystem);
    m_ecs.AddSystem(world1, Bed::CollisionStayTestSystem);
    m_ecs.AddSystem(world1, Bed::ClickableHoverTest);
    m_ecs.AddSystem(world1, Bed::ClickableUnhoveredTest);
    m_ecs.AddSystem(world1, Bed::ClickableClickedTest);
    m_ecs.AddSystem(world1, Bed::ClickableReleasedTest);
    
    //World 2
    uint64_t world2 = m_ecs.CreateWorld();

    uint64_t w2ent1 = m_ecs.CreateEntity(world2);
    m_ecs.AttachComponents(world2, w2ent1, Bed::Transform(Bed::Vector3(2.5, 0.0, 10.0), Bed::Vector3(0.0f), Bed::Vector3(1.0f))/*,
                                           Bed::StaticMesh("Assets/Resources/Meshes/Cube.obj")*/);

    m_ecs.AddSystem(world2, Bed::StaticMeshSystem);
}

void Bed::Game::Update() 
{ 
    m_ecs.UpdateSystems();
};