#ifndef __THOT_WINDOWS_H__
#define __THOT_WINDOWS_H__

#if !defined(WIN32_LEAN_AND_MEAN)
#   define WIN32_LEAN_AND_MEAN
#endif

#if !defined(WIN32_EXTRA_LEAN)
#   define WIN32_EXTRA_LEAN
#endif

#include "windows.h"

//-----------------------------------------------------------------
//          REMOVE CreateFile MACRO
//-----------------------------------------------------------------
#if defined(CreateFile)
#   undef CreateFile

#if defined(THOT_UNICODE)

__forceinline HANDLE CreateFile(
    _In_ LPCWSTR lpFileName,
    _In_ DWORD dwDesiredAccess,
    _In_ DWORD dwShareMode,
    _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    _In_ DWORD dwCreationDisposition,
    _In_ DWORD dwFlagsAndAttributes,
    _In_opt_ HANDLE hTemplateFile
    )
{
    CreateFileW( lpFileName
                ,dwDesiredAccess
                ,dwShareMode
                ,lpSecurityAttributes
                ,dwCreationDisposition
                ,dwFlagsAndAttributes
                ,hTemplateFile  );
}

#else
__forceinline HANDLE CreateFile(    _In_ LPCSTR lpFileName,
                                        _In_ DWORD dwDesiredAccess,
                                        _In_ DWORD dwShareMode,
                                        _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                                        _In_ DWORD dwCreationDisposition,
                                        _In_ DWORD dwFlagsAndAttributes,
                                        _In_opt_ HANDLE hTemplateFile)
{
    CreateFileA( lpFileName
                ,dwDesiredAccess
                ,dwShareMode
                ,lpSecurityAttributes
                ,dwCreationDisposition
                ,dwFlagsAndAttributes
                ,hTemplateFile  );
}

#endif //THOT_UNICODE
#endif //#if defined(CreateFile)




//-----------------------------------------------------------------
//          CONSTANTS
//-----------------------------------------------------------------

#if defined(NO_ERROR)
    const DWORD __noerrorDefined = NO_ERROR;
#   undef NO_ERROR
    const DWORD NO_ERROR = __noerrorDefined;
#endif

#if defined(TRUE)
    const DWORD __trueDefined = TRUE;
#undef TRUE
    const DWORD TRUE = __trueDefined;
#endif



#endif /*__THOT_WINDOWS_H__*/