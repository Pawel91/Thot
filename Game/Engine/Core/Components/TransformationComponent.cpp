#include "Core_PCH.h"
#include "TransformationComponent.h"


//------------------------------------------------------------------------
CTransformationComponent::CTransformationComponent()
    : m_worldTM(i4x4)
    , m_localTM(i4x4)
{
}

//------------------------------------------------------------------------
CTransformationComponent::~CTransformationComponent()
{
}

//------------------------------------------------------------------------
void CTransformationComponent::SetLocalTM( const m4x4& localTM )
{
    m_localTM = localTM;
}

//------------------------------------------------------------------------
void CTransformationComponent::UpdateWorldTM( const m4x4& parentTM )
{
    m_worldTM = m_localTM * parentTM;
}

//------------------------------------------------------------------------
const m4x4& CTransformationComponent::GetLocalTM()const
{
    return m_localTM;
}

//------------------------------------------------------------------------
const m4x4& CTransformationComponent::GetWorldTM()const
{
    return m_worldTM;
}