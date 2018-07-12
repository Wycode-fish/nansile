//
//  Timer.hpp
//  bird
//
//  Created by 汪依尘 on 6/18/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef Timer_hpp
#define Timer_hpp

#include <stdio.h>
#include <chrono>

class Timer
{
public:
    Timer(double duration = 0.0f);
public:
    static std::chrono::time_point<std::chrono::high_resolution_clock> GetCurrentTime();
    static double MsSince(std::chrono::time_point<std::chrono::high_resolution_clock> startTime);
    static Timer DurationClock(double duration);
    static Timer DeltaClock();
public:
    bool DurationAlarm();
    double GetDelta();
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_DuraClk_UpdatePoint;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_DeltaClk_UpdatePoint;
    double m_DuraClk_Duration;
};
#endif /* Timer_hpp */
