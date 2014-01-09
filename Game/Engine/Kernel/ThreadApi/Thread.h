#if !defined(__KERNEL_THREAD_H__)
#define __KERNEL_THREAD_H__

#include "Kernel/KernelDef.h"
#include "Kernel/ThreadApi/CriticalSection.h"


enum EThreadState
{
     EThreadState_Paused
    ,EThreadState_Stopped
    ,EThreadState_Running
};

enum EThreadPriority
{
     EThreadPriority_Idle = -15
    ,EThreadPriority_BelowNormal = -1
    ,EThreadPriority_Normal = 0
    ,EThreadPriority_AboveNormal = 1
    ,EThreadPriority_Highest = 2
    ,EThreadPriority_TimeCritical = 15

};

enum
{
    THREAD_DEFAULT_STACK_SIZE = 0 // when 0 is used the system will choose the best stack size of the thread
};

class KERNEL_API CThread
{
public:

    enum
    {
        InfiniteTimeout = 0xFFFFFFFF
    };

    friend class CThreadEntryPoint;

    typedef u32     ThreadID;
    typedef void*   TNativeHandle;
    typedef u32     TAffinity;
    struct SStartupParams
    {
        SStartupParams()
            : m_stackSize   ( 16 * 1024 )
            , m_priority    ( EThreadPriority_Normal )
            , m_affinity    (0xffffffff)
        {
        }

        u32                 m_stackSize;
        EThreadPriority     m_priority;
        TAffinity           m_affinity;
    };


public:
                CThread();
    virtual    ~CThread();

public:
            void            Pause();
            void            Resume();
            bool            Start( u32 stackSize, TAffinity affinity, EThreadPriority priority = EThreadPriority_Normal );
            bool            WaitUntilStopped    ( u32 timeout = InfiniteTimeout );

            bool            SetAffinity ( TAffinity mask );
            void            SetPriority ( EThreadPriority priority);
            void            SetDebugName( const char* threadDebugName );
            EThreadState    GetState()  { return m_state;}
    inline  ThreadID        GetID()     { return m_nativeThreadID;}
    inline  bool            IsRunning() { return GetState() == EThreadState_Running;}
    inline  bool            IsPaused()  { return GetState() == EThreadState_Paused;}
    inline  bool            IsStopped() { return GetState() == EThreadState_Stopped;}

public:
    static ThreadID         GetCurrentThreadID();

   
protected:
            bool        InternalStart( const SStartupParams& params );

    virtual void        Run()      = 0;

private:
            void    EntryPoint();
            bool    CreateNativeHandleSuspended( const SStartupParams& startupParams );

private:
    TAffinity               m_affinity;
    EThreadState            m_state;
    TNativeHandle           m_nativeThreadHandle;
    ThreadID                m_nativeThreadID;

protected:
    CCritSection            m_criticalSection;
};


#endif //__KERNEL_THREAD_H__