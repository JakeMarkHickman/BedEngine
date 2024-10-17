#pragma once

#include "Platform.h"
#include <Graphics/GraphicVariables.h>
#include <Graphics/Vertex.h>
#include <Bed/GameObjects/Mesh/Quad.h>
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
        glm::mat4 model;
        glm::mat4 proj;
        glm::mat4 view;

        float Size1 = 0.5;
        float Change1 = 0.01;
        float Size2 = 2;
        float Change2 = -0.001;

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

            //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Render objects in wireframe mode

            //Vertex array object
            va = new Bed::VertexArray();
            vb = new Bed::VertexBuffer(1000); // Store 1000 Bed::Vertex (pos, colour, texCoords, texID)
            ib = new Bed::IndexBuffer(3000);

            VertexBufferLayout vertLayout;
            vertLayout.Push<float>(3); // Position: 3 Floats (x, y, z)
            vertLayout.Push<float>(4); // Colour: 4 Floats (r, g, b, a)
            vertLayout.Push<float>(2); // TextureCoord: 2 Floats (x, y)
            vertLayout.Push<float>(1); // Texture ID: 1 Float (ID)
            va->AddBuffer(vb, vertLayout);

            //Shader
            shader = new Bed::Shader("C:/Users/Jake/Documents/GitHub/BedEngine/BedEngine/Resources/Shaders/Texture.shader");
            shader->Bind();

            //Texture
            texture = new Texture("C:/Users/Jake/Documents/GitHub/BedEngine/BedEngine/Resources/Textures/TestBedEngineIcon.png");
            texture->Bind(1); //Bind to slot 0

            testTexture = new Texture("C:/Users/Jake/Documents/GitHub/BedEngine/BedEngine/Resources/Textures/TestPlayer.png");
            testTexture->Bind(2); //Bind to slot 1

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
            testTexture->Bind(1);

            //Bind Shader
            shader->Bind();

            //Set mvp
            proj = glm::ortho(-2.0f *2, 2.0f*2, -1.5f*2, 1.5f*2, -1.0f, 1.0f); // Camera Screen Size
            view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)); // Camera Pos
            model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));// model Pos
            mvp = proj * view * model;
            shader->SetUniformMat4f("u_MVP", mvp);

            //Create two quads and copy over the data to an array
            //auto q0 = CreateQuad(Bed::Vector3(-1.0f, 0.0f, 0.0f), Bed::Vector4(0.18f, 0.6f, 0.95f, 1.0f), Bed::Vector3(Size1, Size2, 0.0f), 0.0f);
            //auto q1 = CreateQuad(Bed::Vector3(Size2, Size1, 0.0f), Bed::Vector4(0.95f, 0.6f, 0.4f, 1.0f), Bed::Vector3(1.0f, 1.0f, 1.0f), 1.0f);
            //Bed::Vertex verts[8];
            //memcpy(verts, q0.data(), q0.size() * sizeof(Bed::Vertex));
            //memcpy(verts + q0.size(), q1.data(), q1.size() * sizeof(Bed::Vertex));

            //unsigned int indices[12];

            //int indexCount = 0;
            //for (int i = 0; i < sizeof(verts) / sizeof(Bed::Vertex); i += 4) 
            //{
            //    // First triangle (0, 1, 2)
            //    indices[indexCount++] = i;
            //    indices[indexCount++] = i + 1;
            //    indices[indexCount++] = i + 2;

            //    // Second triangle (2, 1, 3)
            //    indices[indexCount++] = i + 2;
            //    indices[indexCount++] = i + 1;
            //    indices[indexCount++] = i + 3;
            //}

            //populate data with the newly created quads
            //vb->PopulateBuffer(verts, sizeof(verts), 0);
            //ib->PopulateBuffer(indices, sizeof(indices), 0);

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