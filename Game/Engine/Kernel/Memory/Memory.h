#if !defined(__MEMORY_H__)
#define __MEMORY_H__

#include "Kernel/KernelDef.h"
#include "Kernel/DataTypes.h"

namespace Memory
{
    void KERNEL_API Copy        ( void* destination, const void* source, thSize lenght  );
    void KERNEL_API Set         ( void* destination, thSize length, u8 value );
};


#endif //__MEMORY_H__