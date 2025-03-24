#pragma once

#include <iostream>
#include <Bed/ECS/ECS.h>
#include <Bed/Tools/JsonRW.h>

//This will load a level from a file (JSON for now but binary later)
namespace Bed
{
    class World
    {
    public:
        World();
        ~World();

        bool LoadWorld(std::string path);
        bool UnloadWorld();

        bool IsWorldLoaded();

        void BeginPlay();
        void Update();

    private:
        std::string m_LoadedWorldName;
        Bed::ECS ecs;
    };
}