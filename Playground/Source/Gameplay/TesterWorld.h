#pragma once

#include <Bed/Game/Game.h>
#include <SleepTrace.h>

#include <Transform.h>
#include <Components/Input/Input.h>
#include <Components/Renderer/Sprite.h>
#include <Components/Material/Texture.h>
#include <PhysicsObject.h>
#include <Components/Tag/PlayerTag.h>
#include <Components/Camera.h>

#include <Systems/Input/InputSystem.h>
#include <Systems/Renderer/SpriteSystem.h>
#include "Systems/SpawnerSystem.h"
#include <Bed/Game/GameObjects/Systems/PlayerControllerSystem.h>
#include <Bed/Game/GameObjects/Systems/TwoPlayerControllerSystem.h>


/*
#include <NonEuclidean/Hyperbolic.h>

#include <Graphics/TextureAsset.h>
#include <Components/Lighting/AmbientLight.h>
#include <Components/Lighting/DirectionalLight.h>
#include <Components/Lighting/PointLight.h>
#include <Components/Lighting/SpotLight.h>
#include <Components/Collision/AABBCollision.h>
#include <Components/Collision/Clickable.h>
#include <Components/Material/SubTexture.h>
#include <Components/Material/Material.h>
#include <Components/Enviroment/Fog.h>
#include <Components/Tag/EnemyTag.h>
#include <Components/Renderer/UIElement.h>
#include <Components/Renderer/StaticMesh.h>
#include <Components/UI/Anchor.h>
#include <Components/Utility/Timer.h>

#include <Bed/Game/GameObjects/Components/Material/TileMap.h>
#include <Bed/Game/GameObjects/Systems/Material/TileMapSystem.h>

#include "Components/Tags/Tag.h"

#include <Systems/CameraSystem.h>
#include <Systems/Lighting/AmbientLightSystem.h>
#include <Systems/Lighting/DirectionalLightSystem.h>
#include <Systems/Lighting/PointLightSystem.h>
#include <Systems/Lighting/SpotLightSystem.h>
#include <Systems/Collision/AABBCollisionSystem.h>
#include <Systems/Material/TextureSystem.h>
#include <Systems/Material/SubTextureSystem.h>
#include <Systems/Material/MaterialSystem.h>
#include <Systems/Enviroment/FogSystem.h>
#include <Systems/Renderer/UISystem.h>
#include <Systems/Renderer/StaticMeshSystem.h>
#include <Systems/Collision/ClickableSystem.h>
#include <Systems/Utility/TimerSystem.h>
#include <Bed/Game/GameObjects/Systems/Tests/AnimTestSystem.h>

#include "Systems/Tests/TestCollisionSystem.h"*/

