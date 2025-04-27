
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
        
        //Game Loop
        while (m_Window->IsWindowOpen())
        {
            m_Time.CalculateDeltaTime();

            //std::cout << Time::GetDeltaTime() << "\n";

            m_Game.Update();
            m_Window->UpdateWindow(); // Update the platform App
        }
        
        m_Window->CloseWindow(); // Close the window
    } 
}