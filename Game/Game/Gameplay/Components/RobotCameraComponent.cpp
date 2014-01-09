#include "Game_PCH.h"
#include "RobotCameraComponent.h"

#include "Render/RenderCamera.h"
#include "Render/Render.h"
#include "Core/Components/BindingComponent.h"
#include "Core/EntitySystem/Entity.h"
#include "MathCore/MathUtils.h"
#include "Input/Input.h"

//--------------------------------------------------------------------------------
CRobotCameraComponent:: CRobotCameraComponent()
    : m_parentToCameraDir       ( 0.f, 1.f, -1.f)
    , m_parentToCameraDistance  ( 16.f )
{
    VectNor( m_parentToCameraDir);
}

//--------------------------------------------------------------------------------
CRobotCameraComponent::~CRobotCameraComponent()
{
}

//--------------------------------------------------------------------------------
void CRobotCameraComponent::OnUpdate( float deltaTime )
{
    m_bindingComponent = NULL;
    if( (m_bindingComponent = m_entity->GetComponent<CBindingComponent>()) == NULL )
    {
        return;
    }

    // verify that this camera is attached on an valid entity
    CEntityHandle& parentEntity = m_bindingComponent->GetParent();
    if( !parentEntity )
    {
        return;
    }

    PrivateUpdate( deltaTime );

    Apply();
}

//--------------------------------------------------------------------------------
void CRobotCameraComponent::PrivateUpdate(float deltaTime)
{
    THOT_ASSERT(m_bindingComponent);
    
    CInput& input =  *CInput::GetInstance();
    const CMouseInputInterface* pMouse = input.GetDeviceInputT<CMouseInputInterface>(InputDevices::E_INPUT_DEVICE_MOUSE);
    const CKeyInputInterface* pKeyboard = input.GetDeviceInputT<CKeyInputInterface>(InputDevices::E_INPUT_DEVICE_KEYBOARD);


    tVect2 mouseDelta = pMouse->GetMouseDelta();

    m4x4 rotMatrix = i4x4;

    m4x4 currentCameraTM;
    GetCameraTM(currentCameraTM);

    m4x4 rotYAxisMatrix = i4x4;
    MakeAnyRotMat( AXEY( currentCameraTM ), - mouseDelta.x * deltaTime * 20.f, rotYAxisMatrix);

    m4x4 rotXAxisMatrix = i4x4;
    MakeAnyRotMat( AXEX(rotYAxisMatrix), - mouseDelta.y * deltaTime * 20.f, rotXAxisMatrix );

    rotMatrix = rotYAxisMatrix * rotXAxisMatrix;

    m_parentToCameraDir = m_parentToCameraDir * rotMatrix;

    m4x4 localMatrix = i4x4;
    GetCameraTM( localMatrix );

    m_bindingComponent->SetLocalTM( localMatrix );
}

//--------------------------------------------------------------------------------
void CRobotCameraComponent::Apply()
{
    // apply the current camera parameters to the render camera;

    CRenderCamera* pRenderCamera = CRender::GetInstance()->GetCamera();
    
    const m4x4& cameraToWorldTM =  m_bindingComponent->GetWorldTM( true );

    pRenderCamera->SetTM ( cameraToWorldTM );
    pRenderCamera->SetFov( 82.f );
}

//--------------------------------------------------------------------------------
void CRobotCameraComponent::GetCameraTM( m4x4& outTM)
{
    outTM = i4x4;
    MathUtils::GetMatFromZDir( -m_parentToCameraDir, outTM); // camera is looking at parent
    POS(outTM) = m_parentToCameraDir * m_parentToCameraDistance;
}