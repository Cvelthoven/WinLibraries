//---------------------------------------------------------------------------------------
//
// Module: Timer.cpp
//
// Timer class functions.
//
//---------------------------------------------------------------------------------------
//
// Include files of class libraries
#include "Timer.h"

//---------------------------------------------------------------------------------------
//
// Timer constructor
//
Timer::Timer() : m_running(false) {}

//---------------------------------------------------------------------------------------
//
// Start the timer
//
void Timer::Start()
{
    m_startTime = std::chrono::high_resolution_clock::now();
    m_running = true;
}

//---------------------------------------------------------------------------------------
//
// Stop the timer
//
void Timer::Stop()
{
    m_endTime = std::chrono::high_resolution_clock::now();
    m_running = false;
}

//---------------------------------------------------------------------------------------
//
// Get the elapsed time in milliseconds
//
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
