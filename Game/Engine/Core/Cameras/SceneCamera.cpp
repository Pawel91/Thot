#include "Core_PCH.h"
#include "SceneCamera.h"

#include "Input/Input.h"
#include "Render/Render.h"
#include "Render/RenderCamera.h"

//-----------------------------------------------------------------------
CSceneCameraBase::CSceneCameraBase()
:m_vRot            ( nullVect )
,m_vPos            ( 2.f, 2.f, -5.f )
,m_fFov            ( 52.f )
,m_fCameraSpeed    ( 1.f )
{

}

//-----------------------------------------------------------------------
CSceneCameraBase::~CSceneCameraBase()
{

}

//-----------------------------------------------------------------------
void CSceneCameraBase::OnInit()
{

}

//-----------------------------------------------------------------------
void CSceneCameraBase::GetCameraTM( m4x4& out )
{
    out = i4x4;
    m4x4 mRotY;
    MakeYMat( m_vRot.y, mRotY );
    m4x4 mRotX;
    MakeAnyRotMat(AXEX(mRotY), m_vRot.x, mRotX);
    out = mRotY * mRotX;

    POS(out) = m_vPos;
}

//-----------------------------------------------------------------------
void CSceneCameraBase::GetRotation ( m3x3& out )const
{
    //MakeYXZMat( m_vRot.y, m_vRot.x, m_vRot.z, out );
    out = i3x3;
    m3x3 mRotY;
    MakeYMat( m_vRot.y, mRotY);
    m3x3 mRotX;
    MakeXMat( m_vRot.x, mRotX);
    //out = /*i4x4 **/ mRotX * mRotY;
    out *= mRotX;
    out *= mRotY;

}

//-----------------------------------------------------------------------
void CSceneCameraBase::Apply()
{
    CRenderCamera* pRenderCamera = CRender::GetInstance()->GetCamera();
    m4x4 mCameraTM;
    GetCameraTM( mCameraTM );
    m_transformComponent.SetLocalTM( mCameraTM );
    float fFOV = m_fFov;

    pRenderCamera->SetTM ( mCameraTM );
    pRenderCamera->SetFov( fFOV );
}

//-----------------------------------------------------------------------
void CSceneCameraBase::OnUpdateThis( float fDeltaTime )
{
    CInput& input =  *CInput::GetInstance();

    const CMouseInputInterface* pMouse = input.GetDeviceInputT<CMouseInputInterface>(InputDevices::E_INPUT_DEVICE_MOUSE);
    const CKeyInputInterface* pKeyboard = input.GetDeviceInputT<CKeyInputInterface>(InputDevices::E_INPUT_DEVICE_KEYBOARD);
    tVect2 mouseDelta = pMouse->GetMouseDelta();
    //if( VectLenSquared(mouseDelta)<2.f )
    //    mouseDelta = tVect2::nullVect;

    float fSmoothFactor = 1.f;
    mouseDelta *= fSmoothFactor * fDeltaTime;

    m_vRot.x -= mouseDelta.y * 5.f;
    m_vRot.y -= mouseDelta.x * 5.f;
    //MakeCanonicalEuler(m_vRot);
    //THOT_TRACE( "FreeCamRot = %.3f, %.3f \n", m_vRot.x, m_vRot.y );

    m3x3 mRot;
    GetRotation(mRot);
    //tVect3 vDir = AXEZ(mRot);
    //m_vPos += vDir * m_fCameraSpeed * fDeltaTime;
    if( pKeyboard->ButtonPress(InputKey::E_KEY_W))
    {
        m_vPos += AXEZ(mRot) * m_fCameraSpeed * fDeltaTime;
    }

    if( pKeyboard->ButtonPress(InputKey::E_KEY_S))
    {
        m_vPos += -AXEZ(mRot) * m_fCameraSpeed * fDeltaTime;
    }

    if( pKeyboard->ButtonPress(InputKey::E_KEY_D))
    {
        m_vPos += AXEX(mRot) * m_fCameraSpeed * fDeltaTime;
    }

    if( pKeyboard->ButtonPress(InputKey::E_KEY_A))
    {
        m_vPos += -AXEX(mRot) * m_fCameraSpeed * fDeltaTime;
    }


    int nMouseDelta = pMouse->GetMouseWheelDelta();
    if( nMouseDelta > 0 )
        m_fCameraSpeed *= 1.2f;
    else if( nMouseDelta < 0 )
        m_fCameraSpeed *= 0.8f;

    if( nMouseDelta != 0 )
    {
        THOT_TRACE_LINE( "FreeCamSpeed = %f", m_fCameraSpeed );
    }

    Apply(); // apply to render camera;
}

