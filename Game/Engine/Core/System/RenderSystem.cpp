#include "Core_PCH.h"
#include "RenderSystem.h"

#include "Core/Components/RenderableComponent.h"
#include "Core/Components/BindingComponent.h"
#include "Core/Components/LightComponent.h"
#include "Core/EntitySystem/Entity.h"
#include "Render/ShaderFramework/ShaderParameterProvider.h"
#include "Render/ShaderFramework/ShaderParameter.h"
#include "Render/ShaderFramework/ShaderManager.h"
#include "Render/ShaderFramework/Shader.h"

#include <map>

//--------------------------------------------------------------------------------
struct SRenderableContainter
{
    typedef ShaderID                                        TFrom;
    typedef const CRenderableComponent*                     TTo;
    typedef std::multimap< TFrom, TTo >                     TShaderRenderableMap;
    typedef TShaderRenderableMap::iterator                  TIterator;
    typedef TShaderRenderableMap::const_iterator            TConstIterator;
    typedef std::pair< TFrom, TTo>                          TPair;

    TShaderRenderableMap          m_shaderMap;

    void Insert( const CRenderableComponent* renderableComponent );
};

//--------------------------------------------------------------------------------
void SRenderableContainter::Insert( const CRenderableComponent* renderableComponent )
{
    THOT_ASSERT( renderableComponent, "CANNOT INSERT A NULL RENDERABLE COMPONENT" );
    THOT_ASSERT( renderableComponent->GetShaderID() != INVALID_SHADERID, "RENDERABLE COMPONENT HAS AN INVALID SHADERID");
#if defined(THOT_ENABLE_DEBUG)
    const CEntity* entity = renderableComponent->GetEntity().operator ->();
#endif
    ShaderID shaderID = renderableComponent->GetShaderID();
    m_shaderMap.insert( TPair( shaderID, renderableComponent ));
}

//--------------------------------------------------------------------------------
class CLightDirectionalParameterProvider: public CShaderParameterProviderBase<CLightDirectionalParameterProvider>
{
public:
    CLightDirectionalParameterProvider()
    {

    }

    void Build( CLightComponent& lightComponent )
    {
        m_ambientColor = lightComponent.GetAmbient();
        m_diffuseColor = lightComponent.GetDiffuse();
        m_specularColor = lightComponent.GetSpecular();

        m_directionToLight = zAxis;

        CBindingComponent* bindingComponent = NULL;
        if( !( bindingComponent = lightComponent.GetEntity()->GetComponent<CBindingComponent>() ) )
        {
            // binding component not found
            return;
        }

        m4x4 lightToWorldTM = bindingComponent->GetWorldTM( true );
        m_directionToLight =  - AXEZ( lightToWorldTM);
    }

    static void CreateParameterMap();
    CShaderParameter<CColor>        m_ambientColor;
    CShaderParameter<CColor>        m_diffuseColor;
    CShaderParameter<CColor>        m_specularColor;
    CShaderParameter<tVect3>        m_directionToLight;
};


//--------------------------------------------------------------------------------
void CLightDirectionalParameterProvider::CreateParameterMap()
{
    CLightDirectionalParameterProvider& parameterProvider = *((CLightDirectionalParameterProvider*)(0));
    SetProviderName( "CLightDirectionalParameterProvider" );

    AddParameter(parameterProvider.m_ambientColor,      "uDirLight.m_specular" );
    AddParameter(parameterProvider.m_diffuseColor,      "uDirLight.m_ambient" );
    AddParameter(parameterProvider.m_specularColor,     "uDirLight.m_diffuse" );
    AddParameter(parameterProvider.m_directionToLight,  "uDirLight.m_direction" );
}

//--------------------------------------------------------------------------------
class CMaterialParameterProvider: public CShaderParameterProviderBase<CMaterialParameterProvider>
{
public:
    CMaterialParameterProvider()
    {
        m_diffuseMap->DebugLoad("Data\\textures\\moonDiffuse.jpg");
        m_diffuseMap->SetTextureUnit(1);
    }

    static void CreateParameterMap();

    void Build ( const CMaterial& material )
    {
        m_diffuse = material.m_diffuse;
        m_ambient = material.m_ambient;
        m_specular = material.m_specular;
        m_shininess = material.m_shininess;
        m_opacity = material.m_opacity;
    }

    CShaderParameter<CTexture>      m_diffuseMap;
    CShaderParameter<CColor>        m_diffuse;
    CShaderParameter<CColor>        m_ambient;
    CShaderParameter<CColor>        m_specular;
    CShaderParameter<float>         m_shininess;
    CShaderParameter<float>         m_opacity;
};

//--------------------------------------------------------------------------------
void CMaterialParameterProvider::CreateParameterMap()
{
    CMaterialParameterProvider& parameterProvider = *((CMaterialParameterProvider*)(0));
    SetProviderName( "CMaterialParameterProvider" );

    AddParameter(parameterProvider.m_diffuseMap,    "myTexture" );
    AddParameter(parameterProvider.m_diffuse,       "uMaterial.m_diffuse" );
    AddParameter(parameterProvider.m_ambient,       "uMaterial.m_ambient" );
    AddParameter(parameterProvider.m_specular,      "uMaterial.m_specular" );
    AddParameter(parameterProvider.m_shininess,     "uMaterial.m_shininess" );
    AddParameter(parameterProvider.m_opacity,       "uMaterial.m_opacity" );                      
}

