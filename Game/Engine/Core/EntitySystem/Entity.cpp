#include "Core_PCH.h"
#include "Entity.h"

#include "Core/EntitySystem/EntitySystem.h"
#include "Core/Components/ComponentBase.h"
#include "Core/Components/BindingComponent.h"

//--------------------------------------------------------------------------------
CEntity::CEntity()
    : m_entityID ( INVALID_ENTITY_ID)
{
}

//--------------------------------------------------------------------------------
CEntity::~CEntity()
{
    RemoveAllComponents();
}

//--------------------------------------------------------------------------------
void CEntity::RemoveAllComponents()
{
    CEntitySystem::GetInstance()->RemoveAllComponents( m_entityID );
}

//--------------------------------------------------------------------------------
Bool CEntity::IsValid ()const
{
    //THOT_ASSERT( m_entityID < CEntitySystem::GetInstance()->GetMaxEntityCount(), "THIS IS STILL AN INVALID ENTITY ID[%d]", m_entityID );
    return m_entityID != INVALID_ENTITY_ID;
}

//--------------------------------------------------------------------------------
IComponent* CEntity::GetComponent( TComponentID compID)
{
    return CEntitySystem::GetInstance()->GetComponent( m_entityID, compID );
}

//--------------------------------------------------------------------------------
const IComponent* CEntity::GetComponent( TComponentID compID )const
{
    return CEntitySystem::GetInstance()->GetComponent( m_entityID, compID );
}

//--------------------------------------------------------------------------------
Bool CEntity::InsertComponent( IComponent* component )
{
    Bool rez = CEntitySystem::GetInstance()->InsertComponent( m_entityID, component );
    if( rez )
    {
        component->m_entity = this;
        component->OnBindToEntity();
    }

    return rez;
}

//--------------------------------------------------------------------------------
Bool CEntity::RemoveComponent( IComponent* component )
{
    return CEntitySystem::GetInstance()->RemoveComponent( m_entityID, component );
}

//--------------------------------------------------------------------------------
Bool CEntity::RemoveComponent( TComponentID componentID)
{
    return CEntitySystem::GetInstance()->RemoveComponent( m_entityID, componentID);
}

//--------------------------------------------------------------------------
Bool CEntity::AttachTo( CEntityHandle& parent )
{
    CBindingComponent* parentBindingComponent = parent->GetComponent<CBindingComponent>();
    if( !parentBindingComponent )
    {
        return false;
    }

    CEntityHandle _thisHandle;
    _thisHandle = this;

    // add this entity to parent child list
    parentBindingComponent->AddChild( _thisHandle );

    return true;
}

//--------------------------------------------------------------------------
Bool CEntity::AttachChild( CEntityHandle& entity)
{
    CBindingComponent* bindingComponent = GetComponent<CBindingComponent>();
    if( !bindingComponent )
    {
        return false;
    }

    bindingComponent->AddChild( entity );

    return true;
}