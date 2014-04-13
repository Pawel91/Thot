#if !defined(__KERNEL_MEMORY_DEFINES_H__)
#define __KERNEL_MEMORY_DEFINES_H__

#include "Kernel/Config.h"

#   define THOT_MEM_ENABLE_BUCKETS_SYSTEM


#if defined(THOT_MEM_ENABLE_DEBUG)
#   define THOT_MEM_ENABLE_HANDLE_OPERATION

#   if defined(THOT_MEM_ENABLE_HANDLE_OPERATION)
#       define THOT_MEM_ENABLE_TRACKING
#       define THOT_MEM_ENABLE_STATISTICS
//#       define THOT__MEM_CATCH_OPERATION_STACK
#   endif //THOT_MEM_ENABLE_HANDLE_OPERATION

#endif



#endif //__KERNEL_MEMORY_DEFINES_H__