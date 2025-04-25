#pragma once

namespace Bed
{
    enum class AnchorPoint
    {
        TopLeft, 
        Top, 
        TopRight, 
        Right,
        BottomRight,
        Bottom, 
        BottomLeft,
        Left,
        Centre
    };

    struct UIElement
    {
        UIElement() {};

        AnchorPoint Anchor = AnchorPoint::Centre;

        bool Enabled = true;
        int ZOrder = 0;
        float Opacity = 1.0f;
    };
}