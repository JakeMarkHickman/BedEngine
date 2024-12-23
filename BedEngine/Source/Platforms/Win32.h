#pragma once

#include "Platform.h"
#include <Graphics/GraphicVariables.h>
#include <iostream>

namespace Bed
{
    class Win32 : public Bed::Platform
    {
    public:

        Win32() 
        {
            AvaiableFlags.SetFlag(GraphicsAPI::OpenGL);
            AvaiableFlags.SetFlag(GraphicsAPI::Vulkan);
            AvaiableFlags.SetFlag(GraphicsAPI::DirectX);
        };

        ~Win32() {};

        bool PlatformCreateWindow(int width, int height, const char* title, GraphicsAPI::EGraphicsAPIFlags Pipeline) 
        {
            bool WindowCreated;

            m_CurrentFlag = UseGraphicsPipeline(Pipeline);

            switch (m_CurrentFlag)
            {
            case GraphicsAPI::OpenGL:
                WindowCreated = Win32::OpenGlCreateWindow(width, height, title);
                break;

            case GraphicsAPI::Vulkan:
                WindowCreated = false;
                break;

            case GraphicsAPI::DirectX:
                WindowCreated = false;
                break;

            default:
                WindowCreated = false;
                std::cout << "No valid Graphics API" << std::endl;
                break;
            }

            return WindowCreated;
        };

        void PlatformUpdateWindow() 
        {
            switch (m_CurrentFlag)
            {
            case GraphicsAPI::OpenGL:
                Win32::OpenGLUpdateWindow();
                break;
            
            case GraphicsAPI::Vulkan:
                break;

            case GraphicsAPI::DirectX:
                break;

            default:
                break;
            }
        };

        bool PlatformIsWindowOpen() 
        {
            bool WindowOpen;

            switch (m_CurrentFlag)
            {
            case GraphicsAPI::OpenGL:
                WindowOpen = Win32::OpenGLIsWindowOpen();
                break;

            case GraphicsAPI::Vulkan:
                WindowOpen = false;
                break;

            case GraphicsAPI::DirectX:
                WindowOpen = false;
                break;
            
            default:
                break;
            }

            return WindowOpen;
        };

        void PlatformCloseWindow() 
        {
            switch (m_CurrentFlag)
            {
            case GraphicsAPI::OpenGL:
                Win32::OpenGLCloseWindow();
                break;

            case GraphicsAPI::Vulkan:
                Win32::OpenGLCloseWindow();
                break;

            case GraphicsAPI::DirectX:
                Win32::OpenGLCloseWindow();
                break;
            
            default:
                break;
            }
        };


    private:

        GLFWwindow* window;

        bool OpenGlCreateWindow(int width, int height, const char* title)
        {
            if(!glfwInit())
            {
                return false;
            }

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            //TODO: This sets the window size, this needs to be dynamic
            window = glfwCreateWindow(width, height, title, NULL, NULL);
            if (!window)
            {
                glfwTerminate();
                return false;
            }

            glfwMakeContextCurrent(window);

            glfwSwapInterval(1);

            if(glewInit() != GLEW_OK)
            {
                return false;
            }

            glEnable(GL_DEBUG_OUTPUT);

            // TODO: From here needs to be moved else where as it not Windows Specific.
            
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);

            glEnable(GL_DEPTH_TEST);

            //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Render objects in wireframe mode

            //Vertex array object
            va3D = new Bed::VertexArray();
            vb3D = new Bed::VertexBuffer(3000); // Store 3000 Bed::Vertex (pos, colour, texCoords, texID)
            ib3D = new Bed::IndexBuffer(4000);

            va2D = new Bed::VertexArray();
            vb2D = new Bed::VertexBuffer(3000); // Store 3000 Bed::Vertex (pos, colour, texCoords, texID)
            ib2D = new Bed::IndexBuffer(4000);