namespace Test
{
    class TestWorld : public Bed::Game
    {
    protected:
        virtual void BeginPlay() override {

            Bed::SpriteRenderer spriteRenderer;

            GetECS().RegisterOnComponentAttachedGlobal<Pillow::Transform, Bed::Sprite>(
                [&spriteRenderer](Bed::World& world, uint64_t entity) 
                {
                    spriteRenderer.OnSpriteComponentAttached(world, entity);
                }
            );
            GetECS().RegisterOnComponentRemovedGlobal<Pillow::Transform, Bed::Sprite>(
                [&spriteRenderer](Bed::World& world, uint64_t entity) 
                {
                    spriteRenderer.OnSpriteComponentRemoved(world, entity);
                }
            );

            /*std::vector<int> map = { 0, 0, 0, 0, 1, 1, 1, 2, 2, 2,
                             0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 
                             0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
                             4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                             0, 0, 0, 0, 1, 1, 1, 5, 5, 5,
                             0, 0, 0, 0, 1, 1, 1, 2, 2, 2,
                             0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 
                             0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
                             4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                             0, 0, 0, 0, 1, 1, 1, 5, 5, 5};*/

            //World 1
            uint64_t world1 = GetECS().CreateWorld();

            uint64_t PlayerOne = GetECS().CreateEntity(world1);
            GetECS().AttachComponents(world1, PlayerOne, Bed::Sprite(), 
                                                        Pillow::Transform(Pillow::Vector3f(-1.5f, 0.0f, 0.0f), Pillow::Vector3f(0.0f, 0.0f, 0.0f), Pillow::Vector3f(1.0f, 1.0f, 1.0f)),
                                                        Bed::Input(),
                                                        Bed::PlayerOneTag(),
                                                        Mattress::PhysicsObject(),
                                                        Bed::Texture("Assets/Resources/Textures/LittleGuy.png"));

            uint64_t PlayerOneCam = GetECS().CreateEntity(world1);
            GetECS().AttachComponents(world1, PlayerOneCam, Pillow::Transform(Pillow::Vector3f(-1.5f, 0.0f, -5.0f), Pillow::Vector3f(0.0f, 0.0f, 0.0f), Pillow::Vector3f(1.0f, 1.0f, 1.0f)),
                                                        Bed::Input(),
                                                        Bed::PlayerOneTag(),
                                                        Mattress::PhysicsObject(),
                                                        Bed::Camera(0.0f, 0.0f, 0.5f, 1.0f));

            uint64_t PlayerTwo = GetECS().CreateEntity(world1);
            GetECS().AttachComponents(world1, PlayerTwo, Bed::Sprite(), 
                                                        Pillow::Transform(Pillow::Vector3f(1.5f, 0.0f, 0.0f), Pillow::Vector3f(0.0f, 0.0f, 0.0f), Pillow::Vector3f(1.0f, 1.0f, 1.0f)),
                                                        Bed::Input(),
                                                        Bed::PlayerTwoTag(),
                                                        Mattress::PhysicsObject(),
                                                        Bed::Texture("Assets/Resources/Textures/LittleGuy.png"));

            uint64_t PlayerTwoCam = GetECS().CreateEntity(world1);
            GetECS().AttachComponents(world1, PlayerTwoCam, Pillow::Transform(Pillow::Vector3f(1.5f, 0.0f, -5.0f), Pillow::Vector3f(0.0f, 0.0f, 0.0f), Pillow::Vector3f(1.0f, 1.0f, 1.0f)),
                                                        Bed::Input(),
                                                        Bed::PlayerTwoTag(),
                                                        Mattress::PhysicsObject(),
                                                        Bed::Camera(0.5f, 0.0f, 0.5f, 1.0f)); 

            uint64_t MiniMapCam = GetECS().CreateEntity(world1);
            GetECS().AttachComponents(world1, MiniMapCam, Pillow::Transform(Pillow::Vector3f(0.0f, 0.0f, -5.0f), Pillow::Vector3f(0.0f, 0.0f, 0.0f), Pillow::Vector3f(1.0f, 1.0f, 1.0f)),
                                                        Bed::Camera(0.375f, 0.75f, 0.25f, 0.25f));

            uint64_t TestEnt2 = GetECS().CreateEntity(world1);
            GetECS().AttachComponents(world1, TestEnt2, Bed::Sprite(), 
                                                        Pillow::Transform(-2.0f, 0.0f, 2.0f),
                                                        Bed::Texture("Assets/Resources/Textures/BedEngineLogo.png"));

            uint64_t TestEnt3 = GetECS().CreateEntity(world1);
            GetECS().AttachComponents(world1, TestEnt3, Bed::Sprite(), 
                                                        Pillow::Transform(2.0f, 0.0f, 1.5f),
                                                        Bed::Texture("Assets/Resources/Textures/SpriteTest.png"));

            GetECS().AddSystem(world1, Bed::InputSystem);
            GetECS().AddSystem(world1, 
                [&spriteRenderer](Bed::World& world) {
                    spriteRenderer.SpriteSystem(world);
                }
            );
            GetECS().AddSystem(world1, Bed::TwoPlayerControllerSystem);
            GetECS().AddSystem(world1, SpawnerSystem);

            /*
            //uint64_t w1Map = m_ecs.CreateEntity(world1);
            //m_ecs.AttachComponents(world1, w1Map, Bed::Transform(0.0f, 0.0f, 1.0f),
            //                                        Bed::Texture("Assets/Resources/Textures/SpriteTest.png"),
            //                                        Bed::TileMap(map));

            uint64_t w1Sprite = m_ecs.CreateEntity(world1);
            m_ecs.AttachComponents(world1, w1Sprite, Bed::Transform(Pillow::Vector3f(0.0f, 0.0f, 0.0f), Pillow::Vector3f(0.0f), Pillow::Vector3f(1.0f)),
                                                Bed::Sprite(),
                                                Bed::Texture("Assets/Resources/Textures/LittleGuy.png", Bed::TextureFiltering::Nearest),
                                                Bed::SubTexture(),
                                                Bed::Timer(0.5f, true, true),
                                                Bed::EnemyTag());

            uint64_t w1Logo = m_ecs.CreateEntity(world1);
            m_ecs.AttachComponents(world1, w1Logo, Bed::Transform(Pillow::Vector3f(0.0f, 0.0f, 0.0f), Pillow::Vector3f(0.0f), Pillow::Vector3f(0.4f)),
                                                    Bed::UIElement(),
                                                    Bed::Texture("Assets/Resources/Textures/BedEngineLogo.png"),
                                                    Bed::Anchor(Pillow::Vector2f(0.07f, 0.1f)));

            uint64_t w1Hud1 = m_ecs.CreateEntity(world1);
            m_ecs.AttachComponents(world1, w1Hud1, Bed::Transform(Pillow::Vector3f(0.0f, 0.0f, 0.0f), Pillow::Vector3f(0.0f), Pillow::Vector3f(0.3f)),
                                                    Bed::UIElement(),
                                                    Bed::Texture("Assets/Resources/Textures/256xMissingTexture.png"),
                                                    Bed::Clickable(),
                                                    Bed::Anchor(Pillow::Vector2f(0.35f, 0.5f)),
                                                    Bed::Input(),
                                                    Test::RemoveEntityTag());

            uint64_t w1Hud2 = m_ecs.CreateEntity(world1);
            m_ecs.AttachComponents(world1, w1Hud2, Bed::Transform(Pillow::Vector3f(0.0f, 0.0f, 0.0f), Pillow::Vector3f(0.0f), Pillow::Vector3f(0.3f)),
                                                    Bed::UIElement(),
                                                    Bed::Texture("Assets/Resources/Textures/TestBedEngineIcon.png"),
                                                    Bed::Clickable(),
                                                    Bed::Anchor(Pillow::Vector2f(0.7f, 0.5f)),
                                                    Bed::Input(),
                                                    Test::AddEntityTag());

            uint64_t w1Player = m_ecs.CreateEntity(world1);
            m_ecs.AttachComponents(world1, w1Player, Bed::Transform(Pillow::Vector3f(0.0f, 0.0f, 5.0f), Pillow::Vector3f(0.0f), Pillow::Vector3f(1.0f)),
                                                    Bed::StaticMesh("Assets/Resources/Meshes/Cube.obj"),
                                                    Bed::Texture("Assets/Resources/Textures/TestBedEngineIcon.png"),
                                                    Bed::Input(),
                                                    Bed::PlayerTag(),
                                                    Mattress::PhysicsObject(),
                                                    Bed::AABBCollision(-1.0f, 1.0f));
                                                
            uint64_t w1Camera = m_ecs.CreateEntity(world1);
            m_ecs.AttachComponents(world1, w1Camera, Bed::Transform(Pillow::Vector3f(0.0f, 5.0f, -5.0f), Pillow::Vector3f(0.0f), Pillow::Vector3f(1.0f)),
                                                        Bed::Camera(Bed::ProjectionType::Perspective),
                                                        Bed::Input(),
                                                        Mattress::PhysicsObject());

            uint64_t w1Ent1 = m_ecs.CreateEntity(world1);
            m_ecs.AttachComponents(world1, w1Ent1, Bed::Transform(Pillow::Vector3f(-2.5, 0.0, 5.0), Pillow::Vector3f(0.0f), Pillow::Vector3f(1.0f)),
                                                    Bed::StaticMesh("Assets/Resources/Meshes/Cube.obj"),
                                                    Bed::Texture("Assets/Resources/Textures/256xMissingTexture.png"),
                                                    Bed::AABBCollision(-1.0f, 1.0f),
                                                    Bed::EnemyTag());

            uint64_t w1Ent2 = m_ecs.CreateEntity(world1);
            m_ecs.AttachComponents(world1, w1Ent2, Bed::Transform(Pillow::Vector3f(2.5, 0.0, 5.0), Pillow::Vector3f(0.0f), Pillow::Vector3f(1.0f)),
                                                    Bed::StaticMesh("Assets/Resources/Meshes/Cube.obj"),
                                                    Bed::Texture("Assets/Resources/Textures/256xMissingTexture.png"),
                                                    Bed::AABBCollision(-1.0f, 1.0f),
                                                    Bed::EnemyTag());

            uint64_t w1Floor = m_ecs.CreateEntity(world1);
            m_ecs.AttachComponents(world1, w1Floor, Bed::Transform(Pillow::Vector3f(0.0, -2.5, 5.0), Pillow::Vector3f(0.0f), Pillow::Vector3f(50.0, 0.5, 50.0)),
                                                    Bed::StaticMesh("Assets/Resources/Meshes/Cube.obj"),
                                                    Bed::Texture("Assets/Resources/Textures/256xWhite.png"));

            uint64_t w1Fog = m_ecs.CreateEntity(world1);
            m_ecs.AttachComponents(world1, w1Fog, Bed::Fog(Bed::Colour3(0.0f, 0.0f, 0.0f), 10.0f, 45.0f));
                                                
            uint64_t w1Ambient = m_ecs.CreateEntity(world1);
            m_ecs.AttachComponents(world1, w1Ambient, Bed::AmbientLight());
            
            uint64_t w1Directional = m_ecs.CreateEntity(world1);
            m_ecs.AttachComponents(world1, w1Ambient, Bed::DirectionalLight(Bed::Colour3(1.0f, 1.0f, 1.0f), Pillow::Vector3f(0.0f, -1.0f, 1.0f), 0.5f));

            uint64_t w1Spot = m_ecs.CreateEntity(world1);
            m_ecs.AttachComponents(world1, w1Spot, Bed::Transform(Pillow::Vector3f(0.0f, 3.0f, 5.0f), Pillow::Vector3f(0.0f), Pillow::Vector3f(1.0f)),
                                        Bed::SpotLight(Bed::Colour3(1.0f, 0.0f, 0.0f), Pillow::Vector3f(0.0f, -1.0f, 0.0f), 1.0f, 28.0f, 30.0f, 2.0f));

            uint64_t w1Point1 = m_ecs.CreateEntity(world1);
            m_ecs.AttachComponents(world1, w1Point1, Bed::Transform(Pillow::Vector3f(0.0f, 0.0f, 3.0f), 0.0f, 1.0f),
                                        Bed::PointLight(1.0f, 1.0f, 1.0f));

            uint64_t w1Point2 = m_ecs.CreateEntity(world1);
            m_ecs.AttachComponents(world1, w1Point2, Bed::Transform(Pillow::Vector3f(-2.5f, 0.0f, 3.0f), 0.0f, 1.0f),
                                        Bed::PointLight(Bed::Colour3(0.11f, 0.8f, 0.6f), 1.0f, 1.0f));

            uint64_t w1Point3 = m_ecs.CreateEntity(world1);
            m_ecs.AttachComponents(world1, w1Point3, Bed::Transform(Pillow::Vector3f(2.5f, 0.0f, 3.0f), 0.0f, 1.0f),
                                        Bed::PointLight(Bed::Colour3(0.2f, 0.0f, 1.0f), 1.0f, 1.0f));

            m_ecs.AddSystem(world1, Bed::InputSystem);
            m_ecs.AddSystem(world1, Bed::ClickableSystem);
            m_ecs.AddSystem(world1, Bed::CameraSystem);
            m_ecs.AddSystem(world1, Bed::TextureSystem);
            m_ecs.AddSystem(world1, Bed::SubTextureSystem);
            m_ecs.AddSystem(world1, Bed::TileMapSystem);
            m_ecs.AddSystem(world1, Bed::UISystem);
            m_ecs.AddSystem(world1, Bed::StaticMeshSystem);
            m_ecs.AddSystem(world1, Bed::FogSystem);
            m_ecs.AddSystem(world1, Bed::AmbientLightSystem);
            m_ecs.AddSystem(world1, Bed::SpotLightSystem);
            m_ecs.AddSystem(world1, Bed::PointLightSystem);
            m_ecs.AddSystem(world1, Bed::DirectionalLightSystem);
            m_ecs.AddSystem(world1, Bed::AABBCollisionSystem);
            m_ecs.AddSystem(world1, Bed::TimerSystem);
            m_ecs.AddSystem(world1, Test::CollisionEnterTestSystem);
            m_ecs.AddSystem(world1, Test::CollisionExitTestSystem);
            m_ecs.AddSystem(world1, Test::CollisionStayTestSystem);
            m_ecs.AddSystem(world1, Test::ClickableHoverTest);
            m_ecs.AddSystem(world1, Test::ClickableUnhoveredTest);
            m_ecs.AddSystem(world1, Test::ClickableClickedTest);
            m_ecs.AddSystem(world1, Test::ClickableReleasedTest);
            m_ecs.AddSystem(world1, Bed::AnimTestSystem);
            */
            

            //Pillow::Mat4f mat = Pillow::Mat4f::Identity();
            //LOG_TRACE("Test Mat: " + mat.ToString());

            //World 2
            /*uint64_t world2 = m_ecs.CreateWorld();

            uint64_t w2ent1 = m_ecs.CreateEntity(world2);
            m_ecs.AttachComponents(world2, w2ent1, Bed::Transform(Bed::Vector3(2.5, 0.0, 10.0), Bed::Vector3(0.0f), Bed::Vector3(1.0f)),
                                                Bed::StaticMesh("Assets/Resources/Meshes/Cube.obj"));

            m_ecs.AddSystem(world2, Bed::StaticMeshSystem);*/
        };
    };
}