#include "Game_PCH.h"
#include "GameEntryPoint.h"

#include "Kernel/Profiler/Profiler.h"
#include "Input/InputTypes.h"


#include "GameFlow.h"
#include "Kernel/ThotWindows.h"

#include "Render/GLWrapper/OpenGL.h"
#include "StrSafe.h"
#include "winuser.h"
#include <map>

#ifdef NULL
#undef NULL
#endif

#ifndef NULL
#define NULL 0
#endif


//***** forward function declarations
namespace windows
{
    long    g_windowBits    = 32;
    Bool    g_AppHasFocus   = true;
    
    void                SetupPixelFormat        ( HDC hDC );
    LRESULT CALLBACK    KeyboardEvent           ( int nCode, WPARAM wParam, LPARAM lParam );            // user input win32 callback
    LRESULT CALLBACK    MainWindowProc          ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ); // windows main procedure
    Bool                SetVSync                ( Bool sync );
    Bool                RegisterMouseRawInput   ( HWND hwnd);
    HINSTANCE           GetApplicationHandle    (HWND handleWindow );
    void                GameLoop            ( );
    HWND                InitGameWindow      ( HINSTANCE hInstance, LPSTR lpCmdLine );
    int                 ShutdownGameWindow  ( );
    void                OnKeyboardKeyPress  ( DWORD vkCode, Bool bDown ); //[TODO] REMOVE MEE!!!!!!


LRESULT CALLBACK TestHook( int nCode,  WPARAM wParam,   LPARAM lParam);


}

void windows::SetupPixelFormat(HDC hDC)
{
    int pixelFormat;
    
    //[TODO] get pixel format descriptor from a setting from render or something like that:D:D
    PIXELFORMATDESCRIPTOR pfd =
    {   
        sizeof(PIXELFORMATDESCRIPTOR),  // size
            1,                          // version
            PFD_SUPPORT_OPENGL |        // OpenGL window
            PFD_DRAW_TO_WINDOW |        // render to window
            PFD_DOUBLEBUFFER,           // support double-buffering
            PFD_TYPE_RGBA,              // color type
            32,                         // prefered color depth
            0, 0, 0, 0, 0, 0,           // color bits (ignored)
            0,                          // no alpha buffer
            0,                          // alpha bits (ignored)
            64,                         // accumulation buffer
            0, 0, 0, 0,                 // accum bits (ignored)
            24,                         // depth buffer
            8,                          // stencil buffer
            0,                          // no auxiliary buffers
            PFD_MAIN_PLANE,             // main layer
            0,                          // reserved
            0, 0, 0,                    // no layer, visible, damage masks
    };

    pixelFormat = ChoosePixelFormat(hDC, &pfd);
    THOT_ASSERT( pfd.cStencilBits==8 && pfd.cColorBits == 32 && pfd.cDepthBits == 24); // verify color, depth and stencil buffer
    SetPixelFormat(hDC, pixelFormat, &pfd);
}

void windows::OnKeyboardKeyPress  ( DWORD vkCode, Bool bDown )
{
    InputKey::EKeys key = InputKey::GetFromNativeKeyID( vkCode );
    if( key != InputKey::EKeys::E_KEY_INVALID )
    {
        Game::KeyInputCallback(key, bDown );
    }
}


