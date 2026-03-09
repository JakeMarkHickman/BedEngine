#pragma once

#include <Platforms/Window.h>

//TODO: This needs to change
#include <GLFW/glfw3.h>

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
        virtual void SetWindowIcon(std::string path);
        virtual void ResizeWindow(int width, int height);
        virtual void RenameWindow(const char* title);

        //TODO: This is for testing only
        static GLFWwindow* GetWindow() { return window; };

    private:
        static inline GLFWwindow* window = nullptr;
    };
}