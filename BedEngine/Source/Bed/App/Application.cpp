
#include "Application.h"
#include <Platforms/PlatformWrapper.h>

// TODO: TEMP
#include <Bed/GameObjects/Map.h>
// TODO: TEMPTEMP

namespace Bed
{
    void Application::Run()
    {
        if(!CreateWindow(800, 550, m_ApplicationName, GraphicsAPI::OpenGL)) // Check to make sure the Window is created
        {
            return; // Return if the Window wasnt created
        }

        Update();
    }

    void Application::Update()
    {
        //Game Loop

        //TODO: Remove this
        
        while (IsWindowOpen())
        {
            UpdateWindow(); // Update the platform App

            //TODO: Remove this
            if(m_Map == nullptr)
            {
                break;
            }
            
            m_Map->Update( 0.016f );
            
            // TODO: Create an update event that fires to everything that uses it.
        }
        
        CloseWindow(); // Close the window
    } 
}