LRESULT CALLBACK windows::MainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HDC handleDeviceContext;
    static HGLRC handleRenderContext;
    int height, width;

    HWND hActiveWnd = GetActiveWindow();
    if( hActiveWnd != hWnd )
    {
        if( g_AppHasFocus )
        {
            //THOT_TRACE( "APPLICATION LOSES FOCUS\n" );
            OutputDebugStringA( "APPLICATION LOSES FOCUS\n" );
        }
        g_AppHasFocus = false;
        ReleaseCapture();
    }
    else
    {
        if( !g_AppHasFocus )
        {
            OutputDebugStringA( "APPLICATION GAINS FOCUS\n" );
            SetCapture(hWnd);
            SetCursorPos(  Game::GetGameParams().m_windowWidth /2, Game::GetGameParams().m_windowHeight/2);
        }
        g_AppHasFocus = true;

    }

    // dispatch messages
    switch (uMsg)
    {   
    case WM_CREATE:         // window creation
        handleDeviceContext = GetDC(hWnd);
        windows::SetupPixelFormat(handleDeviceContext);
        //SetupPalette();
        handleRenderContext = wglCreateContext(handleDeviceContext);
        wglMakeCurrent(handleDeviceContext, handleRenderContext);
        SetCursorPos( Game::GetGameParams().m_windowWidth /2, Game::GetGameParams().m_windowHeight/2);
        SetCapture(hWnd);
        break;

    case WM_DESTROY:            // window destroy
    case WM_QUIT:
    case WM_CLOSE:                  // windows is closing

        // deselect rendering context and delete it
        wglMakeCurrent( handleDeviceContext, NULL);
        wglDeleteContext( handleRenderContext );

        // send WM_QUIT to message queue
        PostQuitMessage(0);
        break;

    case WM_SIZE:
    {
        height = HIWORD(lParam);        // retrieve width and height
        width = LOWORD(lParam);
        Game::ResizeRender( width, height );
        break;
    }


    case WM_ACTIVATEAPP:        // activate app
        break;

    case WM_PAINT:  
    {    
        // paint
        PAINTSTRUCT ps;
        BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;
    }

    case WM_INPUT: 
    {

////////////////////////////////////////////////////////

    UINT dwSize;

    GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, 
                    sizeof(RAWINPUTHEADER));

    const unsigned int size = 1024;
    static BYTE lpb [size];
    if( dwSize > size )
    {
        OutputDebugStringA( "ERROR!! SIZE FROM RAW INPUT EXCEEDS RAW INPUT SIZE );" );
    }

    if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, 
         sizeof(RAWINPUTHEADER)) != dwSize )
    {
         OutputDebugStringA (("GetRawInputData does not return correct size !\n")); 
    }

        RAWINPUT* raw = (RAWINPUT*)lpb;
    
        if (raw->header.dwType == RIM_TYPEMOUSE) 
        {
            int xPosRelative = raw->data.mouse.lLastX;
            int yPosRelative = raw->data.mouse.lLastY;
            Game::MouseMoveInputCallback( xPosRelative, yPosRelative );

            DWORD nativeMouseButtonID = raw->data.mouse.usButtonFlags;
            switch ( nativeMouseButtonID )
            {
                case RI_MOUSE_LEFT_BUTTON_DOWN:        // left mouse button
                Game::MouseButtonInputCallback( InputKey::E_MOUSEB_LEFT, true );
                break;

                case RI_MOUSE_RIGHT_BUTTON_DOWN:        // right mouse button
                    Game::MouseButtonInputCallback( InputKey::E_MOUSEB_RIGHT, true );
                break;

                case RI_MOUSE_LEFT_BUTTON_UP:
                    Game::MouseButtonInputCallback( InputKey::E_MOUSEB_LEFT, false );
                break;

                case RI_MOUSE_RIGHT_BUTTON_UP:        
                    Game::MouseButtonInputCallback( InputKey::E_MOUSEB_RIGHT, false );
                break;

                case RI_MOUSE_MIDDLE_BUTTON_DOWN:
                    
                break;

                case RI_MOUSE_MIDDLE_BUTTON_UP:
                    Game::MouseButtonInputCallback( InputKey::E_MOUSEB_SCROLL, false );
                break;
            }

            if( g_AppHasFocus )
                SetCursorPos( Game::GetGameParams().m_windowWidth /2, Game::GetGameParams().m_windowHeight /2);
        } 
        else if (raw->header.dwType == RIM_TYPEKEYBOARD) 
        {

            Bool bDown = true;
            if( raw->data.keyboard.Message == WM_KEYDOWN )
            {
                bDown = true;
            }
            else if( raw->data.keyboard.Message == WM_KEYUP )
            {
                bDown = false;
            }

            OnKeyboardKeyPress( raw->data.keyboard.VKey, bDown );
            
            if( raw->data.keyboard.VKey == VK_F11 && bDown )
            {
                PostQuitMessage(0);
            }
        }
        
        break;
    }


    case WM_MOUSEWHEEL:
    {
        int zDelta = (GET_WHEEL_DELTA_WPARAM(wParam)) / WHEEL_DELTA;
        Game::MouseWheelInputCallback( zDelta );
    }
    break;

    case WM_KEYUP:
        break;

    case WM_KEYDOWN:
        int fwKeys;
        LPARAM keyData;
        fwKeys = (int)wParam;        // virtual-key code 
        keyData = lParam;            // key data 
        if( fwKeys == VK_F11 )
            PostQuitMessage(0);

        break;

    default:
        break;
    }

    //if( !bHaveRawInput )
    //    CMouseInputInterface::s_MouseMoveInputCallback( 0, 0, g_input.GetDeviceInput( InputDevices::E_INPUT_DEVICE_MOUSE ) );
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

