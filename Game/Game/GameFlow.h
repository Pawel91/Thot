#ifndef __GAME_FLOW_H__
#define __GAME_FLOW_H__

#include "Kernel/DataStructures/CString.h"
#include "Input\InputTypes.h"

struct SGameStartupParams
{
    unsigned int        m_windowWidth;
    unsigned int        m_windowHeight;
    bool                m_bFullscreen;
    CString             m_applicationName;

    SGameStartupParams::SGameStartupParams()
        :   m_applicationName   ("Radu`s application")
    {
    }
};


THOT_TODO("REFACTOR THIS SHITTY CODE");
namespace Game
{

#if defined THOT_PLATFORM_WINDOWS
bool                        InitGame            ( void* windowHandle );
void                        SwapBuffers         ( void* windowHandle );
#else
#   error Unsuported platform
#endif
bool                        ShutdownGame        ( );
void                        LoopGame            ( );
void                        OnAppNoFocus        ( );
void                        OnBeginFrame        ( );
void                        OnEndFrame          ( );
SGameStartupParams&         GetGameParams       ( );
bool                        InitGameParams      ( );
void                        ResizeRender        ( int width, int height );


//*********************************
//          INPUT CALLBACKS
//*********************************

//keyboard
void                        KeyInputCallback            ( InputKey::EKeys eKey, bool bButtonDown );

//mouse
void                        MouseButtonInputCallback    ( InputKey::EMouseButton eKey, bool bButtonDown );
void                        MouseMoveInputCallback      ( int dx, int dy );
void                        MouseWheelInputCallback     ( int zDelta );


}


#endif /*__GAME_FLOW_H__*/