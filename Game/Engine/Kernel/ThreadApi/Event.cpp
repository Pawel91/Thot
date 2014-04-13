#include "Kernel_PCH.h"
#include "Kernel/ThreadApi/Event.h"


#include "Kernel/ThotWindows.h"

//--------------------------------------------------------------------------------
CThreadEvent::CThreadEvent( const char* eventName )
    :m_nativeEventHandle (NULL)
{
    m_nativeEventHandle = CreateEventA(
                                         NULL
                                        ,TRUE   // manual reset
                                        ,FALSE  // initial state not signaled
                                        ,eventName
                                    );

}

//--------------------------------------------------------------------------------
CThreadEvent::~CThreadEvent()
{
    if(m_nativeEventHandle)
    {
        CloseHandle( m_nativeEventHandle );
    }

}

//--------------------------------------------------------------------------------
void CThreadEvent::Signal( )
{
    BOOL result = SetEvent( m_nativeEventHandle );
    THOT_ASSERT( result == TRUE );
}

//--------------------------------------------------------------------------------
void CThreadEvent::WaitUntilDone( u32 timeout )
{

}

