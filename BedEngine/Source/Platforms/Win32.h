#pragma once

#include "Platform.h"
#include <Graphics/OpenGL/OpenGl.h>
#include <Graphics/VertexBuffer.h>
#include <Graphics/IndexBuffer.h>
#include <Graphics/VertexArray.h>
#include <Graphics/Shader.h>
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

        float r = 0.5f;
        float g = 0.5f;
        float b = 0.5f;
        
        float interval1 = 0.05f;
        float interval2 = 0.03f;
        float interval3 = 0.01f;

        Bed::IndexBuffer* ib;
        Bed::VertexArray* va;
        Bed::Shader* shader;

        int location;

        GLFWwindow* window;

        bool OpenGlCreateWindow(int width, int height, const char* title)
        {
            if(!glfwInit())
            {
                return false;
            }

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

            //TEMP
            //Vertex array object
            glGenVertexArrays(1, &VertexArrayObject);
            glBindVertexArray(VertexArrayObject);

            va = new VertexArray();

            //Vertex Buffer
            Bed::VertexBuffer vb(Positions, 4 * 2 * sizeof(float));

            VertexBufferLayout layout;
            layout.Push<float>(2);
            va->AddBuffer(vb, layout);

            //Index Element buffer
            ib = new Bed::IndexBuffer(Indices, 6);

            shader = new Bed::Shader("C:/Users/Jake/Documents/GitHub/BedEngine/BedEngine/Resources/Shaders/Basic.shader");
            shader->Bind();
            shader->SetUniform4f("u_Colour", Bed::Vector4 { r, g, b, 1.0f });

            // Unbind everthing
            va->Unbind();
            shader->Unbind();
            vb.Unbind();
            ib->Unbind();
            //TEMP

            return true;
        }

        void OpenGLUpdateWindow()
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            shader->Bind();
            shader->SetUniform4f("u_Colour", Bed::Vector4 { r, g, b, 1.0f });

            va->Bind();

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

            if (r > 1.0f)
                interval1 = -0.05f;
            else if (r < 0.0f )
                interval1 = 0.05f;

            r += interval1;

            if (g > 1.0f)
                interval2 = -0.03f;
            else if (g < 0.0f )
                interval2 = 0.03f;
            
            g += interval2;

            if (b > 1.0f)
                interval3 = -0.01f;
            else if (b < 0.0f )
                interval3 = 0.01f;
            
            b += interval3;

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