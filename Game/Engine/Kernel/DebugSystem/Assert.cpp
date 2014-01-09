#include "Kernel_PCH.h"
#include "Assert.h"

#include "Kernel/ThotWindows.h"
#include "Kernel/DebugSystem/StackWalker.h"

#include "../resource.h"
#include "stdio.h"
#include <CommCtrl.h>


#pragma comment(linker, \
  "\"/manifestdependency:type='Win32' "\
  "name='Microsoft.Windows.Common-Controls' "\
  "version='6.0.0.0' "\
  "processorArchitecture='*' "\
  "publicKeyToken='6595b64144ccf1df' "\
  "language='*'\"")

#pragma comment(lib, "ComCtl32.lib")


INT_PTR CALLBACK DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{  
    switch(uMsg) /* more compact, each "case" through a single line, easier on the eyes */
    {
    case WM_COMMAND:
      switch(LOWORD(wParam))
      {
      case IDOK: 
          {
              int a =0;
            return TRUE; 
          }
      }
      break;
    
    case WM_CLOSE:   
        { 
            return TRUE; /* call subroutine */
            
        }
    case WM_DESTROY: PostQuitMessage(0); return TRUE;
    }

  return FALSE;
}

void ShowMessageBox( const char* message )
{
    HINSTANCE hInst= GetModuleHandle (0);
    HWND hWnd = GetActiveWindow();

    InitCommonControls();
    HWND hDialog = CreateDialogParam(  hInst,
                MAKEINTRESOURCE(IDD_DIALOG1),
	            0,
                DialogProc,
                0);
    ShowWindow( hDialog, SW_SHOW );


     //MessageBoxA(NULL, message, NULL, MB_OK);
}

KERNEL_API const char* GetAssertMessage(const char* format, ... )
{
    if( !format )
    {
        return NULL;
    }

    va_list arg;
    va_start( arg, format );
    static char buff[1024*10];
    vsprintf_s( buff, format, arg );
    va_end(arg);

    static CString finalRezult = "";
    StackWalker::CStackInfo stackInfo;
    StackWalker::CStackInfo::GetCurrentStackInfo(stackInfo);
    stackInfo.DebugGetStringInfo(finalRezult);

    
    finalRezult = buff + CString("\n") + finalRezult;
    return finalRezult.GetBuffer();

    return buff;    
}

KERNEL_API const char* GetAssertMessage2(const char* format, ... )
{
    if( !format )
    {
        return NULL;
    }

    va_list arg;
    va_start( arg, format );
    static char buff[1024*5];
    vsprintf_s( buff, format, arg );
    va_end(arg);

    return buff; 
}



//#if defined(THOT_PLATFORM_WINDOWS) && defined(THOT_PLATFORM_ARCH_X64)
#   define ASSERT_USE_CRT_BRAKE_POINT
//#endif

#ifdef ASSERT_USE_CRT_BRAKE_POINT
#include "crtdbg.h"
#endif 




void _DebugBrake()
{
#ifndef ASSERT_USE_CRT_BRAKE_POINT
_asm{
        int 3
    }
#else
_CrtDbgBreak();
#endif /*_M_IX86*/
}   