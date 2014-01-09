//#pragma once
//#ifndef __RENDER_CAMERA_GL_H__
//#define __RENDER_CAMERA_GL_H__
//
//#include "RenderCamera.h"
//
//#include "Render/ShaderFramework/ShaderParameterProvider.h"
//
///**
//    RenderCamera Interface
//*/
//class CRenderCameraGL: public CRenderCamera
//{
//DECLARE_RTTI(CRenderCameraGL, CRenderCamera );
//
//#pragma region CONSTRUCTORS
//public:
//      CRenderCameraGL( );        // constructing a valid render camera with standard params;
//     ~CRenderCameraGL( ){}
//
//#pragma endregion CONSTRUCTORS
//
//#pragma region INTERFACE
//public:
//
////********** Get Functions; declare all const;
//virtual     void            GetTM               ( m4x4& mOut ) const            override;
//virtual     void            GetInvTM            ( m4x4& mOut ) const            override;
//virtual     float           GetFov              ( ) const                       override;
//virtual     float           GetZNear            ( ) const                       override;
//virtual     float           GetZFar             ( ) const                       override;
//virtual     void            GetPos              ( tVect3& vOutPos )             override;
//virtual     void            GetProjection       ( m4x4& out )                   override;
//virtual     void            GetWorldToClipMatrix( m4x4& out )                   override;
//virtual     float           GetScreenRatio      ()                              override;
//
////********** Set Functions
//virtual     void            SetScreenRatio      ( float ratio)                  override;
//virtual     void            SetProjection       ( const m4x4& projection)       override;
//virtual     void            SetTM               ( const m4x4& mTM )             override;
//virtual     void            SetPos              ( const tVect3& vPos)           override;
//virtual     void            SetFov              ( float fFov  )                 override;
//virtual     void            SetZNear            ( float fZNear)                 override;
//virtual     void            SetZFar             ( float ZFar )                  override;
//
//#pragma endregion INTERFACE
//
//protected:
//        //void            RebuildInvMat    ();
//        void            RebuildMatrices  ();
//
//
//#pragma region MEMBERS
//
//    m4x4        m_TM;
//    m4x4        m_projectionMatrix;
//    m4x4        m_InvTM;
//    m4x4        m_worldToClip;
//
//    float       m_screenRatio;
//    float       m_fFov;
//    float       m_fZNear;
//    float       m_fZFar;
//
//#pragma endregion
//
//};
//
//
//
//#endif /*__RENDER_CAMERA_GL_H__*/