#if !defined(__CORE_ENTITY_POOL_H__)
#define __CORE_ENTITY_POOL_H__

#include "Kernel/DataStructures/Array/Vector.h"
#include "Kernel/DataStructures/Array/Vector.h"
#include "Core/EntitySystem/EntityTypes.h"
#include "Core/Components/ComponentTypes.h"
#include "Core/EntitySystem/Entity.h"

class CEntityPool
{
    friend class CEntitySystem;
    typedef thVector<u16>                    TEntityHandleContainer;
private:
    struct SEntityInfo
    {
        SEntityInfo()
            : m_refCount(0)
            , m_components (NULL)
        {
        }

        CEntity         m_entity;
        s16             m_refCount;
        IComponent**    m_components;
    };

    explicit CEntityPool( u16 maxEntityCount, u16 componentCount );
    ~CEntityPool();


    void            Init                ( );
    CEntity*        GetEntity           ( TEntityID id);
    CEntityHandle   GetNewEntity        ( );
    void            RecycleEntity       ( CEntityHandle& handle );
    IComponent*     GetComponent        ( TEntityID id, TComponentID compID);

    Bool            InsertComponent     ( TEntityID entID, IComponent* component );
    Bool            RemoveComponent     ( TEntityID entID, IComponent* component );
    Bool            RemoveComponent     ( TEntityID entID, TComponentID componentID);

    void            AddRef              ( CEntityHandle& handle );
    void            Release             ( CEntityHandle& handle );
    bool            ValidateEntityID    ( TEntityID id );
    s32             GetRefCount         ( TEntityID id)const;

private:
    void            DestroyEntity       ( TEntityID entityID );


protected:
    u16                     m_maxEntityCount;
    u16                     m_componentCount;
    TEntityHandleContainer  m_freeEntities;
    SEntityInfo*            m_entityContainer;     THOT_TODO("REFACTOR ENTITY CONTAINER")

};

#else
#   error THIS HEADER MUST BE INCLUDED ONLY BY ENTITY SYSTEM ONCE IN CPP FILE. THIS IS MUST BE A PRIVATE FILE
#endif //__CORE_ENTITY_POOL_H__