#pragma once

namespace Bed
{
    struct ClickableReleased
    {
        ClickableReleased(double cursorx, double cursory, std::unordered_set<int> releasedButtons) : CursorX(cursorx), CursorY(cursory), ReleasedButtons(releasedButtons) {};

        double CursorX;
        double CursorY;

        std::unordered_set<int> ReleasedButtons;
    };
}