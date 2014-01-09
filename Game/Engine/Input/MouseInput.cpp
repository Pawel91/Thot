#include "Input_PCH.h"
#include "MouseInput.h"

#include "MathCore\MathCore.h"


CMouseInput::CMouseInput()
:m_vMouseDelta        ( tVect2::nullVect )
,m_pInput            ( NULL )
,m_pLastFrameInput    ( NULL )
,m_nWheelDelta        ( 0 )
{
    m_eDeviceType = InputDevices::E_INPUT_DEVICE_MOUSE;

    for( register int i=0; i<m_aBuffer1.GetSize(); i++ )
        m_aBuffer1[i] = m_aBuffer2[i] = 0;

    m_pInput = &m_aBuffer1;
    m_pLastFrameInput = & m_aBuffer2;
}

CMouseInput::~CMouseInput()
{

}

//const tVect2& CMouseInput:: GetMousePos( )const
//{
//    return tVect2::nullVect;
//}

const tVect2& CMouseInput::GetMouseDelta( )const
{
    return m_vMouseDelta;
}

int CMouseInput::GetMouseWheelDelta    ( )const
{
    return m_nWheelDelta;
}

Bool CMouseInput::ButtonPress( InputKey::EMouseButton eKey ) const
{
    unsigned char& pByte = m_pInput->At( ((int)eKey)/8 )  ;
    int nBitCount = ((int)eKey)%8;
    return ( pByte & (1<<(7-nBitCount)) )?true:false;
}

Bool CMouseInput::ButtonUp( InputKey::EMouseButton eKey ) const
{
    if( !ButtonPress( eKey, 1 ) && ButtonPress( eKey, 0) )
        return true;

    return false;
}

Bool CMouseInput::ButtonDown( InputKey::EMouseButton eKey ) const
{
    if( ButtonPress( eKey, 1 ) && !ButtonPress( eKey, 0) )
        return true;

     return false;
}

void CMouseInput::OnUserInput( InputKey::EMouseButton eKey, Bool bButtonDown )
{
    tInputBuffer* pInputBuffer =  m_pInput;;

    unsigned char& pByte = pInputBuffer->At(((int)eKey)/8);
    int nBitCount = ((int)eKey)%8;
    int mask = (1<<(7-nBitCount));
    
    if( bButtonDown )
        pByte |= mask;
    else
        pByte &= ~mask;

}




void CMouseInput::OnBeforeUserInput    ( )
{
    for( register int i=0; i<m_pInput->GetSize(); i++ )
        m_pLastFrameInput->At(i) = m_pInput->At(i);

    m_nWheelDelta = 0;
    m_vMouseDelta = tVect2::nullVect;
}

void CMouseInput::OnAfterUserInput ( )
{
#ifdef _DBG_MOUSE_INPUT
    for( register int i=0; i<InputKey::E_MOUSEB_COUNT; i++ )
        {

            if( ButtonDown( (InputKey::EMouseButton)i ) )
                THOT_TRACE( "BUTTON DOWN %s  \n", InputKey::MOUSEB_STRING_ARRAY[i] );
            else
            if( ButtonUp( (InputKey::EMouseButton)i ) )
                THOT_TRACE( "BUTTON UP %s  \n", InputKey::MOUSEB_STRING_ARRAY[i] );
        }

    if( m_nWheelDelta!=0 )
        THOT_TRACE( "WHELL DELTA = %d\n", m_nWheelDelta );
#endif

}

void CMouseInput::ClearInputBuffer ( )
{
    for( register int i=0; i<m_aBuffer1.GetSize(); i++ )
        m_aBuffer1[i] = m_aBuffer2[i] = 0;
}

Bool CMouseInput::ButtonPress ( InputKey::EMouseButton eKey, Bool bThisFrame )const
{
    tInputBuffer* pInputBuffer = ( bThisFrame )? m_pInput: m_pLastFrameInput;

    unsigned char& pByte = pInputBuffer->At(((int)eKey)/8);
    int nBitCount = ((int)eKey)%8;
    return ( pByte & (1<<(7-nBitCount)) )?true:false;

}


void CMouseInput::OnMouseMove ( int dx, int dy )
{
    m_vMouseDelta.x = (float)dx;
    m_vMouseDelta.y = (float)dy;

#ifdef _DBG_MOUSE_INPUT
    THOT_TRACE("MouseDelta = %d, %d\n", dx, dy);
#endif
}

void CMouseInput::OnMouseWheel ( int zDelta )
{
    m_nWheelDelta = zDelta;
}
