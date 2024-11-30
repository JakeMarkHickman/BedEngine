#pragma once

#include <Bed/Core.h>

namespace Bed
{
    enum RenderType
    {
        Orthographic = 0,
        Projection = 1
    };

    struct BED_API Camera
    {
        Camera(Bed::RenderType renderType) : m_RenderType(renderType) {};

        Bed::RenderType m_RenderType = Bed::RenderType::Orthographic;
    };
}