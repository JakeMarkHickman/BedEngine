#pragma once

#include "Platform.h"
#include <Graphics/GraphicVariables.h>
#include <iostream>
#include <Bed/Input/Input.h>

//TODO: Remove this
#include <Graphics/OpenGL/OpenTexture.h>
#include <Graphics/OpenGL/OpenShader.h>

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

            glfwSwapInterval(0); //Framerate

            if(glewInit() != GLEW_OK)
            {
                return false;
            }

            glEnable(GL_DEBUG_OUTPUT);

            // TODO: From here needs to be moved else where as it not Windows Specific.
            
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);

            glEnable(GL_DEPTH_TEST);

            glFrontFace(GL_CW);

            //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Render objects in wireframe mode

            //Vertex array object
            va3D = new Bed::VertexArray();
            vb3D = new Bed::VertexBuffer(30000); // Store 3000 Bed::Vertex (pos, colour, texCoords, texID)
            ib3D = new Bed::IndexBuffer(40000);

            //TODO: Make this dynamic
            struct PointData
            {
                Bed::Vector3 Position;
                float Padding1;
                Bed::Vector3 Colour;
                float Padding2;
                float Strength;
                float Radius;
                float padding3[2];
            };
            struct DirectionalData
            {
                Bed::Vector3 Colour;
                float Padding1;
                Bed::Vector3 Direction;
                float Padding2;
                float Strength;
                float Padding3;
            };
            struct SpotData
            {
                Bed::Vector3 Position;
                float Padding1;
                Bed::Vector3 Colour;
                float Padding2;
                Bed::Vector3 Direction;
                float Padding3;
                float Strength;
                float CutOff;
                float OuterCutOff;
                float Radius;
                float padding4[4];
            };
            pointLightBuffer = new Bed::StorageBuffer(10 * sizeof(PointData)); // should give 10 point lights
            directionalLightBuffer = new Bed::StorageBuffer(10 * sizeof(DirectionalData)); // should give 10 directional lights
            spotLightBuffer = new Bed::StorageBuffer(10 * sizeof(SpotData)); // should give 10 spot lights

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
                shader3D = new Bed::OpenShader("Assets/Resources/Shaders/Bed3D.shader");
                shader3D->Bind();

                // Set Default uniforms on start
                shader3D->SetUniform1i("u_GlobalUnlit", false);
                shader3D->SetUniform1i("u_MaterialUnlit", false);
                shader3D->SetUniform1i("u_EnableFog", false);

                int samplers[32] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                    11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
                                    21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 
                                    31};
                shader3D->SetUniform1iv("u_Textures", 32, samplers);
            }

            //2D Shader
            {
                shader2D = new Bed::OpenShader("Assets/Resources/Shaders/Bed2D.shader");
                shader2D->Bind();
            }
            
            //UI Shader
            {
                shaderUI = new Bed::OpenShader("Assets/Resources/Shaders/BedUI.shader");
                shaderUI->Bind();
            }

            return true;
        }

        void OpenGLUpdateWindow()
        {
            //TODO: Switch this to be better
            Bed::ContextRegistry& instance = Bed::ContextRegistry::GetInstance();
            Bed::Input* input = instance.GetContext<Bed::Input>();
            input->PollInput(window, 0);

            /* Render here */
            renderer->Clear();

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
            pointLightBuffer->Unbind();

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