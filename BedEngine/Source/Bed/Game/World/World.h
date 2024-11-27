#pragma once

//This will load a level from a file (JSON for now but binary later)
namespace Bed
{
    class World
    {
    public:
        World() {};
        ~World() {};

        void LoadWorld(std::string path);

        void BeginPlay() {};
        void Update(float deltaTime) {};
    };
}