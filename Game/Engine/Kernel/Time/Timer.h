#if !defined(__KERNEL_TIMER_H__)
#define __KERNEL_TIMER_H__

#include "Kernel/Basics.h"


class KERNEL_API CTimer
{
public:
    typedef u64     TimeUnits;

public:
    CTimer();


public:
    void                Start   ( );
    TimeUnits           Stop    ( ); // returns delta time units from start
    CTimer::TimeUnits   GetTimerValue( );

    static u64      GetMicroseconds ( CTimer::TimeUnits deltaTime );
    static u64      GetMiliseconds  ( CTimer::TimeUnits deltaTime );
    static u64      GetSeconds      ( CTimer::TimeUnits deltaTime );
    


private:
    void    BuildTimerInfo();

private:
    TimeUnits           m_startTime;
    TimeUnits           m_endTime;
    
};

#endif