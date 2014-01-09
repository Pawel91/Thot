#include "Core_PCH.h"
#include "Core/EntitySystem/EntityPool.h"

#include "Kernel/Profiler/Profiler.h"
#include "Core/EntitySystem/Entity.h"
#include "Core/EntitySystem/EntityHandle.h"
#include "Core/Components/ComponentBase.h"

#define ENTITY_ID_ASSERT(__ID)  \
THOT_ASSERT( ValidateEntityID(__ID), "INVALID ENTITY ID[%d]", __ID )

#define ENTITY_COMPONENT_ASSERT(__compID) \
THOT_ASSERT( __compID < m_componentCount, "INVALID ENTITY COMPONENT ID[%d]", __compID )

//----------------------------------------------------------------------
IComponent* CEntityPool::GetComponent( TEntityID id, TComponentID compID)
{
    if( id == INVALID_ENTITY_ID )
    {
        return NULL;
    }
    THOT_ASSERT( id < m_maxEntityCount, "TRYING TO ACCES AN INVALID ENTITY ID:[%d]", id);
    THOT_ASSERT( compID < m_componentCount,"TRYING TO ACCES AN INVALID COMPONENT ID:[%d]", compID);

    if( !m_entityContainer || !m_entityContainer[id].m_components)
    {
        return NULL;
    }

    return m_entityContainer[id].m_components[compID];
}

//----------------------------------------------------------------------
void CEntityPool::AddRef( CEntityHandle& handle )
{
    DECLARE_PROFILE_SCOPED("CEntityPool::AddRef");
    TEntityID id = INVALID_ENTITY_ID;
    if( (id =  handle.m_entityID) == INVALID_ENTITY_ID)
    {
        return;
    }

    m_entityContainer[id].m_refCount++;
}

//----------------------------------------------------------------------
void CEntityPool::Release( CEntityHandle& handle )
{
    DECLARE_PROFILE_SCOPED("CEntityPool::Release");

    TEntityID id = INVALID_ENTITY_ID;
    if( (id =  handle.m_entityID) == INVALID_ENTITY_ID)
    {
        return;
    }

    THOT_ASSERT(m_entityContainer);

    if( m_entityContainer &&  (-- m_entityContainer[id].m_refCount) <= 0 )
    {
        // destroy the entity
        m_entityContainer[id].m_entity.~CEntity();

        // reinit to be ready for use
        new( &m_entityContainer[id].m_entity ) CEntity();
        m_entityContainer[id].m_entity.m_entityID = id;

        RecycleEntity( handle );
    }
}

//----------------------------------------------------------------------
void CEntityPool::RecycleEntity( CEntityHandle handle )
{
    if( handle.m_entityID == INVALID_ENTITY_ID )
    {
        return;
    }

    m_freeEntities.PushBack( handle.m_entityID );
}

//----------------------------------------------------------------------
CEntityPool::CEntityPool( u16 maxEntityCount, u16 componentCount )
    : m_maxEntityCount  ( maxEntityCount )
    , m_componentCount  ( componentCount )
{
}

//----------------------------------------------------------------------
void CEntityPool::Init( )
{
    if(!m_entityContainer)
    {
        return;
    }

    m_entityContainer = THOT_NEW_ARR SEntityInfo[m_maxEntityCount];
    for( u16 i=0; i<m_maxEntityCount; i++ )
    {
        m_entityContainer[i].m_entity.m_entityID = TEntityID(i);    // init entity ID;

        m_entityContainer[i].m_components = THOT_NEW_ARR IComponent*[m_componentCount];
        for( u16 compIdx=0; compIdx<m_componentCount; compIdx++ )
        {
            // init entity components with NULL;
            m_entityContainer[i].m_components[compIdx] = NULL;
        }

        m_freeEntities.PushBack( i );
    }
    
}

//----------------------------------------------------------------------
CEntityPool::~CEntityPool()
{
    if(!m_entityContainer)
    {
        return;
    }

    //destroy all entities
    for( TEntityID entID=0; entID<m_maxEntityCount; entID++)
    {
        m_entityContainer[entID].m_entity.~CEntity();
        THOT_DELETE_ARR( m_entityContainer[entID].m_components );
        m_entityContainer[entID].m_components = NULL;
    }

    THOT_DELETE_ARR( m_entityContainer );
    m_entityContainer = NULL;
}

//--------------------------------------------------------------------------------
CEntity* CEntityPool::GetEntity( TEntityID id)
{
    return &m_entityContainer[id].m_entity;
}

//----------------------------------------------------------------------
CEntityHandle CEntityPool::GetNewEntity( )
{
    TEntityID id = INVALID_ENTITY_ID;
    if( m_freeEntities.Size() )
    {
        id = m_freeEntities[ m_freeEntities.Size() - 1 ];
        m_freeEntities.Erase( m_freeEntities.Begin() + ThNumericCast<TEntityHandleContainer::TSize>( id ) );
    }
    else
    {
        THOT_ASSERT(false, "CANNOT CREATE MORE ENTITIES");
    }

    CEntityHandle handle(id);
    AddRef( handle );

    return handle;
}

//----------------------------------------------------------------------
bool CEntityPool::ValidateEntityID( TEntityID id)
{
    if( id >= m_maxEntityCount || id == INVALID_ENTITY_ID)
    {
        return false;
    }

    return true;
}

//----------------------------------------------------------------------
Bool CEntityPool::InsertComponent( TEntityID entID, IComponent* component )
{
    THOT_ASSERT( component, "CANNOT INSERT A NULL COMPONENT INTO AN ENTITY");
    ENTITY_ID_ASSERT( entID );
    TComponentID compID = component->GetID();
    ENTITY_COMPONENT_ASSERT(compID);
    THOT_ASSERT(m_entityContainer[entID].m_components[compID] == NULL, "A COMPONENT WITH SAME ID[%d] IS ALLREADY IN THIS ENTITY[%d]", compID, entID );

    if( m_entityContainer[entID].m_components[compID] )
    {
        // a component with same id is allready there
        return false;
    }
    else
    {
        m_entityContainer[entID].m_components[compID] = component;
    }

    return true;
}

//----------------------------------------------------------------------
Bool CEntityPool::RemoveComponent(TEntityID entID, IComponent* component )
{
    return RemoveComponent( entID, component->GetID() );
}

//----------------------------------------------------------------------
Bool CEntityPool::RemoveComponent(TEntityID entID, TComponentID componentID)
{    
    ENTITY_ID_ASSERT( entID );
    ENTITY_COMPONENT_ASSERT(componentID);
    IComponent*& component = m_entityContainer[entID].m_components[componentID];
    if( component == NULL )
    {
        // component with this id is not on this entity
        return false;
    }

    THOT_TODO("REVIEW THE DELETE OF COMPONENT HERE");
    THOT_SAFE_DELETE( component );

    return true;
}

//----------------------------------------------------------------------