Bool windows::SetVSync(Bool sync)
{    
    // Function pointer for the wgl extention function we need to enable/disable
    // vsync
    typedef Bool (APIENTRY *PFNWGLSWAPINTERVALPROC)( int );
    PFNWGLSWAPINTERVALPROC wglSwapIntervalEXT = 0;

    const char *extensions = (char*)gl::GetString( gl::EXTENSIONS );

    if( strstr( extensions, "WGL_EXT_swap_control" ) == 0 )
    {
        THOT_TRACE_LINE("Cannot find extension WGL_EXT_swap_control. Cannot set VSync to [%d]", sync );
        return false;
    }
    else
    {
        wglSwapIntervalEXT = (PFNWGLSWAPINTERVALPROC)wglGetProcAddress( "wglSwapIntervalEXT" );

        if( wglSwapIntervalEXT )
        {
            wglSwapIntervalEXT(sync);
        }
        else
        {
            THOT_ASSERT("Cannot find wglSwapIntervalEXT function");
            return false;
        }
    }

    return true;
}


HWND windows::InitGameWindow      ( HINSTANCE hInstance, LPSTR lpCmdLine )
{
    WNDCLASSEX windowClass;     // window class
    HWND       hwnd;            // window handle
    DWORD      dwExStyle;       // Window Extended Style
    DWORD      dwStyle;         // Window Style
    RECT       windowRect;

    windowRect.left     = (long)0;                        // Set Left Value To 0
    windowRect.right    = (long) Game::GetGameParams().m_windowWidth; // Set Right Value To Requested Width
    windowRect.top      = (long)0;                         // Set Top Value To 0
    windowRect.bottom   = (long) Game::GetGameParams().m_windowHeight;   // Set Bottom Value To Requested Height

    // fill out the window class structure
    windowClass.cbSize          = sizeof(WNDCLASSEX);
    windowClass.style           = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc     = windows::MainWindowProc;
    windowClass.cbClsExtra      = 0;
    windowClass.cbWndExtra      = 0;
    windowClass.hInstance       = hInstance;
    windowClass.hIcon           = LoadIcon(NULL, IDI_APPLICATION);  // default icon
    windowClass.hCursor         = LoadCursor(NULL, IDC_ARROW);      // default arrow
    windowClass.hbrBackground   = NULL;                             // don't need background
    windowClass.lpszMenuName    = NULL;                             // no menu
    windowClass.lpszClassName   = "GLClass";
    windowClass.hIconSm         = LoadIcon(NULL, IDI_WINLOGO);      // windows logo small icon

    // register the windows class
    if (!RegisterClassEx(&windowClass))
    {
        return NULL;
    }

    if ( Game::GetGameParams().m_bFullscreen )      // fullscreen?
    {
        DEVMODE dmScreenSettings; memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
        dmScreenSettings.dmSize         = sizeof(dmScreenSettings); 
        dmScreenSettings.dmPelsWidth    = Game::GetGameParams().m_windowWidth ;         // screen width
        dmScreenSettings.dmPelsHeight   = Game::GetGameParams().m_windowHeight;           // screen height
        dmScreenSettings.dmBitsPerPel   = g_windowBits;             // bits per pixel
        dmScreenSettings.dmFields       = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

        // 
        if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
        {
            // setting display mode failed, switch to windowed
            MessageBoxA(NULL, "Display mode failed", NULL, MB_OK);
            Game::GetGameParams().m_bFullscreen = false; 
        }
    }

    if ( Game::GetGameParams().m_bFullscreen )  // Are We Still In Fullscreen Mode?
    {
        dwExStyle=WS_EX_APPWINDOW;              // Window Extended Style
        dwStyle=WS_POPUP;                       // Windows Style
        ShowCursor(false);                      // Hide Mouse Pointer
    }
    else
    {
        //dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;   // Window Extended Style
        //dwStyle = WS_OVERLAPPEDWINDOW;                    // Windows Style
        //ShowCursor(false);

        dwExStyle = WS_EX_APPWINDOW;            // Window Extended Style
        dwStyle = WS_POPUP;                     // Windows Style
        ShowCursor(false);                      // Hide Mouse Pointer
    }

    AdjustWindowRectEx(&windowRect, dwStyle, false, dwExStyle);     // Adjust Window To True Requested Size

    // class registered, so now create our window
    hwnd = CreateWindowEx(NULL,                         // extended style
        "GLClass",                                      // class name
        "SKINNING",                                 // app name
        dwStyle | WS_CLIPCHILDREN |
        WS_CLIPSIBLINGS,
        0, 0,                               // x,y coordinate
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top, // width, height
        NULL,                               // handle to parent
        NULL,                               // handle to menu
        hInstance,                          // application instance
        NULL);                              // no extra params

    // check if window creation failed (hwnd would equal NULL)
    if (!hwnd)
    {
        THOT_ASSERT(false, "Failed to create window handle" );
        return hwnd;
    }

    ShowWindow(hwnd, SW_SHOW);          // display the window
    UpdateWindow(hwnd);                 // update the window


    int hookID = WH_CALLWNDPROC;
    //int hookID = WH_CALLWNDPROCRET;
    //int hookID = WH_KEYBOARD_LL;

    SetWindowsHookEx( hookID, TestHook, hInstance, GetCurrentThreadId() );
    //windows::RegisterMouseRawInput( hwnd );
    
    return hwnd;
}

