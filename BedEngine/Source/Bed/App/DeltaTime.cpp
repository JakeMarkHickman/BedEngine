#include "DeltaTime.h"

float Bed::DeltaTime::CalculateDeltaTime()
{
    static bool DoneatleastOnce = false;

    if(!DoneatleastOnce)
    {
        DoneatleastOnce = true;
        m_LastRecordedTime = std::chrono::steady_clock::now();
        return 0.0f;
    }
        
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = currentTime - m_LastRecordedTime;

    m_DeltaTime = elapsed.count();

    m_LastRecordedTime = currentTime;
    return m_DeltaTime;
}