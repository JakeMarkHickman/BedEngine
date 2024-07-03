
#include <Platform.h>
#ifdef BED_WINDOWS_PLATFORM
#include "Windows.cpp"
#endif

#include "Application.h"
#include "stdio.h"


namespace Bed
{
    
    void Application::Run()
    {
        PlatformCreateWindow(800, 550, "TestGame"); // Creates Platform App
        Update();
    }

    void Application::Update()
    {
        //Game Loop
        while (true)
        {
            PlatformUpdateWindow(); // Update the platform App
        }
        
    } 

}
