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

        virtual bool PlatformCreateWindow(int width, int height, const char* title, GraphicsAPI::EGraphicsAPIFlags Pipeline) { std::cout << "No Platform Avaliable" << std::endl; return false; };
        virtual void PlatformUpdateWindow() {};
        virtual bool PlatformIsWindowOpen() { return false; };
        virtual void PlatformCloseWindow() {};

    protected:
        GraphicsAPI::SGraphicAPIFlags AvaiableFlags;
        GraphicsAPI::EGraphicsAPIFlags m_CurrentFlag = GraphicsAPI::OpenGL;

        GraphicsAPI::EGraphicsAPIFlags UseGraphicsPipeline(GraphicsAPI::EGraphicsAPIFlags Pipeline)
        {
            GraphicsAPI::EGraphicsAPIFlags UsePipeline = Pipeline;

            if(!AvaiableFlags.HasFlag(UsePipeline) || UsePipeline == 0)
            {
                std::cout << UsePipeline << " is not allowed on Windows or isn't valid, Switching to OpenGL" << std::endl;
                UsePipeline = GraphicsAPI::OpenGL;
            }

            std::cout << "Using graphics pipeline: " << UsePipeline << std::endl;

            return UsePipeline;
        };

    private:

    }; 
}