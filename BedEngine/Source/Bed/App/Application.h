#pragma once

#include "Time.h"

#include <Bed/Core.h>
#include <Bed/Game/Game.h>

//Physics
#include <PhysicsWorld.h>

//Renderer
#include <Duvet.h>

#include <Platforms/Platform.h>
#include <Platforms/Window.h>

namespace Bed
{   
    class BED_API Application
    {
    public:
        void Run();

        void SetApplicationName(const char* name)
        {
            if(name != m_ApplicationName)
            {
                m_ApplicationName = name;
            }
        };

        void SetWindowIcon(const char* path)
        {
            if(path != m_WindowIcon)
            {
                m_WindowIcon = path;
            }
        };

        //TODO: This is just a test for now to develop first game!
        void SetGame(Bed::Game* game)
        {
            m_Game = game;
        }

        const char* GetApplicationName()
        {
            return m_ApplicationName;
        };


    protected:
        // TODO: Add variables that are able to be modified to 
        const char* m_ApplicationName = "Bed Engine";
        const char* m_WindowIcon = "Assets/Resources/Textures/BedEngineLogo.png";

        /*TODO: Game Hierarchy
            App
                Game
                    Game Session [Can be Edited] (data persistance, current session of game)
                    Level [Can be Edited] (the game world, also uses level streaming)
                        Level Manager [Can be Edited] (controls spawning, Data loading, basic level stuff)
        */

    private:
        void Update();

        Bed::Time m_Time;
        Bed::Game* m_Game = nullptr;
        //Quilt::Duvet m_Renderer;

        Bed::Platform* m_Platform = nullptr;
        Bed::Window* m_Window = nullptr;
    }; 

    Application* CreateApplication();
    

}