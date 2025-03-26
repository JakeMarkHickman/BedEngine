#pragma once

#include <Bed/ECS/ECS.h>
#include <Bed/Tools/JsonRW.h>

//This will load a level from a file (JSON for now but binary later)
namespace Bed
{
    class WorldManager
    {
    public:
        ~WorldManager();

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