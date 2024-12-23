#pragma once

#include <chrono>

namespace Bed
{
    class DeltaTime
    {
    public:
        float CalculateDeltaTime();
        

    private:
        float m_DeltaTime = 0;
        std::chrono::time_point<std::chrono::steady_clock> m_LastRecordedTime;
    };
}