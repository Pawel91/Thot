#if !defined(__ENTITY_SYSTEM_H__)
#define __ENTITY_SYSTEM_H__

#include "Kernel/Intrinsics.h"
#include "Kernel/Singleton.h"
#include "Core/EntitySystem/EntityTypes.h"
#include "Core/EntitySystem/EntityHandle.h"
#include "Core/EntitySystem/EntityPool.h"
#include "Core/Components/ComponentTypes.h"
#include "Core/System/SystemTypes.h"

THOT_DECLARE_TEMPLATE_API( CORE_TEMPLATE_API,  thVector<ISystem*> );


THOT_TODO("REVIEW ALL friend class IN THE ECS");
class CORE_API CEntitySystem: public CSingleton<CEntitySystem>
{
    template<class T> friend class CSingleton;
    friend class CEntityHandle;
    friend class CEntity;
private:
    CEntitySystem();
public:

    ~CEntitySystem();

            bool    OnInit      ( u16 maxEntityCount );

            CEntityHandle       CreateNewEntity( );
            u16                 GetMaxEntityCount();
            u16                 GetComponentCount();
            u16                 GetSystemCount();

    template<class COMPONENT_TYPE>
    void                RegisterComponent(); // must be called before rigster systems

    template<class SYSTEM_TYPE>
    SYSTEM_TYPE*        GetSystem();

    template<class SYSTEM_TYPE>
    void                RegisterSystem();

    THOT_TODO("WRAP THIS PRIVATE FUNCTIONS INTO A CLASS AND REMOVE THE FRIEND CLASSES FROM CEntitySystem")
private:
    void                AddRef( CEntityHandle& handle );
    void                Release( CEntityHandle& handle );
    IComponent*         GetComponent( TEntityID id, TComponentID);
    CEntity*            GetEntity( TEntityID id );
    
    Bool                InsertComponent( TEntityID entID, IComponent* component );
    Bool                RemoveComponent( TEntityID entID, IComponent* component );
    Bool                RemoveComponent( TEntityID entID, TComponentID componentID );
    void                RemoveAllComponents( TEntityID entID );
    void                NotifySystemsComponentChange(TEntityID entID, IComponent* component, bool added);
private:
    CEntityPool*        m_entityPool;
    thVector<ISystem*>  m_systems;
    u16                 m_registeredComponents;
    u16                 m_registeredSystems;
    u16                 m_maxEntityCount;
};

//-------------------------------------------------------------------
template<class COMPONENT_TYPE>
inline void CEntitySystem::RegisterComponent()
{
    THOT_ASSERT( COMPONENT_TYPE::GetStaticDescriptor().GetID() == INVALID_COMPONENT_ID, "TRYING TO REGISTER A COMPONENT THAT DOES NOT HAVE AN INVALID COMPONENT ID. THIS COMPONENT PROBABLY WAS ALLREADY REGISTERED");
    COMPONENT_TYPE::GetStaticDescriptor().SetID( TComponentID(m_registeredComponents) );
    m_registeredComponents++;
}

//-------------------------------------------------------------------
template<class SYSTEM_TYPE>
inline SYSTEM_TYPE* CEntitySystem::GetSystem()
{
    THOT_ASSERT( SYSTEM_TYPE::GetStaticDescriptor().m_systemID != INVALID_SYSTEM_ID, "TRYING TO GET AN UNREGISTERED SYSTEM");
    unsigned long msb = 0;
    Bool rez = ThotBitScanReverse(&msb, SYSTEM_TYPE::GetStaticDescriptor().m_systemID );
    THOT_ASSERT(rez != 0, "THIS IS ANOTHER INVALID SYSTEM ID");
    return (SYSTEM_TYPE*) m_systems[msb];
}

//-------------------------------------------------------------------
template<class SYSTEM_TYPE>
inline void CEntitySystem::RegisterSystem()
{
    THOT_ASSERT( SYSTEM_TYPE::GetStaticDescriptor().m_systemID == INVALID_SYSTEM_ID, "SYSTEM IS ALLREADY REGISTERED");
    SYSTEM_TYPE::GetStaticDescriptor().m_systemID = 1<<m_registeredSystems;
    m_registeredSystems ++;
    ISystem* system = SYSTEM_TYPE::CreateSystem();
    system->OnInit();
    system->RegisterComponents();
    m_systems.PushBack( system );
}

//-------------------------------------------------------------------

#endif //__ENTITY_SYSTEM_H__