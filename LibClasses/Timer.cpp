#include "Timer.h"

Timer::Timer() : m_running(false) {}

void Timer::Start()
{
    m_startTime = std::chrono::high_resolution_clock::now();
    m_running = true;
}

void Timer::Stop()
{
    m_endTime = std::chrono::high_resolution_clock::now();
    m_running = false;
}

double Timer::GetElapsedMilliseconds() const
{
    std::chrono::time_point<std::chrono::high_resolution_clock> endTime;

    if (m_running)
    {
        endTime = std::chrono::high_resolution_clock::now();
    }
    else
    {
        endTime = m_endTime;
    }

    return std::chrono::duration<double, std::milli>(endTime - m_startTime).count();
}
