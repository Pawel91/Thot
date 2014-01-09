#pragma once
#ifndef __LIGHTS_BASE_H__
#define __LIGHTS_BASE_H__

#include "Kernel\Kernel.h"
#include "MathCore\MathCore.h"
#include "Render\Lights\LightTypes.h"
#include "Render\Color.h"
#include "Render\RenderCamera.h"
#include "Render\Render.h"


//=========================================================================================
//================================= CLightBase ============================================
//=========================================================================================


/**
    Abstract Light;
*/
template class RENDER_API CStaticArray<CColor,E_LIGHT_COMP_COUNT>;

class RENDER_API CLightBase
{
public:
             CLightBase();
             CLightBase( const CLightBase& other );
virtual     ~CLightBase()            = 0;

// for dynamic lights;
virtual             void            OnUpdate                ( float fDeltaTime ){}

//*******GET/CONST  functions

virtual             eLightType      GetLightType            ( )const ;

/**
    Default all color components should be black;
*/
virtual             const CColor&   GetColor                ( eLightComponents component)const;
virtual             void            GetColor                ( eLightComponents component, CColor& out )    const;
virtual             void            SetColor                ( eLightComponents component, const CColor& color );


    
protected:
typedef CStaticArray<CColor,E_LIGHT_COMP_COUNT>    tColorCompArray;

    eLightType              m_eType;
    tColorCompArray         m_aColorComp;
};


//====================================================================================================
//================================= CDirectionalLightBase ============================================
//====================================================================================================


class RENDER_API CDirectionalLightBase:public CLightBase
{
typedef CLightBase super;
public:
     CDirectionalLightBase( );
     CDirectionalLightBase( const CDirectionalLightBase& other );
    ~CDirectionalLightBase( );


//*******GET/CONST  functions
virtual            void            GetDirection            ( tVect3& outDir )const;
virtual            void            SetDirection            ( const tVect3& vDir );

protected:

    tVect3            m_vDirection;
};


//====================================================================================================
//================================= CPositionalLightBase =============================================
//====================================================================================================


/**
    Positional light; it has a position and an attenuation factor
*/
class CPositionalLightBase:public CLightBase
{
typedef CLightBase super; 
public:
             CPositionalLightBase();
             CPositionalLightBase( const CPositionalLightBase& other);
virtual     ~CPositionalLightBase();


virtual            void            GetPosition                ( tVect3& outPos )const;
virtual            void            SetPosition                ( const tVect3& vPos );


virtual             void            OnUpdate                ( float fDeltaTime )
{
    //static float fSpeed = 1.f;
    //m_vPosition += yAxis * fSpeed * fDeltaTime;

    //if( VectLen( m_vPosition - nullVect ) > 3.f )
    //{
    //    fSpeed *= -1.f;
    //}

}
/**
    Attenuation factor for a positional light = 1.f/ ( c + l * d + q * d *d  ) where d is the distance from surface to the light
    clqOut.x = c; clqOut.y = l; clqOut.z = q;
*/
virtual            void            GetAttenuationFactor        ( tVect3& clqOut)const;
virtual            void            SetAttenuationFactor        (const tVect3& clq);
protected:

        tVect3                    m_vPosition;
        tVect3                    m_vAttenuationFactor;
        
};



//====================================================================================================
//================================= CSpotLightBase ===================================================
//====================================================================================================



/**
    SpotLight class. A Spotlight is a also a positional and a directional light. In addition it has a cutoff angle and a spot exponent;
*/
class CSpotLightBase:public CPositionalLightBase
{
typedef CPositionalLightBase super;
public:
        
         CSpotLightBase();
         CSpotLightBase( const CSpotLightBase& other );
virtual    ~CSpotLightBase();



/**
    direction of the spotlight; default should be zaxis;
*/
virtual                void            GetSpotDirection            ( tVect3& outDir)const;
virtual                void            SetSpotDirection            ( const tVect3& vDir );


/** 
    Values ranges from 0.f to 90.f degrees + 180.f
    Default value should be180.f; same effect as positional light;
*/ 
virtual                 float           GetCutoff               ( )const;
virtual                 void            SetCutoff               ( float fCutoff );
inline                  float           GetCosCutoff            ( )const { return cos( GetCutoff() * TO_RAD );  }

/** 
    Values ranges from 0.f to 128.f 
    Default value should be 0.f which results in no attenuation of the spotlight;
*/ 
virtual                 float           GetSpotExponent                ( )const;
virtual                 void            SetSpotExponent                ( float fExponent );


virtual             void            OnUpdate                ( float fDeltaTime )
{
    static CRenderCamera* renderCamera = CRender::GetInstance()->GetCamera();
    THOT_ASSERT(renderCamera);

    tVect3 vPos = nullVect;
    renderCamera->GetPos( vPos );

    m4x4 cameraMatrix =  i4x4;
    renderCamera->GetTM(cameraMatrix);
    const tVect3& vDir = AXEZ(cameraMatrix);

    SetSpotDirection(vDir);
    SetPosition(vPos);

}

protected:
    tVect3              m_vSpotDirection;
    float               m_fCutoff;
    float               m_fExponent;

};


#endif