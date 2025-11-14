#pragma once

#include <Transform.h>
#include <vector>

namespace Quilt
{
    struct Camera
    {
        bool IsActive = true;

        const Pillow::Transform* Transform;

        float XScreenOffset = 0.0f;
        float YScreenOffset = 0.0f;
        float ScreenWidth = 1.0f;
        float ScreenHeight = 1.0f;
    };
}