#pragma once

#include <Platforms/Platform.h>

#ifdef BED_LINUX_PLATFORM

#elif BED_MAC_PLATFORM

#elif BED_WINDOWS_PLATFORM
    #include <Platforms/Windows/Win32.h>
#endif

namespace Bed
{
    struct WindowSize 
    {
        int Width = 0;
        int Height = 0;
    };

    class Window
    {
    public:
        //Window(Bed::Platform* platform) { m_Platform = platform; };

        virtual bool CreateWindow(int width, int height, const char* title) = 0;
        virtual void UpdateWindow() = 0;
        virtual bool IsWindowOpen() = 0;
        virtual void CloseWindow() = 0;

        virtual void SetWindowIcon(std::string path) = 0;

        virtual void ResizeWindow(int width, int height) 
        {
            m_WindowSize.Width = width;
            m_WindowSize.Height = height;
        };
        virtual void RenameWindow(const char* title)
        {
            m_WindowTitle = title;
        };

        static float GetAspectRatio() { return (m_WindowSize.Height <= 0.0f || m_WindowSize.Width <= 0.0f) ? 0.1f : (float)m_WindowSize.Width / (float)m_WindowSize.Height; };
        static WindowSize GetWindowSize() { return m_WindowSize; };
        static const char* GetWindowTitle() { return m_WindowTitle; };

    protected:
        static inline WindowSize m_WindowSize;
        static inline const char* m_WindowTitle;

        Platform* m_Platform = nullptr;
    };
}