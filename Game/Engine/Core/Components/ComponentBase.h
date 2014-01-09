#if !defined (__CORE_COMPONENT_BASE_H__)
#define __CORE_COMPONENT_BASE_H__

#include "Core/Components/ComponentTypes.h"
#include "Core/EntitySystem/EntityTypes.h"
#include "Core/System/SystemTypes.h"
#include "Core/EntitySystem/EntityHandle.h"

class CORE_API IComponent
{
    friend class CEntity;
    friend class CEntitySystem;

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
                IComponent( );
    virtual     ~IComponent( ) = 0;



//*********************************************
//            INTERFACE
//*********************************************
public:

    virtual void                    OnBindToEntity      (){}// the m_entity is allready set when this function is called
    inline TComponentID             GetID()const        { return m_id;}
    inline CEntityHandle&           GetEntity()         { return m_entity;}
    inline const CEntityHandle&     GetEntity()const    { return m_entity;}
    inline TSystemID                GetSystemsMask()    { return m_systemsMask;}

//*********************************************
//            MEMBERS
//*********************************************
protected:
    CEntityHandle       m_entity;
    TComponentID        m_id;
    TSystemID           m_systemsMask;
};


class CORE_API CComponentDescriptor
{
public:
    inline void OnAquireSystem( TSystemID systemID)
    {
        THOT_ASSERT( systemID != INVALID_SYSTEM_ID, "SYSTEM WITH INVALID ID CANNOT AQUIRE A COMPONENT");
        m_systemsMask |= systemID;
    }

    inline CComponentDescriptor()
    : m_componentID ( INVALID_COMPONENT_ID )
    , m_systemsMask ( 0 )
    {
    }

    inline void SetID( TComponentID id)
    {
        m_componentID = id;
    }

    inline TComponentID GetID()
    {
        return m_componentID;
    }

public:
    TComponentID        m_componentID;
    TSystemID           m_systemsMask;
};


template<class DERIVED_COMPONENT>
class  CComponetBase:public IComponent
{
public:
    typedef IComponent super;
    CComponetBase(  )
    {
        THOT_ASSERT( ms_componentDescriptor.GetID() != INVALID_COMPONENT_ID, "TRYING TO CREATE A COMPONENT THAT WAS NOT REGISTERED" );
        m_id =  ms_componentDescriptor.m_componentID;
        m_systemsMask = ms_componentDescriptor.m_systemsMask;
    }

    static TComponentID             GetStaticID()           { return ms_componentDescriptor.m_componentID;}
    static CComponentDescriptor&    GetStaticDescriptor()   { return ms_componentDescriptor;}
public:
    static CComponentDescriptor     ms_componentDescriptor;
};

template<class DERIVED_COMPONENT>
CComponentDescriptor CComponetBase<DERIVED_COMPONENT>::ms_componentDescriptor;


#endif //__CORE_COMPONENT_BASE_H__