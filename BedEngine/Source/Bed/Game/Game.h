#pragma once

#include "GameSession/GameSession.h"
#include "World/World.h"

//This file will not be able to be edited. This is what will be used to deal with levels and the game session.
namespace Bed
{
    class Game
    {
    public:
        Game() {};
        ~Game() {};

        void LoadWorld(Bed::World* worldToLoad) { m_World = worldToLoad; };
        Bed::World* GetCurrentWorld() { return m_World; }

        void Update(float deltaTime) { m_World->Update(deltaTime); };

    private:
        Bed::GameSession* m_GameSession;
        Bed::World* m_World;
    };
}