#pragma once

#include <vector>

#include "UVFrame.h"

namespace Bed
{
    struct UVAnimation
    {
        UVAnimation(std::vector<Bed::UVFrame> frames, int fps, bool isLooping) : Frames(frames), FPS(fps), Looping(isLooping) {};

        std::vector<Bed::UVFrame> Frames;
        int FPS;
        int CurrentFrame = 0;
        float CurrentTime = 0.0f;
        bool Looping; //If false holds on last frame
    };
}