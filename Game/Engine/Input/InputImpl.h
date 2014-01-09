#pragma once
#ifndef __INPUT_IMPL_H__
#define __INPUT_IMPL_H__

#include "Input\Input.h"
#include "Input\KeyboardInput.h"
#include "Input\MouseInput.h"

class  CInputImpl:public CInput
{
public:
     CInputImpl();
    ~CInputImpl();

    const CDeviceInputInterface*    GetDeviceInput      ( InputDevices::eDevices eDeviceType )const;
    CDeviceInputInterface*          GetDeviceInput      ( InputDevices::eDevices eDeviceType );
    void                            OnBeforeUserInput   ( );    // here you should reset al input data; because if there is no input; the callbacks will not be called for no input;
    void                            OnAfterUserInput    ( );    
    void                            ClearInputBuffers   ( );
    float                           GetDeltaTime        ( )const;
    void                            SetDeltaTime        ( float fDeltaTime )    { m_fDeltaTime = fDeltaTime; }



private:
    typedef CStaticArray<CDeviceInputInterface*, InputDevices::E_INPUT_DEVICE_COUNT> TDevices;
    TDevices        m_aDevices;
    float           m_fDeltaTime;
};


#endif