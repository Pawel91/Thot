#include "Input_PCH.h"
#include "Input.h"
#include "KeyboardInput.h"
#include "MouseInput.h"
#include "InputImpl.h"

#include "Kernel/ThotWindows.h"

namespace Input
{
    Bool    RegisterRawInput        ( HWND windowHandle );
}


CKeyInputInterface::CKeyInputInterface()
{
}
    

InputDevices::eDevices CDeviceInputInterface::GetDeviceType       ( )
{ 
    return m_eDeviceType; 
}

Bool CInput::CreateInstance    ( )
{
    s_pInstance = THOT_NEW CInputImpl;

    return true;
}

CInput* CInput::GetInstance       ( )
{
    return s_pInstance;
}

Bool CInput::DestroyInstance   ( )
{
    if( s_pInstance )
    {
        THOT_SAFE_DELETE(s_pInstance);
        return true;
    }
    else
    {
        return false;
    }
}

CInput*     CInput::s_pInstance = NULL;



void CKeyInputInterface::s_KeyInputCallback    ( InputKey::EKeys eKey, Bool bButtonDown, void* pThis )
{
    CKeyInputInterface* _this = (CKeyInputInterface*)pThis;
    _this->OnUserInput( eKey, bButtonDown  );
}


void CMouseInputInterface::s_MouseMoveInputCallback ( int dx, int dy, void* pThis )
{
    CMouseInputInterface* _this = (CMouseInputInterface*) pThis;
    _this->OnMouseMove( dx, dy );
}

void CMouseInputInterface::s_MouseWheelInputCallback ( int zDelta, void* pThis )
{
    CMouseInputInterface* _this = (CMouseInputInterface*) pThis;
    _this->OnMouseWheel( zDelta );
}

void CMouseInputInterface::s_MouseButtonInputCallback ( InputKey::EMouseButton eKey, Bool bButtonDown, void* pThis )
{
    CMouseInputInterface* _this = (CMouseInputInterface*) pThis;
    _this->OnUserInput( eKey, bButtonDown );
}





namespace Input
{
    Bool    RegisterRawInput        ( HWND windowHandle )
    {
        
            // **** register raw input
        #ifndef HID_USAGE_PAGE_GENERIC
        #define HID_USAGE_PAGE_GENERIC         ((USHORT) 0x01)
        #endif
        #ifndef HID_USAGE_GENERIC_MOUSE
        #define HID_USAGE_GENERIC_MOUSE        ((USHORT) 0x02)
        #endif

        RAWINPUTDEVICE Rid[2];

        // KEYBOARD raw input
        Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC; 
        Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE; 
        Rid[0].dwFlags = RIDEV_INPUTSINK;   
        Rid[0].hwndTarget = windowHandle;

        // from http://msdn.microsoft.com/en-us/library/windows/desktop/ms645546(v=vs.85).aspx example 2
        // MOUSE raw input
        Rid[1].usUsagePage = 0x01; 
        Rid[1].usUsage = 0x06; 
        Rid[1].dwFlags = RIDEV_NOLEGACY;   // adds HID keyboard and also ignores legacy keyboard messages
        Rid[1].hwndTarget = 0;

        if ( !RegisterRawInputDevices(Rid, THOT_ARRAY_SIZE(Rid), sizeof(Rid[0])) )
        {
            THOT_ASSERT("failed to register raw input");
            return false;
        }

        return true;
    }

    Bool Init( void* windowHandle )
    {
        HWND nativeWindowHandle = (HWND)windowHandle;
        if( !CInput::CreateInstance() )
        {
            return false;
        }

        if( !Input::RegisterRawInput( nativeWindowHandle ) )
        {
            return false;
        }

        return true;
    }
    
    INPUT_API Bool Shutdown( )
    {
        CInput::DestroyInstance();
        return true;
    }

}
