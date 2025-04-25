#pragma once

#include <Components/Input/Input.h>

#include <unordered_set>

namespace Bed
{
    struct ClickableClicked
    {
        ClickableClicked(double cursorx, double cursory, std::unordered_set<int> pressedButtons) : CursorX(cursorx), CursorY(cursory), PressedButtons(pressedButtons) {};

        double CursorX;
        double CursorY;

        std::unordered_set<int> PressedButtons;
    };
    
}