#include "Input_PCH.h"
#include "KeyboardInput.h"

CKeyInput::CKeyInput()
:m_pInput            ( NULL )
,m_pLastFrameInput    ( NULL )
{
    m_pInput = &m_aBuffer1;
    m_pLastFrameInput = &m_aBuffer2;
    m_eDeviceType = InputDevices::E_INPUT_DEVICE_KEYBOARD;

    for( register int i=0; i<m_pInput->GetSize(); i++ )
    {
        m_pInput->operator[](i) = m_pLastFrameInput->operator[](i) = 0;
    }
}


Bool CKeyInput::ButtonPress( InputKey::EKeys eKey ) const
{
    unsigned char& pByte = m_pInput->At( ((int)eKey)/8 )  ;
    int nBitCount = ((int)eKey)%8;
    return ( pByte & (1<<(7-nBitCount)) )?true:false;
}

Bool CKeyInput::ButtonUp( InputKey::EKeys eKey ) const
{
    if( !ButtonPress( eKey, 1 ) && ButtonPress( eKey, 0) )
        return true;

    return false;
}

Bool CKeyInput::ButtonDown ( InputKey::EKeys eKey ) const
{

    if( ButtonPress( eKey, 1 ) && !ButtonPress( eKey, 0) )
        return true;

     return false;
}

void CKeyInput::OnBeforeUserInput ( )
{
    //SwapInputBuffers();
    //ClearInputForThisFrame();
    for( register int i=0; i<m_pInput->GetSize(); i++ )
        m_pLastFrameInput->At(i) = m_pInput->At(i);
}

void CKeyInput::OnAfterUserInput ( )
{


}



void CKeyInput::ClearInputBuffer    ( )
{
    // TO DO:
    for( register int  i=0; i<m_pInput->GetSize(); i++ )
        m_pInput->At(i) = m_pLastFrameInput->At(i) = 0;    
}

void CKeyInput::SwapInputBuffers ( )
{
    tInputBuffer* tmpPtr = m_pInput;
    m_pInput = m_pLastFrameInput;
    m_pLastFrameInput = tmpPtr;
}

void CKeyInput::ClearInputForThisFrame    ()
{
    for( register int i=0; i<m_pInput->GetSize(); i++ )
        m_pInput->At(i) = 0;
}

Bool CKeyInput::ButtonPress ( InputKey::EKeys eKey, Bool bThisFrame )const
{
    tInputBuffer* pInputBuffer = ( bThisFrame )? m_pInput: m_pLastFrameInput;

    unsigned char& pByte = pInputBuffer->At(((int)eKey)/8);
    int nBitCount = ((int)eKey)%8;
    return ( pByte & (1<<(7-nBitCount)) )?true:false;
}

void CKeyInput::OnUserInput( InputKey::EKeys eKey, Bool bButtonDown )
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

