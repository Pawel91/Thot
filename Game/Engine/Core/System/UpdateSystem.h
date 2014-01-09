//  [11/10/2013 Radu]
#if !defined(__CORE_UPDATE_SYSTEM_H__)
#define __CORE_UPDATE_SYSTEM_H__

#include "Kernel/DataStructures/Array/Vector.h"
#include "Core/System/SystemBase.h"

THOT_DECLARE_TEMPLATE_API(CORE_TEMPLATE_API, thVector<CEntityHandle> );

class CORE_API CUpdateSystem: public CSystemBase<CUpdateSystem>
{

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
     CUpdateSystem();
    ~CUpdateSystem();


//*********************************************
//            INTERFACE
//*********************************************
public:
    virtual     void        OnInit() override;
    virtual     void        Execute( ) override;
    virtual     void        RegisterComponents() override;
    virtual     void        OnEntityComponentChange( const CEntityHandle& handle, IComponent* component, bool added ) override;

//*********************************************
//            MEMBERS
//*********************************************
protected:
    thVector<CEntityHandle>  m_updatableEntities;
};



#endif//__CORE_UPDATE_SYSTEM_H__
