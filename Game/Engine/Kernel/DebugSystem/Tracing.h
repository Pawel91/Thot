#ifndef __KERNEL_TRACING_H__
#define __KERNEL_TRACING_H__

#include "Kernel/Config.h"

#if defined(THOT_ENABLE_TRACING)

#include "Kernel/Defines.h"
#include "Kernel/DataTypes.h"
#include "Kernel/KernelDef.h"

enum eDbgTraceChannel
{
    TRACE_CHANNEL_NONE        = -1
    ,SYSTEM
    ,RENDER
    ,PHYSX
    ,KERNEL
    ,CORE
    ,INPUT_
    ,MATHCORE

    ,TRACE_CHANNEL_COUNT

    ,FORCEDWORD        = FORCE_DWORD
};


KERNEL_API void     DbgPrintStringLine  ( const char* string );
KERNEL_API void     DbgPrintString      ( const char* string );             // should be a cross platform function for tracing a string
KERNEL_API void     DbgPrint            (  const char* format, ...  );      //var args tracing
KERNEL_API void     DbgPrintCh          ( eDbgTraceChannel channel, const char* format, ... );
KERNEL_API void     DbgPrintLine        ( const char* format, ... );    


#   define  THOT_TRACE                      DbgPrint
#   define  THOT_TRACE_LINE                 DbgPrintLine

#else //!THOT_ENABLE_TRACING

#   define THOT_TRACE       do{}while(false)
#   define THOT_TRACE_LINE  do{}while(false)

#endif // THOT_ENABLE_TRACING

#endif /*__KERNEL_TRACING_H__*/