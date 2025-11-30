
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

        if(logType == SleepTrace::LogType::Fatal)
        {
            abort();
        }
    }
}
#endif

namespace Bed
{
    //RENDERING
    void OnSpriteComponentAttached(Bed::World& world, uint64_t entity)
    {
        if(world.HasComponents<Pillow::Transform, Bed::Sprite>(entity))
        {
            Quilt::Vertex v0;
            v0.Position = { -0.5f, -0.5f, 0.0f };
            v0.Normal = { 0.0f, 0.0f, 0.0f };
            v0.Colour = { Pillow::Vector4f(1.0f, 1.0f, 1.0f, 1.0f) };
            v0.TextureCoordinates = { 0.0f,  0.0f };
            v0.TextureID = 0;

            Quilt::Vertex v1;
            v1.Position = { 0.5f, -0.5f, 0.0f };
            v1.Normal = { 0.0f, 0.0f, 0.0f };
            v1.Colour = { Pillow::Vector4f(1.0f, 1.0f, 1.0f, 1.0f) };
            v1.TextureCoordinates = { 1.0f,  0.0f };
            v1.TextureID = 0;

            Quilt::Vertex v2;
            v2.Position = { 0.5f, 0.5f, 0.0f };
            v2.Normal = { 0.0f, 0.0f, 0.0f };
            v2.Colour = { Pillow::Vector4f(1.0f, 1.0f, 1.0f, 1.0f) };
            v2.TextureCoordinates = { 1.0f,  1.0f };
            v2.TextureID = 0;

            Quilt::Vertex v3;
            v3.Position = { -0.5f, 0.5f, 0.0f };
            v3.Normal = { 0.0f, 0.0f, 0.0f };
            v3.Colour = { Pillow::Vector4f(1.0f, 1.0f, 1.0f, 1.0f) };
            v3.TextureCoordinates = { 0.0f,  1.0f };
            v3.TextureID = 0;

            std::vector<Quilt::Vertex> vertices = { v0, v1, v2, v3 };
            std::vector<unsigned int> indices = { 0, 1, 2, 2, 3, 0 };

            Bed::Sprite* sprite = world.GetComponent<Bed::Sprite>(entity);
            sprite->Handle = Quilt::Duvet::CreateMesh(vertices, indices, world.GetComponent<Pillow::Transform>(entity));
        }
    }

    void OnTextureComponentAttached(Bed::World& world, uint64_t entity)
    {
        if(world.HasComponents<Bed::Texture, Bed::Sprite, Pillow::Transform>(entity))
        {
            Bed::Texture* texture = world.GetComponent<Bed::Texture>(entity);
            Bed::Sprite* sprite = world.GetComponent<Bed::Sprite>(entity);

            Quilt::Duvet::CreateTexture(texture->TexturePath, Quilt::TextureFiltering::Nearest, sprite->Handle);
        }
    }

    void OnCameraComponentAttached(Bed::World& world, uint64_t entity)
    {
        if(world.HasComponents<Pillow::Transform, Bed::Camera>(entity))
        {
            Pillow::Transform* transform = world.GetComponent<Pillow::Transform>(entity);
            Quilt::Duvet::CreateCamera(transform);
        }
    }

    //Physics
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

    void OnSpriteComponentRemoved(Bed::World& world, uint64_t entity)
    {
        if(world.HasComponents<Pillow::Transform, Bed::Sprite>(entity))
        {
            Bed::Sprite* sprite = world.GetComponent<Bed::Sprite>(entity);
            Quilt::Duvet::RemoveMesh(sprite->Handle);
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
            return; // Return if the Window wasnt created
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
        */
        m_Game->GetECS().RegisterOnComponentAttachedGlobal<Pillow::Transform, Bed::Sprite>(Bed::OnSpriteComponentAttached);
        m_Game->GetECS().RegisterOnComponentRemovedGlobal<Pillow::Transform, Bed::Sprite>(Bed::OnSpriteComponentRemoved);

        //TODO: Textures shouldnt rely on needing the sprite or transform
        m_Game->GetECS().RegisterOnComponentAttachedGlobal<Bed::Texture, Bed::Sprite, Pillow::Transform>(Bed::OnTextureComponentAttached);
        m_Game->GetECS().RegisterOnComponentAttachedGlobal<Pillow::Transform, Bed::Camera>(Bed::OnCameraComponentAttached);
        m_Game->GetECS().RegisterOnComponentAttachedGlobal<Pillow::Transform, Mattress::PhysicsObject>(Bed::OnPhysicsComponentAttached);

        m_Game->BeginPlay();

        //Game Loop
        while (m_Window->IsWindowOpen())
        {
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
            for(auto& world : m_Game->GetActiveWorlds())
            {
                world.second->GetWorldPhysics().Step(Time::GetDeltaTime()); //Physics update
                
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
            }

            Quilt::Duvet::Draw();
            
            m_Window->UpdateWindow(); // Update the platform App
        }
        
        m_Window->CloseWindow(); // Close the window
    }
}