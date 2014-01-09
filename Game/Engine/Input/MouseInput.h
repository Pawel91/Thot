#pragma once
#ifndef __MOUSE_INPUT_H__
#define  __MOUSE_INPUT_H__
#include "Input.h"


#include "Kernel/DataStructures/Array/Array.h"
#include "MathCore/Vector/Vector.h"
//#ifdef _DEBUG
//#define _DBG_MOUSE_INPUT
//#endif

class CMouseInput:public CMouseInputInterface
{
public:
     CMouseInput( );
    ~CMouseInput( );

virtual         const tVect2&       GetMouseDelta           ( )const;
virtual         int                 GetMouseWheelDelta      ( )const;
virtual         Bool                ButtonPress             ( InputKey::EMouseButton eKey ) const;
virtual         Bool                ButtonUp                ( InputKey::EMouseButton eKey ) const;
virtual         Bool                ButtonDown              ( InputKey::EMouseButton eKey ) const;

virtual         void                OnUserInput             ( InputKey::EMouseButton eKey, Bool bButtonDown );
virtual         void                OnMouseMove             ( int dx, int dy );
virtual         void                OnMouseWheel            ( int zDelta );

virtual         void                OnBeforeUserInput       ( );    
virtual         void                OnAfterUserInput        ( );    
virtual         void                ClearInputBuffer        ( );

protected:
            Bool                ButtonPress                 ( InputKey::EMouseButton eKey, Bool bThisFrame = true )const;
    typedef CStaticArray< unsigned char, InputKey::E_MOUSEB_BYTES_COUNT> tInputBuffer;

        tVect2                  m_vMouseDelta;
        int                     m_nWheelDelta;

        tInputBuffer            m_aBuffer1;
        tInputBuffer            m_aBuffer2;

        tInputBuffer*           m_pInput;
        tInputBuffer*           m_pLastFrameInput;

};
#endif /*__MOUSE_INPUT_H__*/