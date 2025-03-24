#pragma once

#include "GameSession/GameSession.h"
#include "World/World.h"

//This file will not be able to be edited. This is an overhead for worlds and events can be sent between game session and world
namespace Bed
{
    class Game
    {
    public:
        Game() {
            m_World.LoadWorld("Assets/Worlds/TestWorld.world");
        };
        ~Game() {};

        std::string GetCurrentLoadedWorld() { return "m_World"; };
        Bed::GameSession GetGameSession() { return m_GameSession; };

        void Update() { m_World.Update(); };

    private:
        Bed::GameSession m_GameSession;
        Bed::World m_World;
    };
}