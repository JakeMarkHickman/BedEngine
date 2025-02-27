
#include "Application.h"
#include <Platforms/PlatformWrapper.h>
#include <Bed/Input/Input.h>

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
        Bed::ContextRegistry& instance = Bed::ContextRegistry::GetInstance();
        Bed::Input poller;
        instance.RegisterContext(poller);
        Bed::Input* input = instance.GetContext<Bed::Input>();
        input->Init();
        
        //Game Loop
        while (IsWindowOpen())
        {
            float delta = m_DeltaTime.CalculateDeltaTime();

            //std::cout << delta << "\n";

            m_Game.Update( delta );
            UpdateWindow(); // Update the platform App
        }
        
        CloseWindow(); // Close the window
    } 
}