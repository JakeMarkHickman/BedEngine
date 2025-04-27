#pragma once
#include <iostream>
#include <Graphics/GraphicsAPI.h>

namespace Bed
{
    class Platform
    {
    public:

    protected:
        void UseGraphicsPipeline(GraphicsAPI::EGraphicsAPIFlags Pipeline)
        {
            GraphicsAPI::EGraphicsAPIFlags UsePipeline = Pipeline;

            if(!AvaiableFlags.HasFlag(UsePipeline) || UsePipeline == 0)
            {
                std::cout << UsePipeline << " is not allowed on this platform or isn't valid, Switching to Default" << std::endl;
                UsePipeline = m_DefaultFlag;
            }

            m_CurrentFlag = UsePipeline;
        };

        GraphicsAPI::SGraphicAPIFlags AvaiableFlags;
        GraphicsAPI::EGraphicsAPIFlags m_DefaultFlag;
        GraphicsAPI::EGraphicsAPIFlags m_CurrentFlag = GraphicsAPI::OpenGL;

    private:
    }; 
}