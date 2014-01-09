#ifndef __RENDER_CAMERA_H__
#define __RENDER_CAMERA_H__

#include "Render/RenderDef.h"
#include "Kernel/Kernel.h"
#include "MathCore/MathCore.h"
//#include "Render\RenderDef.h"

class RENDER_API CRenderCamera
{

public:
      CRenderCamera( );
public:

//********** Get Functions; declare all const;
            void            GetTM               ( m4x4& mOut ) const;
            void            GetInvTM            ( m4x4& mOut ) const;
            float           GetFov              ( ) const;
            float           GetZNear            ( ) const;
            float           GetZFar             ( ) const;
            void            GetPos              ( tVect3& vOutPos )const;
            void            GetProjection       ( m4x4& out ) const;
            void            GetWorldToClipMatrix( m4x4& out ) const;
            float           GetScreenRatio      ( ) const;

//********** Set Functions
            void            SetScreenRatio      ( float ratio);
            void            SetProjection       ( const m4x4& projection);
            void            SetTM               ( const m4x4& mTM );
            void            SetPos              ( const tVect3& vPos);
            void            SetFov              ( float fFov  );
            void            SetZNear            ( float fZNear);
            void            SetZFar             ( float ZFar );

protected:

        void            RebuildMatrices  ();

protected:

    m4x4        m_TM;
    m4x4        m_projectionMatrix;
    m4x4        m_InvTM;
    m4x4        m_worldToClip;

    float       m_screenRatio;
    float       m_fFov;
    float       m_fZNear;
    float       m_fZFar;
};


extern const float        RENDER_NORMAL_FOV ;
extern const float        RENDER_NORMAL_ZNEAR ;
extern const float        RENDER_NORMAL_ZFAR ;

#endif /*__RENDER_CAMERA_H__*/