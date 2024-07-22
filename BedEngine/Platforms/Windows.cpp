#include <GraphicsAPI.h>
#include <OpenGL/OpenGl.h>

//////////////////////////////////////////////////////////////////
//                         Functions                            //
//////////////////////////////////////////////////////////////////

// TODO: Make this more optimised, some ways of doing this could be that the platform.h is removed completly and this functionality is moved into the Graphics folder.
// Dont do that however as I may want to create windows myself

GraphicsAPI::GraphicsAPIFlags AvailableFlags;
GraphicsAPI::GraphicsAPIFlags CurrentFlag = GraphicsAPI::OpenGL;

bool CreateWindow(int width, int height, const char* title)
{   
    bool WindowCreated;
    switch (CurrentFlag) //This Checks to See what the Current 
    {
        case GraphicsAPI::OpenGL:
            WindowCreated = OpenGLCreateWindow(width, height, title);
            break;
        case GraphicsAPI::Vulkan:
            CurrentFlag = GraphicsAPI::Vulkan;
            WindowCreated = false;
            break;
        case GraphicsAPI::DirectX:
            WindowCreated = false;
            CurrentFlag = GraphicsAPI::DirectX;
            break;
        case GraphicsAPI::Metal:
            WindowCreated = false;
            break;
    }

    return WindowCreated;
}

void UpdateWindow()
{
    switch (CurrentFlag)
    {
        case GraphicsAPI::OpenGL:
            OpenGLUpdateWindow();
            CurrentFlag = GraphicsAPI::OpenGL;
            break;
        case GraphicsAPI::Vulkan:
            CurrentFlag = GraphicsAPI::Vulkan;
            break;
        case GraphicsAPI::DirectX:
            CurrentFlag = GraphicsAPI::DirectX;
            break;
        case GraphicsAPI::Metal:
            break;
    }
    
}

bool IsWindowOpen()
{
    bool WindowOpen = false;
    switch (CurrentFlag)
    {
        case GraphicsAPI::OpenGL:
            WindowOpen = OpenGLIsWindowOpen();
            CurrentFlag = GraphicsAPI::OpenGL;
            break;
        case GraphicsAPI::Vulkan:
            CurrentFlag = GraphicsAPI::Vulkan;
            break;
        case GraphicsAPI::DirectX:
            CurrentFlag = GraphicsAPI::DirectX;
            break;
        case GraphicsAPI::Metal:
            break;
    }
    return WindowOpen;
}

void CloseWindow()
{
    switch (CurrentFlag)
    {
        case GraphicsAPI::OpenGL:
            OpenGLCloseWindow();
            CurrentFlag = GraphicsAPI::OpenGL;
            break;
        case GraphicsAPI::Vulkan:
            CurrentFlag = GraphicsAPI::Vulkan;
            break;
        case GraphicsAPI::DirectX:
            CurrentFlag = GraphicsAPI::DirectX;
            break;
        case GraphicsAPI::Metal:
            break;
    }
}
