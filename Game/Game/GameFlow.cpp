#include "Game_PCH.h"
#include "GameFlow.h"

#include "Kernel/Profiler/Profiler.h"
#include "Kernel/Utils/StringUtils.h"
#include "Kernel/FileSystem/Path.h"
#include "Kernel/ThotWindows.h"
#include "Kernel/Time/Timer.h"
#include "Kernel/DebugSystem/StackWalker.h"
#include "Input/Input.h"
#include "Render/Render.h"
#include "Core/FrameTimeManager.h"
#include "Core/FrameTimeManager.h"
#include "Game/MOD_GameManager.h"

#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
namespace Game
{

void ParseCommandLine ( const char* cmdLine, SGameStartupParams& outGameParams )
{
    ThZeroMemoryTmpl(outGameParams);

    StringUtils::TCommands commands;
    StringUtils::SplitCommandLine( CString( cmdLine), commands );

    u64 nSize = commands.Size();
    for( u64 i=0; i<nSize; i++)
    {
        if( commands[i].m_attribute == "width" )
        {
            THOT_ASSERT( !commands[i].m_value.IsEmpty() );
            outGameParams.m_windowWidth = commands[i].m_value.ToInt();
        }
        else
        if( commands[i].m_attribute == "height" )
        {   
            THOT_ASSERT( !commands[i].m_value.IsEmpty() );
            outGameParams.m_windowHeight = commands[i].m_value.ToInt();
        }
        else
        if( commands[i].m_attribute == "fullscreen" )
        {
            if( commands[i].m_value.IsEmpty() )
            {
                outGameParams.m_bFullscreen = true;
            }
            else
            {
                outGameParams.m_bFullscreen = ( commands[i].m_value.ToInt()==0? false : true );
            }
        }
    
    }
}

void SwapBuffers( void* windowHandle )
{
    DECLARE_PROFILE_SCOPED("SwapBuffers");

    static HWND nativeWindowHandle = (HWND)windowHandle;
    static HDC nativeDeviceContextHandle = GetDC(nativeWindowHandle);

    ::SwapBuffers( nativeDeviceContextHandle );
}

bool InitGame ( void* windowHandle )
{

    HWND nativeWindowHandle = (HWND) windowHandle;

#if defined(THOT_ENABLE_PROFILER)
    if( !ThotProfiler::CManager::CreateInstance() )
    {
        return false;
    }
#endif
    
    if( !CPath::SetDefaultDataPath() )
    {
        THOT_ASSERT( false, "Failed to set default data path" );
    }

    if( !Input::Init(nativeWindowHandle) )
    {
        THOT_TRACE_LINE("Failed to init input");
        return false;
    }

    if( !Render::Init( ) )
    {
        THOT_TRACE_LINE("Failed to init render");
        return false;
    }

    CRender::GetInstance()->SetWidth( Game::GetGameParams().m_windowWidth );
    CRender::GetInstance()->SetHeight( Game::GetGameParams().m_windowHeight );

    CFrameTimeManager::CreateInstance();
    CGameManager::CreateInstance();

    if ( !CFrameTimeManager::GetInstance()->Init() )
    {
        THOT_TRACE_LINE("Failed to init FrameTimeManager");
        return false;
    }

    CGameManager::GetInstance()->Init();

   return true;
}

bool ShutdownGame( )
{
    CGameManager::GetInstance()->DestroyInstance();
    CFrameTimeManager::DestroyInstance();
    Render::Shutdown();
    Input::Shutdown();

    return true;
}

void LoopGame ( )
{
    float fDeltaTime = CFrameTimeManager::GetInstance()->GetGameTime( );

#if defined(THOT_ENABLE_PROFILER)

    const CKeyInputInterface* pKeyboard = CInput::GetInstance()->GetDeviceInputT<CKeyInputInterface>(InputDevices::E_INPUT_DEVICE_KEYBOARD);
    if( pKeyboard->ButtonUp( InputKey::E_KEY_P ) )
    {
        ThotProfiler::CManager::GetInstance()->BeginProfiling(10);
    }
#endif

    {
        DECLARE_PROFILE_SCOPED("INPUT PROCESS");

        CInput::GetInstance()->SetDeltaTime( fDeltaTime );
        CInput::GetInstance()->OnAfterUserInput();
    }


    {
        DECLARE_PROFILE_SCOPED("RENDER LOOP");
        
        CRender::GetInstance()->Render( );
    }

    {
        DECLARE_PROFILE_SCOPED("UPDATE LOOP");

        CGameManager::GetInstance()->OnUpdate( fDeltaTime );
    }



    Bool bRenderSucces = CRender::GetInstance()->EndRender();

    if( !bRenderSucces )
    {
        THOT_ASSERT(false, CRender::GetInstance()->GetRenderErrMessage() );
    }

    CInput::GetInstance()->OnBeforeUserInput();

#define TRACE_DELTA_TIME
#ifdef TRACE_DELTA_TIME
    static float time = 0.f;
    time += fDeltaTime;
    float fTraceInterval = 1.5f;
    if( time > fTraceInterval )
    {
        THOT_TRACE("DeltaTime = %f;    FPS = %f\n", fDeltaTime, 1.f/fDeltaTime );
        time = 0.f;
    }
#endif

}

void OnAppNoFocus()
{
}

void OnBeginFrame()
{
    CFrameTimeManager::GetInstance()->OnBeginFrame();
    CGameManager::GetInstance()->OnBeginFrame();

#if defined(THOT_ENABLE_PROFILER)
    ThotProfiler::CManager::GetInstance()->OnBeginFrame();
#endif
}

void OnEndFrame( )
{
    CGameManager::GetInstance()->OnEndFrame();
#if defined(THOT_ENABLE_PROFILER)
    ThotProfiler::CManager::GetInstance()->OnEndFrame();
#endif

    CFrameTimeManager::GetInstance()->OnEndFrame();
}


bool InitGameParams ( )
{
    //STACK_WALKER_INIT();
    //TODO: read this string from a Launcher.config
    
    CString cmdLine = "width=1280 height=600 fullscreen=0";
    ParseCommandLine( cmdLine, GetGameParams() );
    return true;
}

SGameStartupParams&  GetGameParams( )
{
    static SGameStartupParams obj;
    return obj;
}

void ResizeRender ( int width, int height )
{
    if( CRender::GetInstance() )
    {
        CRender::GetInstance()->SetWidth( width );
        CRender::GetInstance()->SetHeight( height );
    }
}


void KeyInputCallback( InputKey::EKeys eKey, bool bButtonDown )
{
    if( !CInput::GetInstance() )
    {
        return;
    }

    CKeyInputInterface::s_KeyInputCallback( eKey, bButtonDown, CInput::GetInstance()->GetDeviceInput( InputDevices::E_INPUT_DEVICE_KEYBOARD ) );
}

void MouseButtonInputCallback( InputKey::EMouseButton eKey, bool bButtonDown )
{
    if( !CInput::GetInstance() )
    {
        return;
    }

    CMouseInputInterface::s_MouseButtonInputCallback( eKey, bButtonDown,  CInput::GetInstance()->GetDeviceInput( InputDevices::E_INPUT_DEVICE_MOUSE ) );
}

void MouseMoveInputCallback( int dx, int dy )
{
    if( !CInput::GetInstance() )
    {
        return;
    }

    THOT_ASSERT( CInput::GetInstance(), "NULL INPUT" );
    CMouseInputInterface::s_MouseMoveInputCallback( dx, dy, CInput::GetInstance()->GetDeviceInput( InputDevices::E_INPUT_DEVICE_MOUSE ) );
}


void MouseWheelInputCallback( int zDelta )
{
    if( !CInput::GetInstance() )
    {
        return;
    }

    CMouseInputInterface::s_MouseWheelInputCallback( zDelta , CInput::GetInstance()->GetDeviceInput( InputDevices::E_INPUT_DEVICE_MOUSE ) );
}




}//namespace Game