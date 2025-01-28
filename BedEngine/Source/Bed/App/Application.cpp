
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

        m_registry.RegisterContext(m_Game);

        Update();
    }

    void Application::Update()
    {
        //Game Loop
        while (IsWindowOpen())
        {
            float delta = m_DeltaTime.CalculateDeltaTime();

            m_Game.Update( delta );
            UpdateWindow(); // Update the platform App
        }
        
        CloseWindow(); // Close the window
    } 
}