#pragma once

#include "Platform.h"
#include <Graphics/OpenGL/OpenGl.h>
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

            if(!AvaiableFlags.HasFlag(m_CurrentFlag) || m_CurrentFlag == 0)
            {
                std::cout << m_CurrentFlag << " is not allowed on Windows or isn't valid, Switching to OpenGL" << std::endl;
                m_CurrentFlag = GraphicsAPI::OpenGL;
            }
        };
        ~Win32() {};

        bool PlatformCreateWindow(int width, int height, char* title) 
        {
            bool WindowCreated;

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

        int location;

        GLFWwindow* window;

        bool OpenGlCreateWindow(int width, int height, char* title)
        {
            if(!glfwInit())
            {
                return false;
            }

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
            //Array Buffer
            glGenBuffers(1, &buffer);
            glBindBuffer(GL_ARRAY_BUFFER, buffer);
            glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 2 /*2 represents the number of dimensions so 3 would be 3D*/, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
            glEnableVertexAttribArray(0);

            //Index Element buffer
            glGenBuffers(1, &indexBufferObject);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);


            ShaderProgramSource source = ParseShader("D:/GitHub/BedEngine/BedEngine/Resources/Shaders/Basic.shader"); //TODO: Change this to install Dir

            shader = CreateShader(source.vertexSource, source.fragmentSource);
            glUseProgram(shader);

            location = glGetUniformLocation(shader, "u_Colour");
            
            glUniform4f(location, r, g, b, 1.0f);
            //TEMP

            return true;
        }

        void OpenGLUpdateWindow()
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            glUniform4f(location, r, g, b, 1.0f);
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
            glDeleteProgram(shader);
            glfwTerminate();
        }
    };
}