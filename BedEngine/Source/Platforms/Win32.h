#pragma once

#include "Platform.h"
#include <Graphics/GraphicVariables.h>
#include <Graphics/Vertex.h>
#include <Bed/GameObjects/Mesh/Quad.h>
#include <Graphics/Texture.h>
#include <Bed/GameObjects/Mesh/Mesh.h>
#include <iostream>

// TODO: replace GLM Includes
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

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
            va = new Bed::VertexArray();
            vb = new Bed::VertexBuffer(3000); // Store 3000 Bed::Vertex (pos, colour, texCoords, texID)
            ib = new Bed::IndexBuffer(4000);

            VertexBufferLayout vertLayout;
            vertLayout.Push<float>(3); // Position: 3 Floats (x, y, z)
            vertLayout.Push<float>(4); // Colour: 4 Floats (r, g, b, a)
            vertLayout.Push<float>(2); // TextureCoord: 2 Floats (x, y)
            vertLayout.Push<float>(1); // Texture ID: 1 Float (ID)
            va->AddBuffer(vb, vertLayout);

            //Shader
            shader = new Bed::Shader("Assets/Resources/Shaders/Texture.shader");
            shader->Bind();

            //Texture
            texture = new Texture("Assets/Resources/Textures/256xWhite.png");
            texture->Bind(0); //Bind to slot 0


            int samplers[2] = { 0, 1 };
            shader->SetUniform1iv("u_Textures", 2, samplers);

            return true;
        }

        void OpenGLUpdateWindow()
        {
            //TODO: Sometimes nothing renderers

            /* Render here */
            renderer->Clear();

            //Bind Textures
            texture->Bind(0);

            //Render Everything
            renderer->Draw(va, ib, shader);

            //Unbind Everything
            va->Unbind();
            shader->Unbind();
            vb->Unbind();
            ib->Unbind();

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
            delete shader;
            glfwTerminate();
        }
    };
}