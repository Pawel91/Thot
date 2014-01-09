#if !defined(__KERNEL_COMPILER_SPECIFIC_H__)
# define __KERNEL_COMPILER_SPECIFIC_H__


#define THOT_COMPILE_OUTPUT_PREFIX "THOT_COMPILE_OUTPUT: "


#if defined(_MSC_VER)
#   include "Kernel/Basics/MicrosoftSpecific.h"
#else
#   error UNKNOWN PLATFORM
#endif


#if defined(__cplusplus)
#   define THOT_CPLUSPLUS
#endif /*__cplusplus*/

#if defined THOT_CPLUSPLUS
#   define THOT_BEGIN_EXTERN_C extern "C" {
#   define THOT_END_EXTERN_C }
#else
#   define THOT_BEGIN_EXTERN_C
#   define THOT_END_EXTERN_C
#endif /*THOT_CPLUSPLUS*/


#endif //__KERNEL_COMPILER_SPECIFIC_H__