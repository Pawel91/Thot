#include "Kernel_PCH.h"
#include "Timer.h"

#if defined(THOT_PLATFORM_WINDOWS)
#include "Kernel/ThotWindows.h"



LARGE_INTEGER GetFrequency()
{
    LARGE_INTEGER frequency;
    if( !QueryPerformanceFrequency(&frequency) )
    {
        THOT_ASSERT(false, "Failed to init timer");
    }

    return frequency;
}

static const LARGE_INTEGER g_frequency = GetFrequency( );



CTimer::CTimer()
    :m_startTime ( 0 )
{
}

THOT_COMPILE_ASSERT( sizeof(LARGE_INTEGER) == sizeof(CTimer::TimeUnits) );

void    CTimer::Start()
{
    if( !QueryPerformanceCounter( (LARGE_INTEGER*)&m_startTime ) )
    {
        THOT_ASSERT(false, "CTimer: Failed to get start time");
    }
}

CTimer::TimeUnits CTimer::Stop()
{
    if( !QueryPerformanceCounter( (LARGE_INTEGER*)&m_endTime) )
    {
        THOT_ASSERT(false, "CTimer: Failed to get end time");
    }

    return (CTimer::TimeUnits)( m_endTime - m_startTime) / (g_frequency.QuadPart/1000000);
}

CTimer::TimeUnits CTimer::GetTimerValue( )
{
    return (CTimer::TimeUnits)( m_endTime - m_startTime) / (g_frequency.QuadPart/1000000);
}


u64 CTimer::GetMicroseconds ( CTimer::TimeUnits deltaTime )
{
    return deltaTime;
}

u64 CTimer::GetMiliseconds( CTimer::TimeUnits deltaTime )
{
    return deltaTime / 1000;
}

u64 CTimer::GetSeconds      ( CTimer::TimeUnits deltaTime )
{
    return GetMiliseconds( deltaTime ) / 1000;
}



#else
#   error UNKNOWN PLATFORM
#endif//THOT_PLATFORM_WINDOWS
