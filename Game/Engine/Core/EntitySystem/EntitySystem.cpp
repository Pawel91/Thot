#include "Core_PCH.h"
#include "EntitySystem.h"

#include "Kernel/Intrinsics.h"
#include "Core/Components/ComponentBase.h"
#include "Core/System/SystemBase.h"


//------------------------------------------------------------
CEntitySystem::CEntitySystem()
    : m_registeredComponents        ( 0 )
    , m_maxEntityCount              ( 0 )
    , m_registeredSystems           ( 0 )
    , m_entityPool                  ( NULL )

{
}

//------------------------------------------------------------
bool CEntitySystem::OnInit( u16 maxEntityCount )
{
    m_maxEntityCount = maxEntityCount;
    m_entityPool = THOT_NEW CEntityPool( maxEntityCount, m_registeredComponents );
    m_entityPool->Init();
    return true;
}

//------------------------------------------------------------
CEntitySystem::~CEntitySystem()
{
    for( thVector<ISystem*>::Iterator it = m_systems.Begin(); it != m_systems.End(); ++it )
    {
        ISystem* system = *it;
        if( system )
        {
            THOT_DELETE( system );
        }
    }

    if( m_entityPool )
    {
        THOT_SAFE_DELETE(m_entityPool);
    }


}

//------------------------------------------------------------
CEntityHandle CEntitySystem::CreateNewEntity()
{
    return m_entityPool->GetNewEntity();
}

//------------------------------------------------------------
void CEntitySystem::AddRef( CEntityHandle& handle )
{
    m_entityPool->AddRef( handle );
}

//--------------------------------------------------------------------------------
s32 CEntitySystem::GetRefCount( TEntityID id)const
{
    if( id == INVALID_ENTITY_ID )
    {
        return 0;
    }

    return m_entityPool->GetRefCount(id);
}

//------------------------------------------------------------
void CEntitySystem::Release( CEntityHandle& handle )
{
    m_entityPool->Release( handle );
}

//------------------------------------------------------------
IComponent* CEntitySystem::GetComponent( TEntityID id, TComponentID compID)
{
    return m_entityPool->GetComponent( id, compID );   
}

//------------------------------------------------------------
u16  CEntitySystem::GetMaxEntityCount()
{
    return m_maxEntityCount;
}

//------------------------------------------------------------
u16  CEntitySystem::GetComponentCount()
{
    return m_registeredComponents;
}

//------------------------------------------------------------
u16 CEntitySystem::GetSystemCount()
{
    return m_registeredSystems;
}

//------------------------------------------------------------
void CEntitySystem::NotifySystemsComponentChange( TEntityID entID, IComponent* component, bool added)
{
    THOT_ASSERT(entID != INVALID_ENTITY_ID );
    CEntity* entity = m_entityPool->GetEntity( entID );
    component->m_entity = entity;

    CEntityHandle handle( entID);
    AddRef( handle );

    // notify the systems that this entity was chaged
    u32 systemsMask = component->GetSystemsMask();

    unsigned long mostSegnificanBit = 0;
    // parse all bits from systemsID
    while( ThotBitScanReverse( &mostSegnificanBit, systemsMask ) )
    {
        m_systems[mostSegnificanBit]->OnEntityComponentChange( handle, component, added );

        // remove the most segnificant bit from systems mask
        systemsMask &= ~ (1<<mostSegnificanBit);
    }
}

//------------------------------------------------------------
Bool CEntitySystem::InsertComponent( TEntityID entID, IComponent* component )
{
    if( !m_entityPool->InsertComponent( entID, component) )
    {
        return false;
    }

    NotifySystemsComponentChange( entID, component, true);

    return true;
}
//------------------------------------------------------------
Bool CEntitySystem::RemoveComponent( TEntityID entID, IComponent* component )
{
    if( ! m_entityPool->RemoveComponent( entID, component))
    {
        return false;
    }

    NotifySystemsComponentChange( entID, component, false );

    return true;
}

//------------------------------------------------------------
Bool CEntitySystem::RemoveComponent( TEntityID entID, TComponentID componentID)
{
    if( !m_entityPool->RemoveComponent( entID, componentID) )
    {
        return false;
    }

    IComponent* comp = m_entityPool->GetComponent( entID, componentID );
    if(comp)
    {
        NotifySystemsComponentChange( entID, comp, false );
    }

    return true;
}

//--------------------------------------------------------------------------------
void CEntitySystem::RemoveAllComponents( TEntityID entID )
{
    if(entID == INVALID_ENTITY_ID)
    {
        return;
    }

    for( u16 i=0; i <GetComponentCount(); i++ )
    {
        RemoveComponent( entID, TComponentID(i) );
    }
}

//------------------------------------------------------------
CEntity* CEntitySystem::GetEntity( TEntityID id )
{
    return m_entityPool->GetEntity( id );
}

