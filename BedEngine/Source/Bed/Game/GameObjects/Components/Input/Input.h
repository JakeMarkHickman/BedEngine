#pragma once

#include <unordered_map>

namespace Bed
{
    enum class KeyState
    {
        Released,
        Pressed,
        Hold
    };

    struct Input
    {
        Input() {};

        std::unordered_map<int, KeyState> KeyData;
        std::unordered_map<int, KeyState> MouseData;
        double CursorX, CursorY;

        std::unordered_map<int, KeyState> PreviousKeyData;
        std::unordered_map<int, KeyState> PreviousMouseData;
    };
}