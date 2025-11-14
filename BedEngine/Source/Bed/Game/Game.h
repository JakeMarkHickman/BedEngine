#pragma once

#include "GameSession/GameSession.h"
#include <Bed/ECS/ECS.h>

#include <iostream>

//This file will not be able to be edited. This is an overhead for worlds and events can be sent between game session and world
namespace Bed
{
    class Game
    {
    public:
        Game();
        ~Game() {};

        Bed::GameSession GetGameSession() { return m_GameSession; };

        Bed::ECS& GetECS() { return m_ecs; };

        virtual void BeginPlay() {};
        void Update();

        std::unordered_map<uint64_t, Bed::World*>& GetActiveWorlds() { return m_ecs.GetActiveWorlds(); };

    protected:

        Bed::ECS m_ecs;

    private:
        Bed::GameSession m_GameSession;
    };
}