#pragma once

#include "Platform.h"
#include <Graphics/VertexBuffer.h>
#include <Graphics/IndexBuffer.h>
#include <Graphics/VertexArray.h>
#include <Graphics/GraphicVariables.h>
#include <Bed/GameObjects/Models/Square.h>
#include <Graphics/Texture.h>
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

        Bed::Texture* texture;
        Bed::Texture* testTexture;

        glm::mat4 mvp;
        glm::vec3 worldOrigin;
        glm::mat4 proj;
        glm::mat4 view;

        GLFWwindow* window;

        float Verts[80] = {
            //x     //y    //z    //r     //g    //b     //a    //x    //y    //TexID
            -1.5f,  0.5f,  0.0f,  0.18f,  0.6f,  0.96f,  1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.0f,  0.18f,  0.6f,  0.96f,  1.0f,  1.0f,  1.0f,  0.0f,
            -1.5f, -0.5f,  0.0f,  0.18f,  0.6f,  0.96f,  1.0f,  0.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.0f,  0.18f,  0.6f,  0.96f,  1.0f,  1.0f,  0.0f,  0.0f,

             0.5f,  0.5f,  0.0f,  1.0f,  0.6f,  0.96f,  1.0f,  0.0f,  1.0f,  1.0f,
             1.5f,  0.5f,  0.0f,  1.0f,  0.6f,  0.96f,  1.0f,  1.0f,  1.0f,  1.0f,
             0.5f, -0.5f,  0.0f,  1.0f,  0.6f,  0.96f,  1.0f,  0.0f,  0.0f,  1.0f,
             1.5f, -0.5f,  0.0f,  1.0f,  0.6f,  0.96f,  1.0f,  1.0f,  0.0f,  1.0f
        };

        uint32_t indices[12] = {
            0,1,2, 2,1,3,
            4,5,6, 6,5,7
        };

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

            // TODO: From here needs to be moved else where as it not Windows Specific.
            
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);

            //Vertex array object
            va = new Bed::VertexArray();
            Bed::VertexBuffer vb(Verts, sizeof(Verts));

            VertexBufferLayout vertLayout;
            vertLayout.Push<float>(3); // Position: 3 Floats (x, y, z)
            vertLayout.Push<float>(4); // Colour: 4 Floats (r, g, b, a)
            vertLayout.Push<float>(2); // TextureCoord: 2 Floats (x, y)
            vertLayout.Push<float>(1); // Texture ID: 1 Float (ID)
            va->AddBuffer(vb, vertLayout);

            //Index Element buffer
            ib = new Bed::IndexBuffer(indices, sizeof(indices));

            //Shader
            shader = new Bed::Shader("C:/Users/Jake/Documents/GitHub/BedEngine/BedEngine/Resources/Shaders/Texture.shader");
            shader->Bind();

            //Texture
            //TODO: These need updating
            texture = new Texture("C:/Users/Jake/Documents/GitHub/BedEngine/BedEngine/Resources/Textures/TestBedEngineIcon.png");
            texture->Bind(1); //Bind to slot 0

            testTexture = new Texture("C:/Users/Jake/Documents/GitHub/BedEngine/BedEngine/Resources/Textures/TestImage.png");
            testTexture->Bind(2); //Bind to slot 1

            int samplers[2] = { 0, 1 };
            shader->SetUniform1iv("u_Textures", sizeof(samplers), samplers);

            

            worldOrigin = glm::vec3(0,0,0);

            //CAMERA
            proj = glm::ortho(-2.0f *2, 2.0f*2, -1.5f*2, 1.5f*2, -1.0f, 1.0f); // Camera Screen Size
            view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)); // Camera Pos
            
            //MODEL 1
            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), worldOrigin); // Model Pos
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

            texture->Bind(0);
            testTexture->Bind(1);

            //MODEL 1
            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), worldOrigin); // Model Pos
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