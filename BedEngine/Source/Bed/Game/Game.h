#pragma once

#include "GameSession/GameSession.h"
#include <Bed/ECS/ECS.h>

#include <iostream>

#include <Math/Transform.h>
#include <Components/Camera.h>
#include <Components/StaticMesh.h>

//#include <Systems/CameraSystem.h>
#include <Systems/StaticMeshSystem.h>

//This file will not be able to be edited. This is an overhead for worlds and events can be sent between game session and world
namespace Bed
{
    class Game
    {
    public:
        Game() {
            //m_World.LoadWorld("Assets/Worlds/TestWorld.world");
            uint64_t world1 = m_ecs.CreateWorld();
            uint64_t w1ent1 = m_ecs.CreateEntity(world1);
            m_ecs.AttachComponents(world1, w1ent1, Bed::Transform(Bed::Vector3(0.0f, 0.0f, 5.0f), Bed::Vector3(0.0f), Bed::Vector3(1.0f)),
                                                   Bed::StaticMesh("Assets/Resources/Meshes/Cube.obj"));
            uint64_t w1ent2 = m_ecs.CreateEntity(world1);
            m_ecs.AttachComponents(world1, w1ent1, Bed::Transform(Bed::Vector3(0.0f, 5.0f, -5.0f), Bed::Vector3(0.0f), Bed::Vector3(1.0f)),
                                                   Bed::Camera(Bed::ProjectionType::Perspective));

            uint64_t world2 = m_ecs.CreateWorld();
            uint64_t w2ent1 = m_ecs.CreateEntity(world2);
            uint64_t w2ent2 = m_ecs.CreateEntity(world2);

            //m_ecs.AddSystem(world1, Bed::CameraSystem);
            m_ecs.AddSystem(world1, Bed::StaticMeshSystem);

            std::cout << world1 << ": world ID. " << w1ent2 << ": EntityID\n";
            std::cout << world2 << ": world ID. " << w2ent1 << ": EntityID\n";
        };
        ~Game() {};

        //std::string GetCurrentLoadedWorld() { return "m_World"; };
        Bed::GameSession GetGameSession() { return m_GameSession; };

        void Update() { m_ecs.UpdateSystems(); };

    private:
        Bed::GameSession m_GameSession;
        Bed::ECS m_ecs;
    };
}