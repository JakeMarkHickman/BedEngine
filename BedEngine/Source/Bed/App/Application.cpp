
#include "Application.h"
#include <Platforms/PlatformWrapper.h>
#include <Bed/Input/InputPoller.h>

namespace Bed
{
    void TestEvent(InputData data)
    {
        std::cout << data.Keycode << "\n";
    }

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
        Bed::InputPoller poller;
        instance.RegisterContext(poller);
        Bed::InputPoller* input = instance.GetContext<Bed::InputPoller>();
        input->Init();
        input->InputEvent.Subscribe(Bed::TestEvent);

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