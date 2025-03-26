#include "Time.h"

void Bed::Time::CalculateDeltaTime()
{
    if(m_LastTimePoint == std::chrono::time_point<std::chrono::steady_clock>()) // check if m_LastTimePoint is initialised
    {
        m_LastTimePoint = std::chrono::steady_clock::now();
        return;
    }

    std::chrono::time_point<std::chrono::steady_clock> currentTime = std::chrono::steady_clock::now(); //Get current time
    std::chrono::duration<double> elapsed = currentTime - m_LastTimePoint;
    m_LastTimePoint = currentTime;

    m_DeltaTime = elapsed.count();
}