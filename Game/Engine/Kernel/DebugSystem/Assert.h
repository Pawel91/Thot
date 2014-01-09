#ifndef __KERNEL_ASSERT_H__
#define __KERNEL_ASSERT_H__

#include "Kernel/Config.h"


#ifdef    THOT_ENABLE_ASSERT

#include "Kernel/KernelDef.h"

#if defined(THOT_ENABLE_TRACING)
#   include "Kernel/DebugSystem/Tracing.h"
#else
#   error FOR NOW ASSERT SYSTEM IS DEPENDING ON TRACING SYSTEM
#endif


KERNEL_API void _DebugBrake();

#define DEBUG_BRAKE() do{_DebugBrake();}while(0)

KERNEL_API void        ShowMessageBox( const char* message );


KERNEL_API const char* GetAssertMessage(const char* format = nullptr, ... );
KERNEL_API const char* GetAssertMessage2(const char* format = nullptr, ... );


// real-time assert
#define THOT_ASSERT(exp, ...)    \
do \
{\
    if( !(exp) )        \
    {                   \
        const char* message = GetAssertMessage( "ASSERTION FAILED: [ %s ]\n MESSAGE:[%s]", #exp, GetAssertMessage2( __VA_ARGS__) );\
        ShowMessageBox(message);   \
        THOT_TRACE_LINE( "%s",message);\
        DEBUG_BRAKE();  \
    }                   \
}\
while(0)

//#define THOT_ASSERT(exp)

#define     sassert_range(_val,_min,_max)       THOT_ASSERT( _val>=_min && _val<=_max )

#ifdef TRAP
#undef TRAP
#endif

#define     THOT_TRAP(exp, ...)   \
do                      \
{                       \
    if( !exp )          \
    {                   \
        *((int*)0) = 0; \
    }                   \
}while(false)

//compile-time assert
#define THOT_UNKNOWN_COMPILE_ASSERT_MESSAGE             "UNKNOWN COMPILE-TIME ASSERT MESSAGE"

#if defined(THOT_PLATFORM_WINDOWS)
#   define THOT_COMPILE_ASSERT2( code, assertMessage )      static_assert(code,assertMessage);
#else
#   error UNKNOWN STATIC ASSERT FOR THIS PLATFORM
#endif

#define THOT_COMPILE_ASSERT(code)                        THOT_COMPILE_ASSERT2(code,THOT_UNKNOWN_COMPILE_ASSERT_MESSAGE)



#else // !defined THOT_ENABLE_ASSERT

#   define THOT_ASSERT( ... )                           do{}while(false)
#   define sassert_range(_val,_min,_max)                do{}while(false)
#   define THOT_COMPILE_ASSERT2( code, assertMessage )
#   define THOT_COMPILE_ASSERT(code)
#   define THOT_TRAP(exp, ...)                          do{}while(false)

#endif // THOT_ENABLE_ASSERT





#endif /*__ASSERT_H__*/