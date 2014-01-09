#if !defined(__CORE_COMPONENT_CONTAINER_H__)
#define __CORE_COMPONENT_CONTAINER_H__

#include "Core/Components/ComponentTypes.h"


class CORE_API CComponentContainer
{

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
     CComponentContainer();
    ~CComponentContainer();

//*********************************************
//            INTERFACE
//*********************************************
public:
    Bool                PopComponentWithID  ( TComponentID);
    Bool                PopComponent        ( IComponent* component );
    Bool                PushComponent       ( IComponent* component );
    Bool                HasComponentWithID  ( TComponentID id);
    IComponent*         GetComponentByID    ( TComponentID id );

//*********************************************
//            MEMBERS
//*********************************************
protected:
    u8 m_rawData[128];
    class CComponentContainer_PrivateData*     m_privateData;
};


#endif //__CORE_COMPONENT_CONTAINER_H__