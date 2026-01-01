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
        Camera(float xScreenPosition, float yScreenPosition, float xScreenSize, float yScreenSize) : XScreenPosition(xScreenPosition), YScreenPosition(yScreenPosition), XScreenSize(xScreenSize), YScreenSize(yScreenSize) {};

        Bed::ProjectionType ProjectionType = Bed::ProjectionType::Perspective;

        unsigned int Handle;
        bool Active = true;

        float FOV = 90.0f;
        float Zoom = 5.0f;

        float XScreenPosition = 0.0f;
        float YScreenPosition = 0.0f;
        float XScreenSize = 1.0f;
        float YScreenSize = 1.0f;
    };
}