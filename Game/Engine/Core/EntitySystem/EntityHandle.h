#if !defined(__ENTITY_HANDLE_H__)
#define __ENTITY_HANDLE_H__

#include "Core/EntitySystem/EntityTypes.h"
class CEntity;

class CORE_API CEntityHandle
{
    friend class CEntityPool;
    friend class CEntitySystem;

private:
    explicit CEntityHandle( TEntityID entID)
        : m_entityID   (entID)
    {
    }
public:
    inline CEntityHandle()
        : m_entityID( INVALID_ENTITY_ID )
    {}
    CEntityHandle( const CEntityHandle& );
    ~CEntityHandle();
    const CEntityHandle& operator = ( CEntity* entity );
    const CEntityHandle& operator = ( const CEntityHandle& other );
    CEntity* operator->();
    const CEntity* operator->()const;

    void Release();

    inline bool operator == ( CEntityHandle& other)const
    {
        return m_entityID == other.m_entityID;
    }

    inline bool operator != ( CEntityHandle& other)const
    {
        return m_entityID != other.m_entityID;
    }

    inline operator bool()const
    {
        return m_entityID != INVALID_ENTITY_ID;
    }

private:
    void            CopyFromOther( const CEntityHandle& other );

private:
    TEntityID       m_entityID;
};

THOT_COMPILE_ASSERT2( sizeof(CEntityHandle) == sizeof(TEntityID), "sizeof(CEntityHandle) MUST BE MINIMAL" );


#endif//__ENTITY_HANDLE_H__