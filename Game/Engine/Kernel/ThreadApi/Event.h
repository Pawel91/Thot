#if !defined(__KERNEL_EVENT_H__)
#define __KERNEL_EVENT_H__

#include "Kernel/Basics.h"


class CThreadEvent
{
    typedef void*   TNativeEventHandle;

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
     CThreadEvent( const char* eventName );
    ~CThreadEvent();


//*********************************************
//            INTERFACE
//*********************************************
public:
    void        Signal          ( );
    void        WaitUntilDone   ( u32 timeout );


//*********************************************
//            MEMBERS
//*********************************************
protected:
    TNativeEventHandle      m_nativeEventHandle;

};


#endif //__KERNEL_EVENT_H__