//---------------------------------------------------------------------------------------
// Timer.h
// 
// This is the header file of the timer class.
// 
//---------------------------------------------------------------------------------------
#pragma once

//---------------------------------------------------------------------------------------
//
// Include files of general use libraries
//
#include <chrono>

//---------------------------------------------------------------------------------------
//
// Class definition: Timer
//
class Timer
{
public:
    //-----------------------------------------------------------------------------------
    //
    // Constructor
    Timer();
    //-----------------------------------------------------------------------------------
    // Public functions of the timer class
    //
    void Start();
    void Stop();
    double GetElapsedMilliseconds() const;

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_endTime;
    bool m_running;
};
