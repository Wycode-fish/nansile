//
//  Timer.cpp
//  bird
//
//  Created by 汪依尘 on 6/18/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "Timer.hpp"
#include <iostream>


Timer::Timer(double duration)
: m_DuraClk_UpdatePoint(GetCurrentTime()), m_DuraClk_Duration(duration)
{
    
}

std::chrono::time_point<std::chrono::high_resolution_clock>  Timer::GetCurrentTime()
{
    auto current = std::chrono::high_resolution_clock::now();
    return current;
}

double Timer::MsSince(std::chrono::time_point<std::chrono::high_resolution_clock> startTime)
{
//    std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - startTime;
//    return elapsed.count() * 1000;
    
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - startTime).count() / 1000.0f;
}

Timer Timer::DurationClock(double duration)
{
    return Timer(duration);
}

Timer Timer::DeltaClock()
{
    return Timer();
}

double Timer::GetDelta()
{
    double delta = MsSince(m_DeltaClk_UpdatePoint) / 1000.0f;
    m_DeltaClk_UpdatePoint = std::chrono::high_resolution_clock::now();
    return delta;
}

bool Timer::DurationAlarm()
{
    double duration = MsSince(m_DuraClk_UpdatePoint);
    bool res = duration/m_DuraClk_Duration >= 1.0f;
    if (res)
        m_DuraClk_UpdatePoint = GetCurrentTime();
    return res;
}

