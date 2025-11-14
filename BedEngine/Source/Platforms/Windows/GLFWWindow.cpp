#include "GLFWWindow.h"

#include <SleepTrace.h>

//Bed::GLFWWindow::GLFWWindow(Bed::Platform* platform)
//{
//    Bed::Window::Window(platform);
//}

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

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Render objects in wireframe mode

    
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

    Bed::Vertex v0;
        v0.m_Position = { -0.5f, -0.5f, 0.0f };
        v0.m_Normal = { 0.0f, 0.0f, 0.0f };
        v0.m_Colour = { Pillow::Vector4f(1.0f, 1.0f, 1.0f, 1.0f) };
        v0.m_TexCoords = { 0.0f,  0.0f };
        v0.m_TexID = 0;

    Bed::Vertex v1;
        v1.m_Position = { 0.5f, -0.5f, 0.0f };
        v1.m_Normal = { 0.0f, 0.0f, 0.0f };
        v1.m_Colour = { Pillow::Vector4f(1.0f, 1.0f, 1.0f, 1.0f) };
        v1.m_TexCoords = { 1.0f,  0.0f };
        v1.m_TexID = 0;

    Bed::Vertex v2;
        v2.m_Position = { 0.5f, 0.5f, 0.0f };
        v2.m_Normal = { 0.0f, 0.0f, 0.0f };
        v2.m_Colour = { Pillow::Vector4f(1.0f, 1.0f, 1.0f, 1.0f) };
        v2.m_TexCoords = { 1.0f,  1.0f };
        v2.m_TexID = 0;

    Bed::Vertex v3;
        v3.m_Position = { -0.5f, 0.5f, 0.0f };
        v3.m_Normal = { 0.0f, 0.0f, 0.0f };
        v3.m_Colour = { Pillow::Vector4f(1.0f, 1.0f, 1.0f, 1.0f) };
        v3.m_TexCoords = { 0.0f,  1.0f };
        v3.m_TexID = 0;

    std::vector<Bed::Vertex> verts = { v0, v1, v2, v3 };
    std::vector<unsigned int> indices = { 0, 1, 2, 2, 3, 0 };

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
    }

    //2D Shader
    {
        va2D = new Bed::VertexArray();
        vb2D = new Bed::VertexBuffer(3000); // Store 3000 Bed::Vertex (pos, colour, texCoords, texID)
        ib2D = new Bed::IndexBuffer(4000);
        ib2D = new Bed::IndexBuffer(6000);
        ivb2D = new Bed::InstanceBuffer(100, sizeof(InstanceData)); //100 instances

        VertexBufferLayout vertLayout2D;
        vertLayout2D.Push<float>(3); // Position: 3 Floats (x, y, z)
        vertLayout2D.Push<float>(3); // Normal: 3 Floats (x, y, z)
        vertLayout2D.Push<float>(4); // Colour: 4 Floats (r, g, b, a)
        vertLayout2D.Push<float>(2); // TextureCoord: 2 Floats (x, y)
        vertLayout2D.Push<float>(1); // Texture ID: 1 Float (ID)
        va2D->AddBuffer(vb2D, vertLayout2D);

        vb2D->PopulateBuffer(verts.data(), verts.size(), 0);
        ib2D->PopulateBuffer(indices.data(), indices.size(), 0);

        VertexBufferLayout InstanceLayout2D;
        InstanceLayout2D.PushMat4();
        InstanceLayout2D.Push<float>(1); // Texture ID: 1 Float (ID)
        InstanceLayout2D.Push<float>(2); // UVMin
        InstanceLayout2D.Push<float>(2); // UVMax
        iva2D->AddBuffer(ivb2D, InstanceLayout2D, 5);

        shader2D = new Bed::OpenShader("Assets/Resources/Shaders/Bed2D.shader");
        shader2D->Bind();

        shader2D->SetUniform1iv("u_Textures", 32, textureSlots);
    }
            
    //UI Shader
    {
        vaUI = new Bed::VertexArray();
        ivaUI = new Bed::InstanceArray();
        vbUI = new Bed::VertexBuffer(4000); // Store 3000 Bed::Vertex (pos, colour, texCoords, texID)
        ibUI = new Bed::IndexBuffer(6000);
        ivbUI = new Bed::InstanceBuffer(100, sizeof(InstanceData)); //100 instances

        //TODO: UI doesnt need normal
        VertexBufferLayout vertLayoutUI;
        vertLayoutUI.Push<float>(3); // Position: 3 Floats (x, y, z)
        vertLayoutUI.Push<float>(3); // Normal: 3 Floats (x, y, z)
        vertLayoutUI.Push<float>(4); // Colour: 4 Floats (r, g, b, a)
        vertLayoutUI.Push<float>(2); // TextureCoord: 2 Floats (x, y)
        vertLayoutUI.Push<float>(1); // Texture ID: 1 Float (ID)
        vaUI->AddBuffer(vbUI, vertLayoutUI);

        vbUI->PopulateBuffer(verts.data(), verts.size(), 0);
        ibUI->PopulateBuffer(indices.data(), indices.size(), 0);

        VertexBufferLayout InstanceLayoutUI;
        InstanceLayoutUI.PushMat4();
        InstanceLayoutUI.Push<float>(1); // Texture ID: 1 Float (ID)
        InstanceLayoutUI.Push<float>(2); // UVMin
        InstanceLayoutUI.Push<float>(2); // UVMax
        ivaUI->AddBuffer(ivbUI, InstanceLayoutUI, 5);

        shaderUI = new Bed::OpenShader("Assets/Resources/Shaders/BedUI.shader");
        shaderUI->Bind();

        shaderUI->SetUniform1iv("u_Textures", 32, textureSlots);
    }

    //Unbind Everything
    Bed::TextureManager::UnbindTextures();

    va3D->Unbind();
    shader3D->Unbind();
    vb3D->Unbind();
    ib3D->Unbind();
    ivb3D->Unbind();
    pointLightBuffer->Unbind();
    directionalLightBuffer->Unbind();
    spotLightBuffer->Unbind();

    va2D->Unbind();
    shader2D->Unbind();
    vb2D->Unbind();
    ib2D->Unbind();
    ivb2D->Unbind();

    vaUI->Unbind();
    shaderUI->Unbind();
    vbUI->Unbind();
    ibUI->Unbind();
    ivbUI->Unbind();*/

    return true;
}

