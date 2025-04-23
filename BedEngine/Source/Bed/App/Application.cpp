
#include "Application.h"
#include <Platforms/PlatformWrapper.h>

namespace Bed
{
    void Application::Run()
    {
        //TODO: make a system to automatically recognise monitor size and scale correctly
        if(!CreateWindow(800, 550, m_ApplicationName, GraphicsAPI::OpenGL)) // Check to make sure the Window is created
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
        while (IsWindowOpen())
        {
            m_Time.CalculateDeltaTime();

            //std::cout << Time::GetDeltaTime() << "\n";

            m_Game.Update();
            UpdateWindow(); // Update the platform App
        }
        
        CloseWindow(); // Close the window
    } 
}