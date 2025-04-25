#pragma once

namespace Bed
{
    struct ClickableUnhovered
    {
        ClickableUnhovered(double cursorx, double cursory) : CursorX(cursorx), CursorY(cursory) {};

        double CursorX;
        double CursorY;
    };
}

