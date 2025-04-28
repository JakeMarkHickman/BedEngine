#pragma once

namespace Bed
{
    struct Timer
    {
        Timer() {};
        Timer(float duration = 1.0f, bool isActive = true, bool isLooping = false) : Duration(duration), IsActive(isActive), IsLooping(isLooping) {};

        float Elapsed = 0.0f;
        float Duration = 1.0f;

        bool IsActive = true;
        bool IsLooping = false;
    };
    
}