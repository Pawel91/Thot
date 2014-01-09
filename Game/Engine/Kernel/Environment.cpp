#include "Kernel_PCH.h"
#include "Environment.h"

#include "Kernel/ThotWindows.h"
#include "Kernel/DataStructures/CString.h"


static const u32 maxEnvValueSize = 1024;


Bool ThGetEnvVariable( const CString& var, CString& outValue )
{
    char tempBuffer[maxEnvValueSize];

    if( GetEnvironmentVariableA( var.GetBuffer(), tempBuffer, maxEnvValueSize) == 0 )
    {
        return false;
    }

    outValue = tempBuffer;

    return true;
}

Bool ThSetEnvVariable( const CString& var, const CString& value )
{
    if( SetEnvironmentVariableA( var.GetBuffer(), value.GetBuffer() ) == 0 )
    {
        return false;
    }

    return true;
}