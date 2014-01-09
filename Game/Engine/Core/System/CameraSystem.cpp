#include "Core_PCH.h"
#include "CameraSystem.h"

#include "Core/Components/CameraComponent.h"
#include "Core/EntitySystem/Entity.h"
#include "Core/Components/CameraComponent.h"
#include "Core/FrameTimeManager.h"
#include "Input/Input.h"

//-------------------------------------------------------------
CCameraSystem::CCameraSystem()
    : m_activeCameraIndex ( 0 )
{
    
}

//-------------------------------------------------------------
CCameraSystem::~CCameraSystem()
{

}

//-------------------------------------------------------------
void CCameraSystem::OnInit()
{

}

void CCameraSystem::Execute( )
{
    float deltaTime = CFrameTimeManager::GetInstance()->GetGameTime();

    CInput& input =  *CInput::GetInstance();
    const CMouseInputInterface* pMouse = input.GetDeviceInputT<CMouseInputInterface>(InputDevices::E_INPUT_DEVICE_MOUSE);
    const CKeyInputInterface* keyboard = input.GetDeviceInputT<CKeyInputInterface>(InputDevices::E_INPUT_DEVICE_KEYBOARD);

    if( keyboard->ButtonPress(InputKey::E_KEY_0) )
    {
        m_activeCameraIndex = 0;        
    }
    else if( keyboard->ButtonPress(InputKey::E_KEY_1) )
    {
        m_activeCameraIndex = 1;
    }
    else if( keyboard->ButtonPress(InputKey::E_KEY_2) )
    {
        m_activeCameraIndex = 2;        
    }
    else if( keyboard->ButtonPress(InputKey::E_KEY_3) )
    {
        m_activeCameraIndex = 3;        
    }
    else if( keyboard->ButtonPress(InputKey::E_KEY_4) )
    {
        m_activeCameraIndex = 4;
    }
    else if( keyboard->ButtonPress(InputKey::E_KEY_5) )
    {
        m_activeCameraIndex = 5;
    }
    else if( keyboard->ButtonPress(InputKey::E_KEY_6) )
    {
        m_activeCameraIndex = 6;
    }
    else if( keyboard->ButtonPress(InputKey::E_KEY_7) )
    {
        m_activeCameraIndex = 7;
    }
    else if( keyboard->ButtonPress(InputKey::E_KEY_8) )
    {
        m_activeCameraIndex = 8;
    }
    else if( keyboard->ButtonPress(InputKey::E_KEY_9) )
    {
        m_activeCameraIndex = 9;
    }




    m_activeCameraIndex = ThClamp<u32>( 0, ThNumericCast<u32>( m_cameraEntities.Size() ), m_activeCameraIndex );

    THOT_ASSERT(m_cameraEntities.Size() > 0);

    //for( u64 i=0; i<m_cameraEntities.GetSize(); i++ )
    {
        CEntityHandle& handle = m_cameraEntities[m_activeCameraIndex];
        CCameraComponentBase* cameraComponent =  handle->GetComponent<CCameraComponentBase>();
        cameraComponent->OnUpdate( deltaTime );
    }
}

//-------------------------------------------------------------
void CCameraSystem::RegisterComponents()
{
    RegisterComponent<CCameraComponentBase>();
}

//-------------------------------------------------------------
void CCameraSystem::OnEntityComponentChange(const CEntityHandle& handle,
                                            IComponent* component,
                                            bool Added )
{
    if( Added )
    {
        if( handle->GetComponent<CCameraComponentBase>() )
        {
            m_cameraEntities.PushBack( handle );
        }
    }
    else
    {
        THOT_TODO("REMOVE THE ENTITY FROM ENTITIES VECTOR");
    }
}
