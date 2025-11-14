#pragma once
#include <iostream>
//#include <Graphics/GraphicsAPI.h>

namespace Bed
{
    enum EGraphicsAPIFlags
    {
        OpenGL = 1 << 0,
        Vulkan = 1 << 1,
        DirectX = 1 << 2,
        Metal = 1 << 3
    };

    struct SGraphicAPIFlags
    {
        uint8_t m_AvailableFlags = 0;

        void SetFlag(EGraphicsAPIFlags Flag)
        {
            m_AvailableFlags |= (int)Flag;
        }

        bool HasFlag(EGraphicsAPIFlags Flag)
        {
            return (m_AvailableFlags & (int)Flag) == (int)Flag;
        }
    };

    class Platform
    {
    public:

    protected:
        void UseGraphicsPipeline(Bed::EGraphicsAPIFlags Pipeline)
        {
            Bed::EGraphicsAPIFlags UsePipeline = Pipeline;

            if(!AvaiableFlags.HasFlag(UsePipeline) || UsePipeline == 0)
            {
                std::cout << UsePipeline << " is not allowed on this platform or isn't valid, Switching to Default" << std::endl;
                UsePipeline = m_DefaultFlag;
            }

            m_CurrentFlag = UsePipeline;
        };

        Bed::SGraphicAPIFlags AvaiableFlags;
        Bed::EGraphicsAPIFlags m_DefaultFlag;
        Bed::EGraphicsAPIFlags m_CurrentFlag = Bed::OpenGL;

    private:
    }; 
}