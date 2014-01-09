#include "Kernel_PCH.h"
#include "Tracing.h"

#if defined(THOT_ENABLE_TRACING)
#include "Kernel/ThotWindows.h"
#include "Kernel/DataStructures/CString.h"
#include "stdio.h"









const char* ToString( eDbgTraceChannel dbgChannel )
{
#ifdef CASE
#   error CASE macro allready defined;
#else
#   define CASE(_arg)       case _arg: return #_arg; break;
#endif /*CASE*/


    switch (dbgChannel)
    {
    CASE(SYSTEM     )
    CASE(RENDER     )
    CASE(PHYSX      )
    CASE(KERNEL     )
    CASE(CORE       )
    CASE(INPUT_     )
    CASE(MATHCORE   )

    default:
    {
        THOT_ASSERT(0);
        return NULL;
        break;
    }

    }


#undef CASE
}




void DbgPrintStringLine  ( const char* string )
{
    DbgPrintString( string );
    DbgPrintString( "\n" );
}

void    DbgPrintString    ( const char* string )
{
#if defined _WIN32 && defined _MSC_VER

    OutputDebugStringA( string );

#else
#error Unsuported platform


#endif /*defined _WIN32 && defined _MSC_VER*/
}

static char g_formatStringBuffer[1024*1024*4];

void DbgPrint (  const char* format, ...  )
{
    va_list arg;
    va_start( arg, format );

    //static char buff[1024*1024*4];
    //vsprintf_s( buff, format, arg );
    //DbgPrintString( buff );

    vsprintf_s( g_formatStringBuffer, format, arg );
    DbgPrintString( g_formatStringBuffer );

    va_end(arg);
}

void DbgPrintLine ( const char* format, ... )
{
    va_list arg;
    va_start( arg, format );

    //static char buff[1024*1024*4];
    //vsprintf_s( buff, format, arg );
    vsprintf_s( g_formatStringBuffer, format, arg );


    //DbgPrintStringLine( buff );
    DbgPrintStringLine( g_formatStringBuffer );

    va_end(arg);
}

void DbgPrintCh ( eDbgTraceChannel channel, const char* format, ... )
{
    
}


#endif //THOT_ENABLE_TRACING