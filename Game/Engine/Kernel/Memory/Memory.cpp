#include "Kernel_PCH.h"
#include "Memory.h"
#include "Kernel/ThotWindows.h"

namespace Memory
{
    void Copy ( void* destination, const void* source, thSize lenght  )
    {
        CopyMemory( destination, source, lenght );
    }

    void Set  ( void* destination, thSize length, u8 value )
    {
        FillMemory( destination, length, value );
    }

}// namespace Memory