#include "Core_PCH.h"
#include "FrameTimeManager.h"

#include "Kernel/Time/Timer.h"

CFrameTimeManager::CFrameTimeManager()
    : m_currentGameTime (0.03f)
{

}

CFrameTimeManager::~CFrameTimeManager()
{
}

Bool CFrameTimeManager::Init ( )
{
    m_timer = THOT_NEW CTimer;

    return true;
}


float CFrameTimeManager::GetGameTime( )
{
    return m_currentGameTime;
}

void CFrameTimeManager::OnBeginFrame( )
{
    m_timer->Start();
}

void CFrameTimeManager::OnEndFrame  ( )
{
    u64 deltaMicro =m_timer->Stop();;
    m_currentGameTime = (float)( (double)deltaMicro * 0.000001 );

    if( m_currentGameTime > 0.03f )
    {
        m_currentGameTime = 0.03f;
    }
}
