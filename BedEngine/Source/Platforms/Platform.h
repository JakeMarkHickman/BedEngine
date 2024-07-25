#pragma once
#include <iostream>
#include <Graphics/GraphicsAPI.h>

namespace Bed
{
    enum PlatformTypes 
    {
        Linux,
        Mac,
        Windows
    };

    class Platform
    {
    public:
        Platform() {};
        ~Platform() {};

        virtual bool PlatformCreateWindow(int width, int height, char* title) { std::cout << "No Platform Avaliable" << std::endl; return false; };
        virtual void PlatformUpdateWindow() {};
        virtual bool PlatformIsWindowOpen() { return false; };
        virtual void PlatformCloseWindow() {};

    protected:
        GraphicsAPI::SGraphicAPIFlags AvaiableFlags;
        GraphicsAPI::EGraphicsAPIFlags m_CurrentFlag = GraphicsAPI::OpenGL;

    private:

    }; 
}