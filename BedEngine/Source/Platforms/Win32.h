#pragma once

#include "Platform.h"
#include <Graphics/VertexBuffer.h>
#include <Graphics/IndexBuffer.h>
#include <Graphics/VertexArray.h>
#include <Graphics/Renderer.h>
#include <Graphics/Shader.h>
#include <Graphics/Texture.h>
#include <iostream>

// TODO: replace GLM Includes
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

namespace Bed
{
    float Positions[] = 
    {
    //   X      Y
        -0.5f, -0.5f, 0.0f, 0.0f,   // 0
        -0.5f,  0.5f, 0.0f, 1.0f,   // 1
         0.5f,  0.5f, 1.0f, 1.0f,   // 2
         0.5f, -0.5f, 1.0f, 0.0f    // 3
    };

    unsigned int Indices[]
    {
        0, 1, 2,
        0, 2, 3
    };

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

        Bed::IndexBuffer* ib;
        Bed::VertexArray* va;
        Bed::Shader* shader;
        Bed::Renderer* renderer;
        Bed::Texture* texture;

        glm::mat4 mvp;
        glm::vec3 model1;
        glm::vec3 model2;
        glm::mat4 proj;
        glm::mat4 view;

 
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

            // TODO: From here needs to be moved else where as it not Windows Specific.
            
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);

            //Vertex array object
            va = new Bed::VertexArray();
            Bed::VertexBuffer vb(Positions, 4 * 4 * sizeof(float));

            VertexBufferLayout layout;
            layout.Push<float>(2);
            layout.Push<float>(2);
            va->AddBuffer(vb, layout);

            //Index Element buffer
            ib = new Bed::IndexBuffer(Indices, 6);

            //Shader
            shader = new Bed::Shader("C:/Users/Jake/Documents/GitHub/BedEngine/BedEngine/Resources/Shaders/Basic.shader");
            shader->Bind();

            //Texture
            texture = new Texture("C:/Users/Jake/Documents/GitHub/BedEngine/BedEngine/Resources/Textures/TestBedEngineIcon.png");
            texture->Bind();
            shader->SetUniform1i("u_Texture", 0);

            model1 = glm::vec3(0,0,0);
            model2 = glm::vec3(1,1,0);

            //CAMERA
            proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f); // Camera Screen Size
            view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)); // Camera Pos
            
            //MODEL 1
            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), model1); // Model Pos
                mvp = proj * view * model;

                shader->Bind(); //TODO: this is redundant, a cage would be used to catch if a shader is already bound
                shader->SetUniformMat4f("u_MVP", mvp);

                //Draw
                renderer->Draw(va, ib, shader);
            }

            //MODEL 2
            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), model2); // Model Pos
                mvp = proj * view * model;

                shader->Bind(); //TODO: this is redundant, a cage would be used to catch if a shader is already bound
                shader->SetUniformMat4f("u_MVP", mvp);

                //Draw
                renderer->Draw(va, ib, shader);
            }

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
            renderer->Clear();

            texture->Bind();

            //MODEL 1
            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), model1); // Model Pos
                mvp = proj * view * model;

                shader->Bind(); //TODO: this is redundant, a cage would be used to catch if a shader is already bound
                shader->SetUniformMat4f("u_MVP", mvp);

                //Draw
                renderer->Draw(va, ib, shader);
            }

            //MODEL 2
            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), model2); // Model Pos
                mvp = proj * view * model;

                shader->Bind(); //TODO: this is redundant, a cage would be used to catch if a shader is already bound
                shader->SetUniformMat4f("u_MVP", mvp);

                //Draw
                renderer->Draw(va, ib, shader);
            }
            
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