void Bed::GLFWWindow::UpdateWindow()
{
    int width;
    int height;
    glfwGetWindowSize(window, &width, &height);
    ResizeWindow(width, height);

    /*
    // Render here 
    renderer->Clear();

    //Render Everything
    glEnable(GL_DEPTH_TEST);
    renderer->Draw(va3D, ib3D, shader3D);

    glEnable(GL_DEPTH_TEST);
    renderer->Draw(va2D, ib2D, shader2D);
    renderer->DrawInstanced(va2D, ib2D, ivb2D, shader2D);

    glDisable(GL_DEPTH_TEST);
    renderer->Draw(vaUI, ibUI, shaderUI);
    renderer->DrawInstanced(vaUI, ibUI, ivbUI, shaderUI);

    //Unbind Everything
    Bed::TextureManager::UnbindTextures();

    shader3D->Unbind();
    vb3D->Unbind();
    ib3D->Unbind();
    va3D->Unbind();
    ivb3D->Unbind();
    iva3D->Unbind();
    pointLightBuffer->Unbind();
    directionalLightBuffer->Unbind();
    spotLightBuffer->Unbind();

    shader2D->Unbind();
    vb2D->Unbind();
    ib2D->Unbind();
    va2D->Unbind();
    ivb2D->Unbind();
    iva2D->Unbind();

    shaderUI->Unbind();
    vbUI->Unbind();
    ibUI->Unbind();
    vaUI->Unbind();
    ivbUI->Unbind();
    ivaUI->Unbind();
    */

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
}

bool Bed::GLFWWindow::IsWindowOpen()
{
    return !glfwWindowShouldClose(window);
}

void Bed::GLFWWindow::CloseWindow()
{
    /*delete shader3D;
    delete shader2D;
    delete shaderUI;*/
    glfwTerminate();
}

void Bed::GLFWWindow::ResizeWindow(int width, int height)
{
    if(m_WindowSize.Width != width || m_WindowSize.Height != height)
    {
        //TODO: make this use Quilt
        glViewport(0, 0, width, height);
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