int windows::ShutdownGameWindow  ( )
{

    if ( Game::GetGameParams().m_bFullscreen )
    {
        ChangeDisplaySettings(NULL,0);          // If So Switch Back To The Desktop
        ShowCursor(true);                       // Show Mouse Pointer
    }

  
    return -1;
}


void windows::GameLoop ( )
{
    MSG msg;
    bool exit = false;
    for(;;)
    {
        THOT_DECLARE_PROFILE("windows::GameLoop");

        Game::OnBeginFrame();

        if( g_AppHasFocus )
        {
            HWND hActiveWnd = GetActiveWindow();
            Game::LoopGame();
            Game::SwapBuffers( hActiveWnd );
        }
        else
        {
            Game::OnAppNoFocus();
        }

       {
        THOT_DECLARE_PROFILE("window message processing");
            
            while ( PeekMessage (&msg, NULL, 0, 0, PM_NOREMOVE) )
            {
                if (!GetMessage (&msg, NULL, 0, 0))
                {
                    exit = true;
                    break;
                }

                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }

        if( exit)
        {
            break;
        }

        Game::OnEndFrame();
    }
}

int RunGame ( HINSTANCE hInstance, LPSTR lpCmdLine )
{
    Game::InitGameParams();
    HWND windowHandle =  windows::InitGameWindow( hInstance, lpCmdLine );
    Game::InitGame( windowHandle );
    windows::SetVSync( true );
    windows::GameLoop();
    Game::ShutdownGame();
    windows::ShutdownGameWindow();

    return 0;
}

Bool windows::RegisterMouseRawInput ( HWND hwnd )
{
    // **** register raw input
    #ifndef HID_USAGE_PAGE_GENERIC
    #define HID_USAGE_PAGE_GENERIC         ((USHORT) 0x01)
    #endif
    #ifndef HID_USAGE_GENERIC_MOUSE
    #define HID_USAGE_GENERIC_MOUSE        ((USHORT) 0x02)
    #endif

    RAWINPUTDEVICE Rid[2];
    Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC; 
    Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE; 
    Rid[0].dwFlags = RIDEV_INPUTSINK;   
    Rid[0].hwndTarget = hwnd;

    // from http://msdn.microsoft.com/en-us/library/windows/desktop/ms645546(v=vs.85).aspx example 2
    Rid[1].usUsagePage = 0x01; 
    Rid[1].usUsage = 0x06; 
    Rid[1].dwFlags = RIDEV_NOLEGACY;   // adds HID keyboard and also ignores legacy keyboard messages
    Rid[1].hwndTarget = 0;

    if ( !RegisterRawInputDevices(Rid, THOT_ARRAY_SIZE(Rid), sizeof(Rid[0])) )
    {
        THOT_ASSERT("failed to register raw input device");

    }

    return true;
}

HINSTANCE windows::GetApplicationHandle  (HWND handleWindow )
{
    return (HINSTANCE)GetWindowLongPtr(handleWindow, GWLP_HINSTANCE);
} 


LRESULT CALLBACK windows::TestHook( int nCode,  WPARAM wParam,   LPARAM lParam)
{
#if !defined(DEFAULT_VALUE)
#define DEFAULT_VALUE() CallNextHookEx( NULL , nCode, wParam, lParam)


    if( nCode != HC_ACTION )
    {
        return DEFAULT_VALUE();
    }

    CWPSTRUCT* pData = (CWPSTRUCT*)lParam;    

    if( pData->message == WM_INPUT )
    {
        int a=0;
        a++;
    }


    return DEFAULT_VALUE();


#undef DEFAULT_VALUE
#else
#error    DEFAULT_VALUE is allready defined
#endif
}