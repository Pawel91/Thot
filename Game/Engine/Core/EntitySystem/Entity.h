#if !defined(__ENTITY_H__)
#define __ENTITY_H__

#include "Core/EntitySystem/EntityTypes.h"
#include "Core/Components/ComponentTypes.h"


#if defined(THOT_ENABLE_DEBUG)
#   include "Kernel/DataStructures/CString.h"
#endif

class IComponent;

class CORE_API CEntity
{
    friend class CEntityPool;
public:
    CEntity();
    ~CEntity();

    Bool                IsValid ()const;

    void                RemoveAllComponents();
    Bool                InsertComponent( IComponent* component );
    Bool                RemoveComponent( IComponent* component );
    Bool                RemoveComponent( TComponentID componentID);

    TEntityID           GetID(){ return m_entityID;}
    Bool                AttachTo( CEntityHandle& parent );
    Bool                AttachChild( CEntityHandle& child);
    IComponent*         GetComponent( TComponentID compID );
    const IComponent*   GetComponent( TComponentID compID )const;

#if defined(THOT_ENABLE_DEBUG)
    void                SetDebugName(char* name){ m_debugName = name; }
    const CString&      GetDebugName(){ return m_debugName;}
#else
    inline void                SetDebugName(char* name){}
    inline const CString&      GetDebugName(){ return m_debugName;}

#endif

    template<typename COMPONENT_TYPE>
    COMPONENT_TYPE*     GetComponent();

    template<typename COMPONENT_TYPE>
    const COMPONENT_TYPE*     GetComponent()const;

private:
#if defined(THOT_ENABLE_DEBUG)
    CString         m_debugName;
#endif 
    TEntityID       m_entityID;
};

//------------------------------------------------------
template<typename COMPONENT_TYPE>
COMPONENT_TYPE* CEntity::GetComponent()
{
    return (COMPONENT_TYPE*)GetComponent( COMPONENT_TYPE::GetStaticID() );
}

//------------------------------------------------------
template<typename COMPONENT_TYPE>
const COMPONENT_TYPE* CEntity::GetComponent()const
{
    return (COMPONENT_TYPE*)GetComponent( COMPONENT_TYPE::GetStaticID() );
}

#endif //__ENTITY_H__