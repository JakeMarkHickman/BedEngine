
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
        //Game Loop
        while (IsWindowOpen())
        {
            m_Game.Update( 0.016f );
            
            UpdateWindow(); // Update the platform App
        }
        
        CloseWindow(); // Close the window
    } 
}