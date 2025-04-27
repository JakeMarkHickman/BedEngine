#pragma once

#include <Platforms/Window.h>
#include <Graphics/GraphicVariables.h>

//TODO: Remove this
#include <Graphics/OpenGL/OpenTexture.h>
#include <Graphics/OpenGL/OpenShader.h>
#include <Graphics/TextureManager.h>

namespace Bed
{
    class GLFWWindow : public Bed::Window
    {
    public:
        //GLFWWindow(Bed::Platform* platform);

        virtual bool CreateWindow(int width, int height, const char* title);
        virtual void UpdateWindow();
        virtual bool IsWindowOpen();
        virtual void CloseWindow();
        virtual void ResizeWindow(int width, int height);
        virtual void RenameWindow(const char* title);

        //TODO: This is for testing only
        static GLFWwindow* GetWindow() { return window; };

    private:
        static inline GLFWwindow* window = nullptr;
    };
}