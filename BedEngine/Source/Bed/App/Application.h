#pragma once

#include "Time.h"

#include <Bed/Core.h>
#include <Bed/Game/Game.h>

#include <Platforms/Platform.h>
#include <Platforms/Window.h>

namespace Bed
{
    
    class BED_API Application
    {
    public:
        void Run();

        void SetApplicationName(const char* Name)
        {
            if(Name != m_ApplicationName)
            {
                m_ApplicationName = Name;
            }
        };

        const char* GetApplicationName()
        {
            return m_ApplicationName;
        };

    protected:
        // TODO: Add variables that are able to be modified to 
        const char* m_ApplicationName = "Bed Engine";

        /*TODO: Game Hierarchy
            App
                Game
                    Game Session [Can be Edited] (data persistance, current session of game)
                    Level [Can be Edited] (the game world, also uses level streaming)
                        Level Manager [Can be Edited] (controls spawning, Data loading, basic level stuff)
        */

    private:
        void Update();

        Bed::Game m_Game;
        Bed::Time m_Time;

        Bed::Platform* m_Platform = nullptr;
        Bed::Window* m_Window = nullptr;
    }; 

    Application* CreateApplication();
    

}