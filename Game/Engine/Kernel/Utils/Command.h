#if !defined(__KERNEL_COMMAND_H__)
#define __KERNEL_COMMAND_H__

#include "Kernel/DebugSystem/DebugSystem.h"

class KERNEL_API ICommand
{

public:
    ICommand()
        : m_done (false)
    {
    
    }

    virtual    ~ICommand();

    virtual void    OnDone(){} 

    void                Execute()
    {
        InternalExecute();
        m_done = true;
        OnDone();
    }

    virtual     void    InternalExecute()           = 0;

    Bool        IsDone(){ return m_done;}

private:
    Bool            m_done;
};


#endif //__KERNEL_COMMAND_H__