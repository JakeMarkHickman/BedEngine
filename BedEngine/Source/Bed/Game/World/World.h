#pragma once

#include <iostream>
#include <Bed/ECS/ECS.h>
#include <Bed/Events/EventManager.h>

//TODO: DELETE
#include <Bed/Events/Event.h>

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

        void testEventFunc(std::string value);

    private:
        Bed::ECS ecs;

        Event<std::string> testEvent;
        Bed::EventManager worldEventManager;
    };
}