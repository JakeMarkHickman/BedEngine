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
#include <Systems/CameraSystem.h>
#include <Systems/Material/TextureSystem.h>
#include "Systems/SpawnerSystem.h"
#include <Bed/Game/GameObjects/Systems/PlayerControllerSystem.h>
#include <Bed/Game/GameObjects/Systems/TwoPlayerControllerSystem.h>

namespace Test
{
    class Game : public Bed::Game
    {
    protected:
        virtual void BeginPlay() override 
        {
            //GLOBAL
            Bed::SpriteSystems spriteSystems;
            GetECS().RegisterOnComponentAttachedGlobal<Pillow::Transform, Bed::Sprite>(spriteSystems, &Bed::SpriteSystems::OnSpriteComponentAttached);
            GetECS().RegisterOnComponentRemovedGlobal<Pillow::Transform, Bed::Sprite>(spriteSystems, &Bed::SpriteSystems::OnSpriteComponentRemoved);
            GetECS().AddSystemGlobal(spriteSystems, &Bed::SpriteSystems::SpriteSystem);

            Bed::CameraSystems cameraSystems;
            GetECS().RegisterOnComponentAttachedGlobal<Pillow::Transform, Bed::Camera>(cameraSystems, &Bed::CameraSystems::OnCameraComponentAttached);
            GetECS().RegisterOnComponentRemovedGlobal<Pillow::Transform, Bed::Camera>(cameraSystems, &Bed::CameraSystems::OnCameraComponentRemoved);

            Bed::TextureSystems textureSystems;
            GetECS().RegisterOnComponentAttachedGlobal<Bed::Texture>(textureSystems, &Bed::TextureSystems::OnTextureComponentAttached);
            GetECS().RegisterOnComponentRemovedGlobal<Bed::Texture>(textureSystems, &Bed::TextureSystems::OnTextureComponentRemoved);

            //WORLD 1
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
                                                        Bed::Texture("Assets/Resources/Textures/LittleGuyGBA.png"));

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
            GetECS().AddSystem(world1, Bed::TwoPlayerControllerSystem);
            GetECS().AddSystem(world1, SpawnerSystem);
        };
    };
}