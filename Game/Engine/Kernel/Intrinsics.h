#if !defined(__KERNEL_INTRINSICS_H__)
#define __KERNEL_INTRINSICS_H__

#include "Kernel/Basics.h"
//
#if defined(THOT_PLATFORM_WINDOWS)
#include <intrin.h>
//test
#   if defined(THOT_PLATFORM_ARCH_X64)
#   pragma intrinsic(_BitScanReverse64)
__forceinline bool ThotBitScanReverse( unsigned long* outIndex, unsigned long mask )
{
    return _BitScanReverse( outIndex, mask) != 0;
}
#   else
#   error NOT IMPLEMENTED ON x86
#endif //THOT_PLATFORM_ARCH_X64

#else
# error UNKNOWN PLATFORM
#endif //PLATFORM WINDOWS

#endif //__KERNEL_INTRINSICS_H__