
#include <Platform.h>
#include "Application.h"

namespace Bed
{
    void Application::Run()
    {
        CreateWindow(800, 550, "TestGame"); // Create the window

        Update();
    }

    void Application::Update()
    {
        //Game Loop
        while (IsWindowOpen())
        {
            UpdateWindow(); // Update the platform App

            // TODO: Create an update event that fires to everything that uses it.
        }
        
        CloseWindow(); // Close the window
    } 

}