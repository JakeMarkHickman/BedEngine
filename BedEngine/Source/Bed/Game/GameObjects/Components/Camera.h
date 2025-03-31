#pragma once

namespace Bed
{
    enum ProjectionType 
    {
        Orthographic = 0,
        Perspective = 1
    };

    struct Camera
    {
        Camera() {};
        Camera(Bed::ProjectionType projectionType) : ProjectionType(projectionType) {};

        Bed::ProjectionType ProjectionType = Bed::ProjectionType::Perspective;
    };
}