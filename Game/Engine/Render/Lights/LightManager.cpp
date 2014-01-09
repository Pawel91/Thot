#include "Render_PCH.h"
#include "LightManager.h"
#include "Render\RenderGL.h"
#include "Render/ShaderFramework/Shader.h"

IMPLEMENT_MANAGER_CLASS(CLightManager,CUpdateManager)
THOT_IMPLEMENT_SINGLETON( CLightManager )

//CLightManager*        CLightManager::s_instance = NULL;
//CLightManager*        CLightManager::GetInstance()
//{
//    return s_instance;
//}
//
//CLightManager*        CLightManager::CreateInstance()
//{
//    if( s_instance == NULL )
//        s_instance =  THOT_NEW CLightManager;
//    else
//    {
//        THOT_DELETE(s_instance);
//        s_instance = THOT_NEW CLightManager;
//    }
//
//    return s_instance;
//}
//
//void CLightManager::DestroyInstance()
//{
//        if( s_instance )
//        THOT_DELETE(s_instance);
//}




CLightManager:: CLightManager()
{
    u64 nSize = m_aLights.GetSize();
    for( u64 i=0; i<nSize; i++ )
        m_aLights[i] = NULL;
}

CLightManager::~CLightManager()
{
    u64 nSize = m_aLights.GetSize();
    for( u64 i=0; i<nSize; i++ )
        if( m_aLights[i] )
            THOT_DELETE(m_aLights[i]);
}

void CLightManager::Init ( )
{
    // set a directional light;
    CDirectionalLightBase* pDirLight = THOT_NEW CDirectionalLightBase;
    pDirLight->SetDirection( -Unit( tVect3( -0.852f, 0.350f, -0.389f )) );
    pDirLight->SetColor( E_LIGHT_COMP_AMBIENT, CColor( 0.13f, 0.13f, 0.13f, 1.f ) );
    pDirLight->SetColor( E_LIGHT_COMP_DIFFUSE, CColor( 1.f, 1.f, 1.f, 1.f )  );
    pDirLight->SetColor( E_LIGHT_COMP_SPECULAR, CColor( 0.5f, 0.5f, 0.5f, 1.f )  );
    AddLight(pDirLight);

    //set a positional light
    CPositionalLightBase* pPosLight = THOT_NEW CPositionalLightBase;
    pPosLight->SetPosition( tVect3(-1.f, 1.3f, 0.f) );
    pPosLight->SetColor( E_LIGHT_COMP_AMBIENT, CColor( 0.2f, 0.2f, 0.2f, 1.f ) );
    pPosLight->SetColor( E_LIGHT_COMP_DIFFUSE, CColor( 1.f, 1.f, 1.f, 1.f ) );
    pPosLight->SetColor( E_LIGHT_COMP_SPECULAR, CColor( 1.0f, 0.5f, 0.5f, 1.f ) );
    pPosLight->SetAttenuationFactor( tVect3( 1.f, 1.f, 0.02f) );
    AddLight(pPosLight);

    ////// add a spotlight
    CSpotLightBase* pSpot = THOT_NEW CSpotLightBase;
    pSpot->SetPosition( nullVect );
    pSpot->SetSpotDirection( zAxis );
    pSpot->SetAttenuationFactor( tVect3( 1.f, 0.01f, 0.0f) );
    pSpot->SetCutoff( 45.5f );
    pSpot->SetSpotExponent( 260.f );
    pSpot->SetColor( E_LIGHT_COMP_AMBIENT, CColor( 0.1f, 0.1f, 0.1f, 1.f ) );
    pSpot->SetColor( E_LIGHT_COMP_DIFFUSE, CColor( 1.f, 1.f, 1.f, 1.f ) );
    pSpot->SetColor( E_LIGHT_COMP_SPECULAR, CColor( 1.0f, 1.f, 0.0f, 1.f ) );
    AddLight(pSpot);
}

void CLightManager::OnUpdate ( float fDeltaTime )
{
    u64 nSize = m_aLights.GetSize();
    for( u64 i=0; i<nSize; i++ )
        if( m_aLights[i] )
            m_aLights[i]->OnUpdate( fDeltaTime );
}

Bool CLightManager::AddLight (  CLightBase* pLight )
{
    THOT_ASSERT(pLight != NULL);

    int nSlot = FindFreeLightSlot();
    if( nSlot == -1 )
        return false;

    m_aLights[nSlot] = pLight;

    return true;
}

void CLightManager::ApplyLights ( )
{
    u64 nSize = m_aLights.GetSize();
    for( u64 i=0; i<nSize; i++ )
    {
        if( m_aLights[i] )
        ApplyLight( (int)i );
    }
}

int CLightManager::FindFreeLightSlot    ( )
{
    u64 nSize = m_aLights.GetSize();

    for( u64 i=0; i<nSize; i++ )
    {
        if( m_aLights[i] == NULL )
        {
            return (int) i;
        }
    }

    // there are not free slots to add another light;
    return -1;
}

void CLightManager::ApplyLight ( int nIdx )
{
    THOT_ASSERT( m_aLights[nIdx]!= NULL );

    eLightType type = m_aLights[nIdx]->GetLightType();
    switch(type)
    {
        case E_LIGHT_TYPE_DIRECTIONAL:
        {
            ApplyDirectional( nIdx );
        break;
        }

        case E_LIGHT_TYPE_POSITIONAL:
        {
            ApplyPositional( nIdx );
        break;
        }

    case E_LIGHT_TYPE_SPOTLIGHT:
        {
            ApplySpotLight( nIdx );
        break;
        }

    }
}


void CLightManager::ApplyDirectional ( int nIdx )
{
    THOT_ASSERT(m_aLights[nIdx] != NULL && m_aLights[nIdx]->GetLightType() == E_LIGHT_TYPE_DIRECTIONAL );

    CDirectionalLightBase& light = (CDirectionalLightBase&)(*m_aLights[nIdx]);

    //CShader::GetCurrentShader()->SetLight( light );
}

void CLightManager::ApplyPositional ( int nIdx )
{
    THOT_ASSERT(m_aLights[nIdx] != NULL && m_aLights[nIdx]->GetLightType() == E_LIGHT_TYPE_POSITIONAL );

    CPositionalLightBase& light = (CPositionalLightBase&)(*m_aLights[nIdx]);

   // CShader::GetCurrentShader()->SetLight(light);
}

void CLightManager::ApplySpotLight ( int nIdx )
{
    THOT_ASSERT(m_aLights[nIdx] != NULL && m_aLights[nIdx]->GetLightType() == E_LIGHT_TYPE_SPOTLIGHT );

    CSpotLightBase& light = (CSpotLightBase&)(*m_aLights[nIdx]);


    //CShader::GetCurrentShader()->SetLight( light );
}



//        thVector<CLightBase*>            m_aLights;
