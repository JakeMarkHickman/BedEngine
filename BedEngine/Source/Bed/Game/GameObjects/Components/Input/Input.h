#pragma once

#include <unordered_map>

namespace Bed
{
    enum class KeyState
    {
        Released,
        Press,
        Hold
    };

    struct Input
    {
        Input() {};

        std::unordered_map<int, KeyState> KeyData;
    };
}