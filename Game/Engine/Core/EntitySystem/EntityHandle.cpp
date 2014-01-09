#include "Core_PCH.h"
#include "EntityHandle.h"

#include "Core/EntitySystem/EntitySystem.h"

//---------------------------------------------------
void CEntityHandle::CopyFromOther( const CEntityHandle& other )
{
    if( m_entityID == other.m_entityID )
    {
        return;
    }
    CEntitySystem::GetInstance()->Release( *this );
    m_entityID = other.m_entityID;
    CEntitySystem::GetInstance()->AddRef( *this );
}
//---------------------------------------------------
CEntityHandle::CEntityHandle( const CEntityHandle& other )
    : m_entityID (INVALID_ENTITY_ID)
{
    CopyFromOther( other );
}

//---------------------------------------------------
CEntityHandle::~CEntityHandle()
{
    Release();
}

//--------------------------------------------------------------------------------
void CEntityHandle::Release()
{
    CEntitySystem::GetInstance()->Release( *this );
}

//---------------------------------------------------
const CEntityHandle& CEntityHandle::operator = ( const CEntityHandle& other )
{
    CopyFromOther( other );

    return *this;
}

//---------------------------------------------------
CEntity* CEntityHandle::operator->()
{
    return CEntitySystem::GetInstance()->GetEntity( m_entityID );
}

//---------------------------------------------------
const CEntity* CEntityHandle::operator->()const
{
    return CEntitySystem::GetInstance()->GetEntity( m_entityID );
}

//---------------------------------------------------
const CEntityHandle& CEntityHandle::operator = ( CEntity* entity )
{
    CEntitySystem::GetInstance()->Release( *this );
    m_entityID =  entity->GetID();
    CEntitySystem::GetInstance()->AddRef( *this);
    return *this;
}