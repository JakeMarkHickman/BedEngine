#pragma once

namespace Bed
{
    //TODO: Implement ZOrder
    struct UIElement
    {
        UIElement() {};

        bool Enabled = true;
        int ZOrder = 0;
        float Opacity = 1.0f;
    };
}