#include "Kernel_PCH.h"
#include "Thread.h"
#include "AutoLock.h"
#include "Kernel/ThotWindows.h"
#include "Kernel/KernelUtils.h"


//-----------------------------------------------------
typedef CAutoLock<CCritSection> ThreadAutoLock;

//-----------------------------------------------------
class CThreadEntryPoint
{
public:
    static DWORD __stdcall EntryPoint( void* threadObj )
    {
        CThread* _this = reinterpret_cast<CThread*>(threadObj);
        _this->EntryPoint();
        return 0;
    }
};

//-----------------------------------------------------
CThread::CThread()
    : m_nativeThreadHandle      ( NULL )
    , m_state                   (EThreadState_Stopped)
    , m_affinity                ( 0xffffffff )
{
}

//-----------------------------------------------------
CThread::~CThread()
{
    ThreadAutoLock lock(m_criticalSection);
    m_state = EThreadState_Stopped;


}

//-----------------------------------------------------
void CThread::EntryPoint()
{
    {
        ThreadAutoLock lock(m_criticalSection);
        m_state =  EThreadState_Running;
    }
    Run();

    {
        ThreadAutoLock lock(m_criticalSection);
        m_state = EThreadState_Stopped;
    }
}

//-----------------------------------------------------
void CThread::SetDebugName( const char* threadDebugName )
{
    ThreadAutoLock lock(m_criticalSection);
    //[TODO]
}

//-----------------------------------------------------
bool CThread::Start( u32 stackSize, TAffinity affinity, EThreadPriority priority )
{
    SStartupParams params;
    params.m_stackSize = stackSize;
    params.m_affinity = affinity;
    params.m_priority = priority;

    InternalStart(params);
    return true;
}

//-----------------------------------------------------
bool CThread::InternalStart( const SStartupParams& params )
{
    ThreadAutoLock lock(m_criticalSection);

    if( !IsStopped()) 
    {
        // thread already started
        return false;
    }

    if( !CreateNativeHandleSuspended( params ) )
    {
        return false;
    }

    SetAffinity( params.m_affinity );
    SetPriority( params.m_priority);
    m_state = EThreadState_Paused;

    Resume();

    return true;
}

//-----------------------------------------------------
void CThread::Pause()
{
    if( GetCurrentThreadID() == m_nativeThreadID )
    {
        // a thread cannot pause itself
        return;
    }
    
    ThreadAutoLock lock(m_criticalSection);

    if( IsRunning() )
    {
        SuspendThread( m_nativeThreadHandle );
        m_state = EThreadState_Paused;
    }
}

//-----------------------------------------------------
void CThread::Resume()
{
    if( !IsPaused())
    {
        return;
    }

    ThreadAutoLock lock(m_criticalSection);
    
    DWORD count;
    do 
    {
        count = ResumeThread( m_nativeThreadHandle );
    } while (count > 1);

    m_state = EThreadState_Running;
}

//-----------------------------------------------------
bool CThread::WaitUntilStopped( u32 timeout )
{
    if( m_nativeThreadHandle )
    {
        DWORD ret = WaitForSingleObject( m_nativeThreadHandle, timeout );
        return ret != WAIT_TIMEOUT;
    }
    return true;
}

//-----------------------------------------------------
bool CThread::CreateNativeHandleSuspended( const SStartupParams& startupParams )
{
    DWORD threadID;
    m_nativeThreadHandle = CreateThread(
                                         NULL
                                        ,startupParams.m_stackSize
                                        ,&CThreadEntryPoint::EntryPoint
                                        ,this
                                        ,CREATE_SUSPENDED
                                        ,&threadID
                                        );
    if( !m_nativeThreadHandle )
    {
        return false;
    }
    m_nativeThreadID = (ThreadID)threadID;

    return true;
}

//--------------------------------------------------------
CThread::ThreadID CThread::GetCurrentThreadID()
{
    return (ThreadID)GetCurrentThreadId();
}

//--------------------------------------------------------
void CThread::SetPriority ( EThreadPriority priority)
{
    if( m_nativeThreadHandle )
    {
        SetThreadPriority( m_nativeThreadHandle, priority );
    }
}

//--------------------------------------------------------
bool CThread::SetAffinity ( TAffinity mask )
{
    if(!m_nativeThreadHandle)
    {
        return false;
    }

    DWORD_PTR oldAffinityMask = 0;
    DWORD_PTR newAffinity = ThNumericCast<DWORD_PTR>( mask );
    if( (oldAffinityMask = SetThreadAffinityMask( m_nativeThreadHandle, newAffinity ) ) == 0 )
    {
        return false;
    }
    m_affinity = mask;
    return true;
}