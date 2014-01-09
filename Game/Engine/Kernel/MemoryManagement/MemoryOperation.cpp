#include "Kernel_PCH.h"
#include "Kernel/MemoryManagement/MemoryOperation.h"

//--------------------------------------------------------------------------------
namespace MemoryManagement
{
    const char* CMemoryOperation::EMemoryOperationToString( EMemoryOperation op  )
    {
    
    #define __CASE(__op)\
        case __op: return #__op;
    
        switch( op)
        {
            __CASE( EMemoryOperation_Malloc        );
            __CASE( EMemoryOperation_New           );
            __CASE( EMemoryOperation_NewArray      );
            __CASE( EMemoryOperation_Free          );
            __CASE( EMemoryOperation_Delete        );
            __CASE( EMemoryOperation_DeleteArray   );
            __CASE( EMemoryOperation_Allocation    );
            __CASE( EMemoryOperation_Remove        );
        }
    
        return "EMemoryOperation_UNKNOWN";
    }
}

//--------------------------------------------------------------------------------