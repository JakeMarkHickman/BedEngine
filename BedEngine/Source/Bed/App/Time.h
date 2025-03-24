#pragma once

#include <chrono>

namespace Bed
{
    class Time
    {
    public:
        static float GetDeltaTime() { return m_DeltaTime; };
        void CalculateDeltaTime();
    private:
        inline static float m_DeltaTime = 0.0f;
    
        std::chrono::time_point<std::chrono::steady_clock> m_LastTimePoint;
    };    
}