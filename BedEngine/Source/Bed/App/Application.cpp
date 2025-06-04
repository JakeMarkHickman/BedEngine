
#include "Application.h"

#include <Platforms/PlatformFactory.h>
#include <Platforms/WindowFactory.h>

namespace Bed
{
    void Application::Run()
    {
        m_Platform = Bed::PlatformFactory::CreatePlatform(GraphicsAPI::OpenGL);
        m_Window = Bed::WindowFactory::CreatePlatform(m_Platform);

        //TODO: make a system to automatically recognise monitor size and scale correctly
        if(!m_Window->CreateWindow(800, 450, m_ApplicationName)) // Check to make sure the Window is created
        {
            return; // Return if the Window wasnt created
        }

        Update();
    }

    void Application::Update()
    {
        //TODO: This needs to be better
        //Bed::ContextRegistry& instance = Bed::ContextRegistry::GetInstance();

        m_Game->BeginPlay();
        
        //Game Loop
        while (m_Window->IsWindowOpen())
        {
            m_Time.CalculateDeltaTime();

            m_Game->Update(); //Game update

            /*
                TODO: figure out some way of making Fixed time loop for all worlds at once
                Options:
                    Have a clock that checks inside the physics system
                        Mattress::Physics::Tick();

                    A global clock for the whole engine
                        m_Time.GetFixedTime();

                    Have the loop below inside of the physics system and worlds are added into the manager
                    from the ECS that way its a one function call
            */
            for(auto& world : m_Game->GetActiveWorlds())
            {
                world.second->GetWorldPhysics().Step(Time::GetDeltaTime()); //Physics update
            }

            m_Window->UpdateWindow(); // Update the platform App
        }
        
        m_Window->CloseWindow(); // Close the window
    } 
}