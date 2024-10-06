#pragma once

namespace Bed
{
    enum RenderType
    {
        Orthographic = 0,
        Projection = 1
    };

    struct Camera
    {
        Camera(Bed::RenderType renderType) : m_RenderType(renderType) {};

        Bed::RenderType m_RenderType = Bed::RenderType::Orthographic;
    };
}