//--------------------------------------------------------------------------------
class CViewportParameterProvider:public CShaderParameterProviderBase<CViewportParameterProvider>
{
public:
    CViewportParameterProvider()
    {
        m_modelMatrix = i4x4;
        m_modelViewProjection = i4x4;
    }

public:
    static void CreateParameterMap();
    CShaderParameter<m4x4>  m_modelMatrix;
    CShaderParameter<m4x4>  m_modelViewProjection;
};

//--------------------------------------------------------------------------------
void CViewportParameterProvider::CreateParameterMap()
{
    CViewportParameterProvider& parameterProvider = *((CViewportParameterProvider*)(0));

    SetProviderName( "CModelViewProjection" );

    AddParameter(  parameterProvider.m_modelViewProjection, "uMVP" );
    AddParameter(  parameterProvider.m_modelMatrix, "uModelMatrix" );
}


//---------------------------------------------------------------------------
CRenderSystem::CRenderSystem()
    : m_viewportParameterProvider       ( NULL )
    , m_renderableContainer             ( NULL )
{
    m_viewportParameterProvider = THOT_NEW CViewportParameterProvider;
    m_renderableContainer = THOT_NEW SRenderableContainter;
}

//---------------------------------------------------------------------------
CRenderSystem::~CRenderSystem()
{
    if( m_viewportParameterProvider )
    {
        THOT_SAFE_DELETE( m_viewportParameterProvider);
    }

    if( m_renderableContainer )
    {
        THOT_SAFE_DELETE( m_renderableContainer );
    }
}

//---------------------------------------------------------------------------
void CRenderSystem::OnInit()
{

}

//---------------------------------------------------------------------------
void GetRotation ( m3x3& out, const tVect3& m_vRot )
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


//---------------------------------------------------------------------------
void CRenderSystem::Execute()
{
    RENDER_GUARD_BLOCK

    CRenderCamera* renderCamera = CRender::GetInstance()->GetCamera();
    m4x4 viewProjection = i4x4;
    renderCamera->GetWorldToClipMatrix( viewProjection );

    SRenderableContainter::TIterator shaderIDIterator, renderableIterator;

    for (   shaderIDIterator = m_renderableContainer->m_shaderMap.begin();
            shaderIDIterator != m_renderableContainer->m_shaderMap.end();
            shaderIDIterator = renderableIterator)
    {
        ShaderID shaderID = (*shaderIDIterator).first;
        std::pair<SRenderableContainter::TIterator, SRenderableContainter::TIterator> keyRange = m_renderableContainer->m_shaderMap.equal_range(shaderID);
        CShaderManager::GetInstance()->BindShader( shaderID );

        for (renderableIterator = keyRange.first;  renderableIterator != keyRange.second;  ++renderableIterator)
        {
            const CRenderableComponent* renderableComponent = (*renderableIterator).second;
            const CEntityHandle& entityHandle = renderableComponent->GetEntity();
            const CEntity* entity = entityHandle.operator ->();
            const CBindingComponent* bindingComponent = entityHandle->GetComponent<CBindingComponent>();
            const CShader* shaderHandle = renderableComponent->GetShader();

            {//TEMP BLOCK TO TEST SOME FUNCTIONALITY
                // setup global parameter providers
                m4x4 modelMatrix = bindingComponent? bindingComponent->GetWorldTM(true) : i4x4;
                // setup viewport shader parameter providers
                m_viewportParameterProvider->m_modelMatrix = modelMatrix;
                m_viewportParameterProvider->m_modelViewProjection = modelMatrix * viewProjection;
                
                shaderHandle->SetupParameterProvider( *m_viewportParameterProvider );
                if( m_lightEntities.Size() )
                {
                    CEntityHandle& handle = m_lightEntities[0];
                    CLightComponent* lightComponent = handle->GetComponent<CLightComponent>();
                    THOT_ASSERT( lightComponent );
                    CLightDirectionalParameterProvider lightParameterProvider;
                    lightParameterProvider.Build( *lightComponent);
                    shaderHandle->SetupParameterProvider( lightParameterProvider );
                }
            }

            // make the draw calls for the meshes
            for( u64 i=0; i<renderableComponent->m_meshes.Size(); i++ )
            {
                IMesh* mesh = renderableComponent->m_meshes[i];

                static CMaterialParameterProvider materialParameterProvider; // TEMP TO BE REMOVED
                static bool init = false;
                if(! init)
                {
                    materialParameterProvider.Build( mesh->GetMaterial() );
                    materialParameterProvider.m_ambient = CColor( 0.2f, 0.2f, 0.2f, 1.f );
                    init = true;
                }

                shaderHandle->SetupParameterProvider( materialParameterProvider );
                mesh->OnDraw();
            }

        }
    }
}

//---------------------------------------------------------------------------
void CRenderSystem::RegisterComponents()
{
    RegisterComponent<CRenderableComponent>();
    RegisterComponent<CLightComponent>();

}

//---------------------------------------------------------------------------
void CRenderSystem::OnEntityComponentChange( const CEntityHandle& handle, IComponent* component, bool added )
{
    if( added )
    {
        const CRenderableComponent* renderableComponent = handle->GetComponent<CRenderableComponent>();
        const CLightComponent* lightComponent = handle->GetComponent<CLightComponent>();

        if( renderableComponent )
        {
            m_renderableContainer->Insert( renderableComponent );
        }

        if( lightComponent )
        {
            m_lightEntities.PushBack( handle );
        }

    }
    else
    {
        THOT_TODO("REMOVE THE ENTITY FROM ENTITIES VECTOR");
    }
}