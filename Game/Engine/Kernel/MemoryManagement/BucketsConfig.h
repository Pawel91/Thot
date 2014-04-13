#if !defined(__KERNEL_BUCKETS_CONFIG_H__)
#define __KERNEL_BUCKETS_CONFIG_H__

#include "Kernel/Basics.h"

#if defined(THOT_ENABLE_DEBUG)
#   define BUCKET_POOL_DEBUG
#   define BUCKET_POOL_DEBUG_ONLY(__expr) __expr
#   define BUCKET_DEBUG
#else
#   define BUCKET_POOL_DEBUG_ONLY(__expr) void(0)
#endif


namespace MemoryManagement
{
    enum
    {
         BUCKETS_PAGE_SIZE  = 4 * 1024
        ,BUCKETS_INVALID_PAGE_INDEX = -1
        ,BUCKETS_MAX_ELEMENTSIZE = 257
        ,BUCKETS_GRANULARITY = 4
    };
}//namespace MemoryManagement



#endif //__KERNEL_BUCKETS_CONFIG_H__