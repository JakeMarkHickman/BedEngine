#pragma once

namespace Bed
{
    struct UIElement
    {
        UIElement() {};

        bool Enabled = true;
        int ZOrder = 0;
        float Opacity = 1.0f;
    };
}