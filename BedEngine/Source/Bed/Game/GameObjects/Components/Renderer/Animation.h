#pragma once

#include <string>
#include <vector>

namespace Bed
{
    struct Animation
    {
        std::string Name;
        std::vector<int> KeyFrames;

        float FrameRate;

        bool Looping;
    }
}