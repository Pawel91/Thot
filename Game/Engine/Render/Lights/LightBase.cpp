#include "Render_PCH.h"
#include "LightBase.h"


CLightBase::CLightBase()
:m_eType            ( E_LIGHT_TYPE_NONE )
{
    u64 nSize = m_aColorComp.GetSize();
    for( u64 i=0; i<nSize; i++ )
        m_aColorComp[i] = black; 
}

CLightBase::CLightBase( const CLightBase& other )
{
    m_eType = other.GetLightType();
    
    //copy colors components
    u64 nSize = m_aColorComp.GetSize();
    for( u64 i=0; i<nSize; i++ )
        m_aColorComp[i] = other.m_aColorComp[i];
}

CLightBase::~CLightBase()
{

}

eLightType CLightBase::GetLightType ( )const
{
    return m_eType;
}

const CColor& CLightBase::GetColor( eLightComponents component)const
{
    return m_aColorComp[component];
}

void CLightBase::GetColor ( eLightComponents component, CColor& out )    const
{
    out = m_aColorComp[component];
}

void CLightBase::SetColor ( eLightComponents component, const CColor& color )
{
    m_aColorComp[component] = color;
}


//====================================================================================================
//================================= CDirectionalLightBase ============================================
//====================================================================================================


CDirectionalLightBase::CDirectionalLightBase()
:m_vDirection        ( zAxis )
{
    m_eType = E_LIGHT_TYPE_DIRECTIONAL;
}

CDirectionalLightBase::CDirectionalLightBase( const CDirectionalLightBase& other )
:super            ( other )
,m_vDirection    ( other.m_vDirection )
{
    
}


CDirectionalLightBase::~CDirectionalLightBase()
{

}


void CDirectionalLightBase::GetDirection ( tVect3& outDir )const
{
    outDir = m_vDirection;
}

void CDirectionalLightBase::SetDirection ( const tVect3& vDir )
{
    m_vDirection = vDir;
}


//====================================================================================================
//================================= CPositionalLightBase =============================================
//====================================================================================================

CPositionalLightBase:: CPositionalLightBase()
:m_vPosition                ( nullVect)
,m_vAttenuationFactor        ( 1.f, 0.f, 0.f )            // no attenuation
{
    m_eType = E_LIGHT_TYPE_POSITIONAL;
}

CPositionalLightBase::CPositionalLightBase( const CPositionalLightBase& other)
    :super                    ( other )
    ,m_vPosition            ( other.m_vPosition )
    ,m_vAttenuationFactor    ( other.m_vAttenuationFactor )
{

}

CPositionalLightBase::~CPositionalLightBase()
{
    
}

void CPositionalLightBase::GetPosition ( tVect3& outPos )const
{
    outPos = m_vPosition; 
}

void CPositionalLightBase::SetPosition ( const tVect3& vPos )
{
    m_vPosition = vPos;
}

void CPositionalLightBase::GetAttenuationFactor ( tVect3& clqOut)const
{
    clqOut = m_vAttenuationFactor;
}

void CPositionalLightBase::SetAttenuationFactor (const tVect3& clq)
{
    m_vAttenuationFactor = clq;
}




//====================================================================================================
//================================= CSpotLightBase ===================================================
//====================================================================================================




CSpotLightBase::CSpotLightBase()
:m_vSpotDirection       ( zAxis )
,m_fCutoff              ( 180.f )
,m_fExponent            ( 0.f )
{
    m_eType = E_LIGHT_TYPE_SPOTLIGHT;
}

CSpotLightBase::CSpotLightBase( const CSpotLightBase& other )
:super                ( other )
,m_vSpotDirection    ( other.m_vSpotDirection )
,m_fCutoff            ( other.m_fCutoff )
,m_fExponent        ( other.m_fExponent )
{
}


CSpotLightBase::~CSpotLightBase()
{

}



void CSpotLightBase::GetSpotDirection ( tVect3& outDir)const
{
    outDir = m_vSpotDirection;
}

void CSpotLightBase::SetSpotDirection ( const tVect3& vDir )
{
    m_vSpotDirection = vDir;
}

float CSpotLightBase::GetCutoff ( )const
{
    return m_fCutoff;
}

void CSpotLightBase::SetCutoff ( float fCutoff )
{
    THOT_ASSERT( (fCutoff >= 0.f && fCutoff <= 128.f) || fCutoff == 180.f );
    m_fCutoff = fCutoff;
}

float CSpotLightBase::GetSpotExponent ( )const
{
    return m_fExponent;
}

void CSpotLightBase::SetSpotExponent ( float fExponent )
{
    //THOT_ASSERT( fExponent >= 0.f && fExponent <= 128.f );
    m_fExponent = fExponent;
}

