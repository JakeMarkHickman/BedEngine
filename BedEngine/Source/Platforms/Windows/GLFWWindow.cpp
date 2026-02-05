#include "GLFWWindow.h"

#include <SleepTrace.h>


bool Bed::GLFWWindow::CreateWindow(int width, int height, const char* title)
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

    m_WindowSize = { width, height };

    glfwMakeContextCurrent(window);

    glfwSwapInterval(0); //Framerate

    /*renderer = new Bed::OpenRenderer();

    //TODO: Make this dynamic
    struct PointData
    {
        Pillow::Vector3f Position;
        float Padding1;
        Pillow::Vector3f Colour;
        float Padding2;
        float Strength;
        float Radius;
        float padding3[2];
    };
    struct DirectionalData
    {
        Pillow::Vector3f Colour;
        float Padding1;
        Pillow::Vector3f Direction;
        float Padding2;
        float Strength;
        float Padding3;
    };
    struct SpotData
    {
        Pillow::Vector3f Position;
        float Padding1;
        Pillow::Vector3f Colour;
        float Padding2;
        Pillow::Vector3f Direction;
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

    int TextureSlots;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &TextureSlots);

    LOG_INFO("Available Texture slots: " + std::to_string(TextureSlots));

    int textureSlots[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
        21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 
        31};

    struct InstanceData
    {
        glm::mat4 MatTransform;
        float TextureID;
        Pillow::Vector2f UVMin;
        Pillow::Vector2f UVMax;
    };

    //3D Shader
    {
        //Vertex array object
        va3D = new Bed::VertexArray();
        vb3D = new Bed::VertexBuffer(30000); // Store 3000 Bed::Vertex (pos, colour, texCoords, texID)
        ib3D = new Bed::IndexBuffer(40000);

        VertexBufferLayout vertLayout3D;
        vertLayout3D.Push<float>(3); // Position: 3 Floats (x, y, z)
        vertLayout3D.Push<float>(3); // Normal: 3 Floats (x, y, z)
        vertLayout3D.Push<float>(4); // Colour: 4 Floats (r, g, b, a)
        vertLayout3D.Push<float>(2); // TextureCoord: 2 Floats (x, y)
        vertLayout3D.Push<float>(1); // Texture ID: 1 Float (ID)
        va3D->AddBuffer(vb3D, vertLayout3D);

        shader3D = new Bed::OpenShader("Assets/Resources/Shaders/Bed3D.shader");
        shader3D->Bind();

        // Set Default uniforms on start
        shader3D->SetUniform1i("u_GlobalUnlit", false);
        shader3D->SetUniform1i("u_MaterialUnlit", false);
        shader3D->SetUniform1i("u_EnableFog", false);

        shader3D->SetUniform1iv("u_Textures", 32, textureSlots);
    }*/

    return true;
}

void Bed::GLFWWindow::UpdateWindow()
{
    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
}

bool Bed::GLFWWindow::IsWindowOpen()
{
    int width;
    int height;
    glfwGetWindowSize(window, &width, &height);
    ResizeWindow(width, height);
    return !glfwWindowShouldClose(window);
}

void Bed::GLFWWindow::CloseWindow()
{
    glfwTerminate();
}

void Bed::GLFWWindow::ResizeWindow(int width, int height)
{
    if(m_WindowSize.Width != width || m_WindowSize.Height != height)
    {
        Bed::Window::ResizeWindow(width, height);
    }
}

void Bed::GLFWWindow::RenameWindow(const char* title)
{
    if(m_WindowTitle != title)
    {
        glfwSetWindowTitle(window, title);
        Bed::Window::RenameWindow(title);
    }
}