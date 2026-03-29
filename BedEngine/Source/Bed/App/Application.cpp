
#include "Application.h"

//Debugger
#include <SleepTrace.h>
#include <iostream>

//Platform Factory
#include <Platforms/PlatformFactory.h>
#include <Platforms/WindowFactory.h>

//Components
#include <Transform.h>
#include <Components/Renderer/Sprite.h>
#include <Components/Material/Texture.h>
#include <Components/Camera.h>
#include <PhysicsObject.h>

#include <Vertex.h>

#ifdef BED_DEBUG
namespace Debug
{
    void log(SleepTrace::LogType logType, const char* file, int line, const std::string& message)
    {
        std::string type = "";
        switch (logType)
        {
        case SleepTrace::LogType::Trace:
            type = "[TRACE]: ";
            break;

        case SleepTrace::LogType::Debug:
            type = "[DEBUG]: ";
            break;

        case SleepTrace::LogType::Info:
            type = "[INFO]: ";
            break;

        case SleepTrace::LogType::Warn:
            type = "[WARN]: ";
            break;

        case SleepTrace::LogType::Error:
            type = "[ERROR]: ";
            break;

        case SleepTrace::LogType::Fatal:
            type = "[FATAL]: ";
            break;
        }

        //TODO: Add a time to see when something happened
        std::cout << type << "[" << file << " " << line << "]: " << message << "\n";

        //TODO: this needs to crash before the function is called.
        if(logType == SleepTrace::LogType::Fatal)
        {
            abort();
        }
    }
}
#endif

namespace Bed
{
    //PHYSICS
    void OnPhysicsComponentAttached(Bed::World& world, uint64_t entity)
    {
        if(world.HasComponents<Pillow::Transform, Mattress::PhysicsObject>(entity))
        {
            Mattress::PhysicsObject* physicsObject = world.GetComponent<Mattress::PhysicsObject>(entity);
            Pillow::Transform* transform = world.GetComponent<Pillow::Transform>(entity);

            physicsObject->Position = transform->Position;

            world.GetWorldPhysics().AddPhysicsObject(physicsObject);
        }
    }
}

namespace Bed
{

    void Application::Run()
    {
        #ifdef BED_DEBUG
            SleepTrace::Log::SetCallback(Debug::log);
        #endif

        m_Platform = Bed::PlatformFactory::CreatePlatform(Bed::OpenGL);
        m_Window = Bed::WindowFactory::CreatePlatform(m_Platform);

        //TODO: make a system to automatically recognise monitor size and scale correctly
        if(!m_Window->CreateWindow(800, 450, m_ApplicationName)) // Check to make sure the Window is created
        {
            LOG_FATAL("Window not Created!");
            return;
        }

        m_Window->SetWindowIcon(m_WindowIcon);

        if(!Quilt::Duvet::IsContextValid()) // Check to make sure the context is created
        {
            LOG_FATAL("Context not Created!");
            return;
        }

        Update();
    }

    void Application::Update()
    {
        //TODO: This needs to be better
        //Bed::ContextRegistry& instance = Bed::ContextRegistry::GetInstance();

        /*
            TODO: Some of these may not be global
            TODO: Make it so reloading a world correctly adds the global events
            TODO: call plugins that register global components here, maybe have a way to force reload plugins so that it can happen at any time (stops closing the editor).
            TODO: make this a seperate function as this will be able to be modified by users or plugins
        */

        Quilt::Duvet::Init();

        std::string shaderName = "2D Shader";

        std::string vertexShader = R"(
            #version 450 core 
            layout(location = 0) in vec4 a_Position;
            layout(location = 1) in vec3 a_Normal;
            layout(location = 2) in vec4 a_Colour;
            layout(location = 3) in vec2 a_TexCoord;
            layout(location = 4) in float a_TexID;

            uniform mat4 u_View;
            uniform mat4 u_Projection;
            uniform mat4 u_Model;

            out vec4 v_Pos;
            out vec3 v_Normal;
            out vec4 v_Colour;
            out vec2 v_TexCoord;
            flat out float v_TexID;

            vec4 mvp(vec4 pos)
            {
                return u_Projection * u_View * (u_Model * pos);
            }

            void main()
            {
                v_Pos = u_Model * a_Position;
                v_Normal = a_Normal;
                v_Colour = a_Colour;
                v_TexCoord = a_TexCoord;
                v_TexID = a_TexID;

                gl_Position = mvp(a_Position);
            }
        )";

        std::string fragmentShader = R"(
            #version 450 core
            in vec4 v_Pos;
            in vec3 v_Normal;
            in vec4 v_Colour;
            in vec2 v_TexCoord;
            flat in float v_TexID;

            uniform sampler2D u_Textures[32];

            layout(location = 0) out vec4 o_FragColour;

            void main()
            {
                o_FragColour = texture(u_Textures[int(v_TexID)], v_TexCoord) * v_Colour;
            }
        )";

        Quilt::Duvet::CreateShader(shaderName, vertexShader, fragmentShader);
        Quilt::Duvet::SetDefaultTexture("Assets/Resources/Textures/256xWhite.png");

        //TODO: Textures shouldnt rely on needing the sprite or transform
        m_Game->GetECS().RegisterOnComponentAttachedGlobal<Pillow::Transform, Mattress::PhysicsObject>(Bed::OnPhysicsComponentAttached);

        m_Game->BeginPlay();

        float PhysicsUpdateDelay = 1.0f / PhysicsFramerate;
        int MaxSteps = 4;

        float currentTimer = 0.0f;


        //Game Loop
        while (m_Window->IsWindowOpen())
        {
            Quilt::Duvet::SetViewPort(Bed::Window::GetWindowSize().Width, Bed::Window::GetWindowSize().Height);

            m_Time.CalculateDeltaTime();

            m_Game->Update(); //Game update

            /*
                TODO: figure out some way of making Fixed time loop for all worlds at once
                Options:
                    Have a clock that checks inside the physics system
                        Mattress::Physics::Tick();

                    A global clock for the whole engine
                        m_Time.GetFixedTime();

                    Have the loop below inside of the physics system and worlds are added into the manager
                    from the ECS that way its a one function call
            */
            currentTimer += Time::GetDeltaTime();
            currentTimer = std::min(currentTimer, PhysicsUpdateDelay * MaxSteps);

            while(currentTimer >= PhysicsUpdateDelay)
            {
                
                for(auto& world : m_Game->GetActiveWorlds())
                {
                    world.second->GetWorldPhysics().Step(PhysicsUpdateDelay); //Physics update
                    
                    //Update Entity Positions from physics step
                    //TODO: Use quieries to test for physics data not a physics object to update
                    //TODO: This could be a call back so that all data/worlds gets registered then
                    for(uint64_t i : world.second->GetAllEntities())
                    {
                        if(!world.second->HasComponents<Pillow::Transform, Mattress::PhysicsObject>(i))
                        {
                            continue;
                        }

                        Pillow::Transform* transform = world.second->GetComponent<Pillow::Transform>(i);
                        Mattress::PhysicsObject* phyObj = world.second->GetComponent<Mattress::PhysicsObject>(i);

                        //Update the Position of the Object
                        transform->Position = phyObj->Position;
                    }

                    currentTimer -= PhysicsUpdateDelay;
                }
            } 

            //Clear the screen
            Quilt::Duvet::Clear();
            //Draw
            Quilt::Duvet::Draw();

            m_Window->UpdateWindow(); // Update the window buffers
        }
        
        m_Window->CloseWindow(); // Close the window
    }
}