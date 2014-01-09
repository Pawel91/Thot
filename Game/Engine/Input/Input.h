#ifndef __INPUT_H__
#define __INPUT_H__

#include "Input\InputTypes.h"
struct tVect2;

/**
    Base interface for all devices;
*/
class INPUT_API CDeviceInputInterface
{
friend class CInput;


public:
                CDeviceInputInterface(){}
virtual         ~CDeviceInputInterface(){}

public:
virtual     InputDevices::eDevices      GetDeviceType       ( );
virtual     void                        ClearInputBuffer    ( )        = 0;
virtual     void                        OnBeforeUserInput   ( )        = 0;
virtual     void                        OnAfterUserInput    ( )        = 0;

protected:
    InputDevices::eDevices        m_eDeviceType;
};


/**
    Input for all buttons
*/
class INPUT_API CKeyInputInterface:public CDeviceInputInterface
{
public:
                CKeyInputInterface();
virtual        ~CKeyInputInterface(){}

virtual     Bool            ButtonPress             ( InputKey::EKeys eKey ) const                          = 0;
virtual     Bool            ButtonUp                ( InputKey::EKeys eKey ) const                          = 0;
virtual     Bool            ButtonDown              ( InputKey::EKeys eKey ) const                          = 0;
virtual     void            OnUserInput             ( InputKey::EKeys eKey, Bool bButtonDown )              = 0;


static      void            s_KeyInputCallback    ( InputKey::EKeys eKey, Bool bButtonDown, void* pThis );
protected:
};

/**
    Mouse movement input
*/
class INPUT_API CMouseInputInterface: public CDeviceInputInterface
{
public:
     CMouseInputInterface() { m_eDeviceType = InputDevices::E_INPUT_DEVICE_MOUSE;}
    ~CMouseInputInterface() { }

virtual     const tVect2&       GetMouseDelta       ( )const                                            = 0;
virtual     int                 GetMouseWheelDelta  ( )const                                            = 0;
virtual     Bool                ButtonPress         ( InputKey::EMouseButton eKey ) const               = 0;
virtual     Bool                ButtonUp            ( InputKey::EMouseButton eKey ) const               = 0;
virtual     Bool                ButtonDown          ( InputKey::EMouseButton eKey ) const               = 0;
virtual     void                OnUserInput         ( InputKey::EMouseButton eKey, Bool bButtonDown )   = 0;
virtual     void                OnMouseMove         ( int dx, int dy )                                  = 0;
virtual     void                OnMouseWheel        ( int zDelta )                                      = 0;

static      void                s_MouseButtonInputCallback      ( InputKey::EMouseButton eKey, Bool bButtonDown, void* pThis );
static      void                s_MouseMoveInputCallback        ( int dx, int dy, void* pThis );
static      void                s_MouseWheelInputCallback       ( int zDelta, void* pThis );
};


/**
    Manager of all input devices
*/
class INPUT_API CInput
{
public:
            CInput(){}
virtual     ~CInput(){}

virtual     const CDeviceInputInterface*    GetDeviceInput      ( InputDevices::eDevices eDeviceType )const         = 0;
virtual     CDeviceInputInterface*          GetDeviceInput      ( InputDevices::eDevices eDeviceType )              = 0;
virtual     void                            OnBeforeUserInput   ( )                                                 = 0;    // here you should reset al input data; because if there is no input; the callbacks will not be called for no input;
virtual     void                            OnAfterUserInput    ( )                                                 = 0;    
virtual     void                            ClearInputBuffers   ( )                                                 = 0;
virtual     float                           GetDeltaTime        ( )const                                            = 0;
virtual     void                            SetDeltaTime        ( float fDeltaTime )                                = 0;


static      Bool                            CreateInstance    ( );
static      CInput*                         GetInstance       ( );
static      Bool                            DestroyInstance   ( );

protected:
static      CInput*                         s_pInstance;

public:

template<class T>
    const T*                        GetDeviceInputT        ( InputDevices::eDevices eDeviceType )const;

};



template<class T>
const T* CInput::GetDeviceInputT ( InputDevices::eDevices eDeviceType )const
{
    //return (const T*) ( CInput::GetDeviceInput( eDeviceType ) );
    THOT_ASSERT(CInput::GetInstance()!=NULL);
    return (const T*) CInput::GetInstance()->GetDeviceInput(eDeviceType);
}



namespace Input
{
#if defined(THOT_PLATFORM_WINDOWS)
    INPUT_API       Bool        Init( void* windowHandle );
#else
#   error Undefined platform
#endif
    INPUT_API       Bool        Shutdown( );
}




#endif /*__INPUT_H__*/