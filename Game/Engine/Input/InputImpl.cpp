#include "Input_PCH.h"
#include "InputImpl.h"

CInputImpl::CInputImpl()
:m_fDeltaTime        ( 0.f )
{
    for( int i=0; i<m_aDevices.GetSize(); i++ )
        m_aDevices[i] = NULL;

    m_aDevices[ InputDevices::E_INPUT_DEVICE_KEYBOARD ]     = THOT_NEW CKeyInput;
    m_aDevices[ InputDevices::E_INPUT_DEVICE_MOUSE ]        = THOT_NEW CMouseInput;
}

const CDeviceInputInterface* CInputImpl::GetDeviceInput ( InputDevices::eDevices eDeviceType )const
{ 
    return m_aDevices[eDeviceType]; 
}

CDeviceInputInterface* CInputImpl::GetDeviceInput ( InputDevices::eDevices eDeviceType )
{
    return m_aDevices[eDeviceType];
}


float CInputImpl::GetDeltaTime ( )const
{
    return m_fDeltaTime;
}

void CInputImpl::OnBeforeUserInput ( )
{
    for( register int i=0; i<m_aDevices.GetSize(); i++ )
        if( m_aDevices[i] )
            m_aDevices[i]->OnBeforeUserInput();
}

void CInputImpl::OnAfterUserInput ( )
{
    for( register int i=0; i<m_aDevices.GetSize(); i++ )
        if( m_aDevices[i] )
            m_aDevices[i]->OnAfterUserInput();
}



void CInputImpl::ClearInputBuffers( )
{
    for( register int i=0; i<m_aDevices.GetSize(); i++ )
    if( m_aDevices[i] )
        m_aDevices[i]->ClearInputBuffer();

}

CInputImpl::~CInputImpl()
{
    for( register int i=0; i<m_aDevices.GetSize(); i++ )
        if( m_aDevices[i] )
            THOT_DELETE(m_aDevices[i]);
}





