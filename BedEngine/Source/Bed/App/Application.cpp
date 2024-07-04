
#include <Platform.h>
#include "Application.h"
#include "stdio.h"

namespace Bed
{
    void Application::Run()
    {
        if(PlatformCreateWindow(800, 550, "TestGame")) // Creates Platform App and checks to make sure its open
        {
            printf("Failed to create app");
            return; // leaves the function
        }

        Update();
    }

    void Application::Update()
    {
        bool ApplicationOpen = true;

        //Game Loop
        while (ApplicationOpen)
        {
            if(!ApplicationOpen) { return; } // If the application is no longer open close

            PlatformUpdateWindow(); // Update the platform App

            // TODO: Create an update event that fires to everything that uses it.
        }
        
    } 

}
