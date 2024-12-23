#include "DeltaTime.h"

float Bed::DeltaTime::CalculateDeltaTime()
{
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = currentTime - m_LastRecordedTime;

    m_DeltaTime = elapsed.count();

    m_LastRecordedTime = currentTime;
    return m_DeltaTime;
}