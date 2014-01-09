#include "Render_PCH.h"
#include "RenderCameraGL.h"



//IMPLEMENT_RTTI(CRenderCameraGL, CRenderCamera );
//
//CRenderCameraGL:: CRenderCameraGL( )
//:m_TM                   ( i4x4 )
//,m_projectionMatrix     ( i4x4 )
//,m_InvTM                ( i4x4 )
//,m_worldToClip          ( i4x4 )
//,m_screenRatio          ( 16.f/9.f )
//,m_fFov                 ( RENDER_NORMAL_FOV )
//,m_fZNear               ( RENDER_NORMAL_ZNEAR )
//,m_fZFar                ( RENDER_NORMAL_ZFAR )
//{
//
//}
//
//void CRenderCameraGL::GetTM ( m4x4& mOut )const
//{
//    mOut = m_TM;
//}
//
//void CRenderCameraGL::GetInvTM ( m4x4& mOut )const
//{
//    mOut = m_InvTM;
//}
//
//float CRenderCameraGL::GetFov ( )const
//{
//    return m_fFov;
//}
//
//float CRenderCameraGL::GetZNear ( )const
//{
//    return m_fZNear;
//}
//
//float CRenderCameraGL::GetZFar ( )const
//{
//    return m_fZFar;
//}
//
//void CRenderCameraGL::SetTM ( const m4x4& mTM )    
//{
//    THOT_ASSERT(IsOrtho(mTM)); // only orhto matrix for viewing transforms;
//
//    m_TM = mTM;
//    RebuildMatrices();
//}
//
//void CRenderCameraGL::GetPos ( tVect3& vOutPos )
//{
//    vOutPos = POS(m_TM);
//}
//
//void CRenderCameraGL::SetPos ( const tVect3& vPos)
//{
//    POS(m_TM) = vPos;
//    RebuildMatrices();
//}
//
//void CRenderCameraGL::SetFov ( float fFov  )
//{
//    m_fFov = fFov;
//}
//
//void CRenderCameraGL::SetZNear ( float fZNear)
//{
//    m_fZNear = fZNear;
//}
//
//void CRenderCameraGL::SetZFar ( float ZFar )
//{
//    m_fZFar =ZFar;
//}
//
////void CRenderCameraGL::RebuildInvMat ( )
////{
////    m4x4 mToInvert = m_TM;
////
////    m4x4 m = i4x4;
////    InvMat( mToInvert, m_InvTM );
////}
//
//
//void CRenderCameraGL::GetProjection( m4x4& out )
//{
//    out = m_projectionMatrix;
//}
//
//void CRenderCameraGL::GetWorldToClipMatrix( m4x4& out ) 
//{
//    out = m_worldToClip;
//}
//
//void CRenderCameraGL::RebuildMatrices()
//{
//    m4x4 mToInvert = m_TM;
//    m4x4 m = i4x4;
//    InvMat( mToInvert, m_InvTM );
//    m_worldToClip = m_InvTM * m_projectionMatrix;
//}
//
//void CRenderCameraGL::SetProjection( const m4x4& projection) 
//{
//    m_projectionMatrix = projection;
//    RebuildMatrices();
//}
//
//float CRenderCameraGL::GetScreenRatio()
//{
//    return m_screenRatio;
//}
//void  CRenderCameraGL::SetScreenRatio( float ratio)
//{
//    m_screenRatio = ratio;
//
//    // rebuild projection matrix
//    PerspectiveMat( m_fFov, m_screenRatio, m_fZNear, m_fZFar,  m_projectionMatrix);
//    RebuildMatrices();
//}