            vaUI = new Bed::VertexArray();
            vbUI = new Bed::VertexBuffer(3000); // Store 3000 Bed::Vertex (pos, colour, texCoords, texID)
            ibUI = new Bed::IndexBuffer(4000);

            VertexBufferLayout vertLayout3D;
            vertLayout3D.Push<float>(3); // Position: 3 Floats (x, y, z)
            vertLayout3D.Push<float>(3); // Normal: 3 Floats (x, y, z)
            vertLayout3D.Push<float>(4); // Colour: 4 Floats (r, g, b, a)
            vertLayout3D.Push<float>(2); // TextureCoord: 2 Floats (x, y)
            vertLayout3D.Push<float>(1); // Texture ID: 1 Float (ID)
            va3D->AddBuffer(vb3D, vertLayout3D);

            VertexBufferLayout vertLayout2D;
            vertLayout2D.Push<float>(3); // Position: 3 Floats (x, y, z)
            vertLayout2D.Push<float>(3); // Normal: 3 Floats (x, y, z)
            vertLayout2D.Push<float>(4); // Colour: 4 Floats (r, g, b, a)
            vertLayout2D.Push<float>(2); // TextureCoord: 2 Floats (x, y)
            vertLayout2D.Push<float>(1); // Texture ID: 1 Float (ID)
            va2D->AddBuffer(vb2D, vertLayout2D);

            //TODO: UI doesnt need normal
            VertexBufferLayout vertLayoutUI;
            vertLayoutUI.Push<float>(3); // Position: 3 Floats (x, y, z)
            vertLayoutUI.Push<float>(3); // Normal: 3 Floats (x, y, z)
            vertLayoutUI.Push<float>(4); // Colour: 4 Floats (r, g, b, a)
            vertLayoutUI.Push<float>(2); // TextureCoord: 2 Floats (x, y)
            vertLayoutUI.Push<float>(1); // Texture ID: 1 Float (ID)
            vaUI->AddBuffer(vbUI, vertLayoutUI);

            //3D Shader
            {
                shader3D = new Bed::Shader("Assets/Resources/Shaders/Bed3D.shader");
                shader3D->Bind();

                //Texture
                texture = new Texture("Assets/Resources/Textures/256xWhite.png");
                texture->Bind(0); //Bind to slot 0

                int samplers[2] = { 0, 1 };
                shader3D->SetUniform1iv("u_Textures", 2, samplers);
            }

            //2D Shader
            {
                shader2D = new Bed::Shader("Assets/Resources/Shaders/Bed2D.shader");
                shader2D->Bind();
            }
            
            //UI Shader
            {
                shaderUI = new Bed::Shader("Assets/Resources/Shaders/BedUI.shader");
                shaderUI->Bind();
            }

            return true;
        }

        void OpenGLUpdateWindow()
        {
            /* Render here */
            renderer->Clear();

            //Bind Textures
            texture->Bind(0);

            //TODO: Render World3D then World2D then UI
            //Render Everything
            glEnable(GL_DEPTH_TEST);
            renderer->Draw(va3D, ib3D, shader3D);

            glEnable(GL_DEPTH_TEST);
            renderer->Draw(va2D, ib2D, shader2D);

            glDisable(GL_DEPTH_TEST);
            renderer->Draw(vaUI, ibUI, shaderUI);

            //Unbind Everything
            va3D->Unbind();
            shader3D->Unbind();
            vb3D->Unbind();
            ib3D->Unbind();

            va2D->Unbind();
            shader2D->Unbind();
            vb2D->Unbind();
            ib2D->Unbind();

            vaUI->Unbind();
            shaderUI->Unbind();
            vbUI->Unbind();
            ibUI->Unbind();

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        bool OpenGLIsWindowOpen()
        {
            return !glfwWindowShouldClose(window);
        }

        void OpenGLCloseWindow()
        {
            delete shader3D;
            delete shader2D;
            delete shaderUI;
            glfwTerminate();
        }
    };
}