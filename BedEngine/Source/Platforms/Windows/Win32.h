#pragma once

#include <Platforms/Platform.h>

namespace Bed
{
    class Win32 : public Bed::Platform
    {
    public:
        Win32(GraphicsAPI::EGraphicsAPIFlags pipeline)
        {
            AvaiableFlags.SetFlag(GraphicsAPI::OpenGL);
            AvaiableFlags.SetFlag(GraphicsAPI::Vulkan);
            AvaiableFlags.SetFlag(GraphicsAPI::DirectX);

            m_DefaultFlag = GraphicsAPI::OpenGL; //TODO: Set this to DirectX when its available

            UseGraphicsPipeline(pipeline);
        };
    private:
    };
}