#include "Core_PCH.h"
#include "LightComponent.h"

#include "Core/EntitySystem/Entity.h"
#include "Core/Components/BindingComponent.h"
#include "MathCore/MathUtils.h"

//--------------------------------------------------------------------
CLightComponent:: CLightComponent()
    : m_lightType   ( ELightType_Directional )
    , m_attenuation ( tVect3( 0.f, 1.f, 0.f ) )
    , m_fCutoff     ( 45.f )
    , m_fExponent   ( 0.f )
{
}

//--------------------------------------------------------------------
CLightComponent::~CLightComponent()
{
}

//--------------------------------------------------------------------
void CLightComponent::SetAmbient( const CColor& color )
{
    m_ambient = color;
}

//--------------------------------------------------------------------
void CLightComponent::SetDiffuse( const CColor& color )
{
    m_diffuse = color;
}

//--------------------------------------------------------------------
void CLightComponent::SetSpecular( const CColor& color )
{
    m_specular = color;
}

//--------------------------------------------------------------------
const CColor& CLightComponent::GetAmbient()const
{
    return m_ambient;
}

//--------------------------------------------------------------------
const CColor& CLightComponent::GetDiffuse()const
{
    return m_diffuse;
}

//--------------------------------------------------------------------
const CColor& CLightComponent::GetSpecular()const
{
    return m_specular;
}

//--------------------------------------------------------------------
void CLightComponent::SetAttenuation( const tVect3& attenuation )
{
    m_attenuation = attenuation;
}

//--------------------------------------------------------------------------------
const tVect3& CLightComponent::GetAttenuation()const
{
    return m_attenuation;
}

//--------------------------------------------------------------------------------
void CLightComponent::SetExponent( float exponent )
{
    m_fExponent = exponent;
}

//--------------------------------------------------------------------------------
void CLightComponent::SetCutoff( float cutoff )
{
    m_fCutoff = cutoff;
}

//--------------------------------------------------------------------------------
float CLightComponent::GetExponent()const
{
    return m_fExponent;
}

//--------------------------------------------------------------------------------
float CLightComponent::GetCutoff()const
{
    return m_fCutoff;
}

//--------------------------------------------------------------------------------
void CLightComponent::SetType( ELightType lightType )
{
    m_lightType = lightType;
}

//--------------------------------------------------------------------------------
ELightType CLightComponent::GetLightType()const
{
    return m_lightType;
}

//--------------------------------------------------------------------------------
void CLightComponent::SetDirectionToLight( const tVect3& dir )
{
    CBindingComponent* bindingComponent = m_entity->GetComponent<CBindingComponent>();
    if( !bindingComponent)
    {
        return;
    }
    
    m4x4 transformMatrix;
    MathUtils::GetMatFromZDir( dir, transformMatrix );
    bindingComponent->SetLocalTM( transformMatrix );
}

//--------------------------------------------------------------------------------