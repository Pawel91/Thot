#if !defined(__CORE_SYSTEM_BASE_H__)
#define __CORE_SYSTEM_BASE_H__

#include "Kernel/DataStructures/Array/Vector.h"
#include "Core/System/SystemTypes.h"
#include "Core/EntitySystem/EntityHandle.h"
#include "Core/Components/ComponentTypes.h"

THOT_DECLARE_TEMPLATE_API( CORE_TEMPLATE_API, thVector<CEntityHandle>);
THOT_DECLARE_TEMPLATE_API( CORE_TEMPLATE_API, thVector<TComponentID>);

class CORE_API ISystem
{

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
     ISystem()
         : m_systemID (INVALID_SYSTEM_ID)
     {
     }
     virtual ~ISystem(){};


//*********************************************
//            INTERFACE
//*********************************************
public:

    virtual     void        OnInit() = 0;
    virtual     void        Execute( ) = 0;             // execute this system
    virtual     void        RegisterComponents() = 0;   // register the components that this system will work with

    // a system must register a component to be notified when it was removed or added to an entity;
    virtual     void        OnEntityComponentChange( const CEntityHandle& handle, IComponent* component, bool Added ) = 0; 

    template<class COMPONENT_TYPE>
    void RegisterComponent();

//*********************************************
//            MEMBERS
//*********************************************
protected:
    TSystemID                   m_systemID;
};

//-------------------------------------------------------------------
template<class COMPONENT_TYPE>
void ISystem::RegisterComponent()
{
    THOT_ASSERT( m_systemID != INVALID_SYSTEM_ID, "CANNOT REGISTER COMPONENT FOR AN INVALID SYSTEM");
    COMPONENT_TYPE::GetStaticDescriptor().OnAquireSystem( m_systemID );
}

//-------------------------------------------------------------------
class CORE_API CSystemDescriptor
{
public:
    CSystemDescriptor()
        : m_systemID(INVALID_SYSTEM_ID)
    {
    }
    TSystemID       m_systemID;
};

//--------------------------------------------------------------------------------
template<class DERIVED_SYSTEM>
class  CSystemBase:public ISystem
{
public:
    CSystemBase()
        :ISystem()
    {
        THOT_ASSERT( ms_systemDescriptor.m_systemID != INVALID_SYSTEM_ID, "CREATING A SYSTEM THAT WAS NOT REGISTERED TO ENTITY SYSTEM");
        m_systemID = ms_systemDescriptor.m_systemID;
    }

    static CSystemDescriptor&   GetStaticDescriptor();
    static TSystemID            GetStaticID();
    static ISystem*             CreateSystem();

private:
    static CSystemDescriptor    ms_systemDescriptor;
};

//-------------------------------------------------------------------
template<class DERIVED_SYSTEM>
CSystemDescriptor CSystemBase<DERIVED_SYSTEM>::ms_systemDescriptor;

//-------------------------------------------------------------------
template<class DERIVED_SYSTEM>
CSystemDescriptor& CSystemBase<DERIVED_SYSTEM>::GetStaticDescriptor()
{
    return ms_systemDescriptor;
}

//-------------------------------------------------------------------
template<class DERIVED_SYSTEM>
TSystemID CSystemBase<DERIVED_SYSTEM>::GetStaticID()
{
    return ms_systemDescriptor.m_systemID;    
}

//-------------------------------------------------------------------
template<class DERIVED_SYSTEM>
ISystem* CSystemBase<DERIVED_SYSTEM>::CreateSystem()
{
    return THOT_NEW DERIVED_SYSTEM;
}

//-------------------------------------------------------------------

#endif //__CORE_SYSTEM_BASE_H__