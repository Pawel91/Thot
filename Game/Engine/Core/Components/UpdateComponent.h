//  [11/10/2013 Radu]
#if !defined(__CORE_UPDATE_COMPONENT_H__)
#define __CORE_UPDATE_COMPONENT_H__

#include "Core/Components/ComponentBase.h"

// component used to update stuff;
class CORE_API CUpdateComponent: public CComponetBase< CUpdateComponent >
{

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
     CUpdateComponent();
    ~CUpdateComponent();

//*********************************************
//            INTERFACE
//*********************************************
public:
    virtual     void        OnUpdate ( float deltaTime)     = 0;

//*********************************************
//            MEMBERS
//*********************************************
protected:

};


#endif //__CORE_UPDATE_COMPONENT_H__