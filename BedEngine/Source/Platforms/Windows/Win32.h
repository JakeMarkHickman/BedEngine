#pragma once

#include <Platforms/Platform.h>

namespace Bed
{
    class Win32 : public Bed::Platform
    {
    public:
        Win32(Bed::EGraphicsAPIFlags pipeline)
        {
            AvaiableFlags.SetFlag(Bed::OpenGL);
            AvaiableFlags.SetFlag(Bed::Vulkan);
            AvaiableFlags.SetFlag(Bed::DirectX);

            m_DefaultFlag = Bed::OpenGL; //TODO: Set this to DirectX when its available

            UseGraphicsPipeline(pipeline);
        };
    private:
    };
}