#include "Kernel_PCH.h"
#include "Kernel/MemoryManagement/MemoryUtils.h"
#include "Kernel/ThotWindows.h"
#include "Winnt.h"


struct _TEB
{
   NT_TIB NtTib;
   // Ignore rest of struct
};

Bool IsPointerOnStack( void* ptr )
{

    _TEB* threadEnvironmentBlock =  NtCurrentTeb();
    void* stackBase = threadEnvironmentBlock->NtTib.StackBase;
    void* stackLimit = threadEnvironmentBlock->NtTib.StackLimit;
    
    if( ptr >= stackLimit && ptr <= stackBase )
    {
        return true;
    }

    return false;
}