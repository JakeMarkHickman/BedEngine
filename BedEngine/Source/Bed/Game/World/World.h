#pragma once

#include <iostream>
#include <Bed/ECS/ECS.h>

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
        void Update(float deltaTime);

    private:
        Bed::ECS ecs;
    };
}