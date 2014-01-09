#include "Render_PCH.h"
#include "RenderCamera.h"

//-----------------------------------------------------------------------------------------------
//*** global variables
const float         RENDER_NORMAL_FOV       = 60.f;
const float         RENDER_NORMAL_ZNEAR     = 1.3f;
const float         RENDER_NORMAL_ZFAR      = 800.f;

//-----------------------------------------------------------------------------------------------
CRenderCamera:: CRenderCamera( )
:m_TM                   ( i4x4 )
,m_projectionMatrix     ( i4x4 )
,m_InvTM                ( i4x4 )
,m_worldToClip          ( i4x4 )
,m_screenRatio          ( 16.f/9.f ) // HDMI..ca sa moara fetili :))
,m_fFov                 ( RENDER_NORMAL_FOV )
,m_fZNear               ( RENDER_NORMAL_ZNEAR )
,m_fZFar                ( RENDER_NORMAL_ZFAR )
{
}

//-----------------------------------------------------------------------------------------------
void CRenderCamera::GetTM ( m4x4& mOut )const
{
    mOut = m_TM;
}

//-----------------------------------------------------------------------------------------------
void CRenderCamera::GetInvTM ( m4x4& mOut )const
{
    mOut = m_InvTM;
}

//-----------------------------------------------------------------------------------------------
float CRenderCamera::GetFov ( )const
{
    return m_fFov;
}

//-----------------------------------------------------------------------------------------------
float CRenderCamera::GetZNear ( )const
{
    return m_fZNear;
}

//-----------------------------------------------------------------------------------------------
float CRenderCamera::GetZFar ( )const
{
    return m_fZFar;
}

//-----------------------------------------------------------------------------------------------
void CRenderCamera::SetTM ( const m4x4& mTM )    
{
    THOT_ASSERT(IsOrtho(mTM)); // only orhto matrix for viewing transforms;

    m_TM = mTM;
    RebuildMatrices();
}

//-----------------------------------------------------------------------------------------------
void CRenderCamera::GetPos ( tVect3& vOutPos )const
{
    vOutPos = POS(m_TM);
}

//-----------------------------------------------------------------------------------------------
void CRenderCamera::SetPos ( const tVect3& vPos)
{
    POS(m_TM) = vPos;
    RebuildMatrices();
}

//-----------------------------------------------------------------------------------------------
void CRenderCamera::SetFov ( float fFov  )
{
    m_fFov = fFov;
}

//-----------------------------------------------------------------------------------------------
void CRenderCamera::SetZNear ( float fZNear)
{
    m_fZNear = fZNear;
}

//-----------------------------------------------------------------------------------------------
void CRenderCamera::SetZFar ( float ZFar )
{
    m_fZFar =ZFar;
}

//-----------------------------------------------------------------------------------------------
void CRenderCamera::GetProjection( m4x4& out )const
{
    out = m_projectionMatrix;
}

//-----------------------------------------------------------------------------------------------
void CRenderCamera::GetWorldToClipMatrix( m4x4& out )const
{
    out = m_worldToClip;
}

//-----------------------------------------------------------------------------------------------
void CRenderCamera::RebuildMatrices()
{
    m4x4 mToInvert = m_TM;
    m4x4 m = i4x4;
    InvMat( mToInvert, m_InvTM );
    m_worldToClip = m_InvTM * m_projectionMatrix;
}

//-----------------------------------------------------------------------------------------------
void CRenderCamera::SetProjection( const m4x4& projection) 
{
    m_projectionMatrix = projection;
    RebuildMatrices();
}

//-----------------------------------------------------------------------------------------------
float CRenderCamera::GetScreenRatio()const
{
    return m_screenRatio;
}

//-----------------------------------------------------------------------------------------------
void  CRenderCamera::SetScreenRatio( float ratio)
{
    m_screenRatio = ratio;

    // rebuild projection matrix
    PerspectiveMat( m_fFov, m_screenRatio, m_fZNear, m_fZFar,  m_projectionMatrix);
    RebuildMatrices();
}
