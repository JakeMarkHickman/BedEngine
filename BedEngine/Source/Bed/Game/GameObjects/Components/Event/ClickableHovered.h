#pragma once

namespace Bed
{
    struct ClickableHovered
    {
        ClickableHovered(double cursorx, double cursory) : CursorX(cursorx), CursorY(cursory) {};

        double CursorX;
        double CursorY;
    };
}