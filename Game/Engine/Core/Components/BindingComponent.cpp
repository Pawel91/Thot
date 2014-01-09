#include "Core_PCH.h"
#include "BindingComponent.h"

#include "Core/EntitySystem/Entity.h"

//--------------------------------------------------------
CBindingComponent::CBindingComponent()
    : m_isDirty ( false )
    , m_localTM (i4x4)
    , m_worldTM (i4x4)
{
}

//--------------------------------------------------------
CBindingComponent::~CBindingComponent()
{
}

//--------------------------------------------------------
const m4x4& CBindingComponent::GetLocalTM()
{
    return m_localTM;
}

//--------------------------------------------------------
void CBindingComponent::SetDirty( Bool isDirty )
{
    m_isDirty = isDirty;
}

//--------------------------------------------------------
void CBindingComponent::SetLocalTM( const m4x4& tm )
{
    SetDirty();
    m_localTM = tm;
}

//--------------------------------------------------------
void CBindingComponent::AddChild( CEntityHandle& child )
{
    THOT_ASSERT( m_entity != child, "CANNOT BIND A ENTITY TO ITSELF");
    if( m_entity == child )
    {
        return;
    }

    m_children.PushBack( child );
    CBindingComponent* bindingComp = child->GetComponent<CBindingComponent>();
    if( bindingComp )
    {
        bindingComp->SetDirty();
        bindingComp->m_parent = m_entity;
    }
}

//--------------------------------------------------------
Bool CBindingComponent::IsOrphan()
{
    return !m_parent->IsValid();
}

//--------------------------------------------------------
const m4x4& CBindingComponent::GetWorldTM( Bool force)const
{
    if( ! force )
    {
        return m_worldTM;
    }

    if( m_parent && m_parent->IsValid() )
    {
        const CBindingComponent* parentBindingComp = m_parent->GetComponent<CBindingComponent>();
        m4x4 parentWorldTM = parentBindingComp->GetWorldTM( true );
        m_worldTM = m_localTM * parentWorldTM;
    }
    else
    {
        m_worldTM = m_localTM;
    }

    //SetDirty( false );
    return m_worldTM;
}

//--------------------------------------------------------
void CBindingComponent::UpdateChildrenMatrices()
{
    for( u64 i=0; i<m_children.Size(); i++)
    {
        CEntityHandle& handle = m_children[i];
        CBindingComponent* childBindingComp = handle->GetComponent<CBindingComponent>();
        THOT_ASSERT(childBindingComp!=NULL);

        const m4x4& childLocalTM = childBindingComp->GetLocalTM();
        childBindingComp->m_worldTM = ( childLocalTM * m_worldTM );
        childBindingComp->SetDirty( false );

        // update all hierarchy
        childBindingComp->UpdateChildrenMatrices();
    }
}