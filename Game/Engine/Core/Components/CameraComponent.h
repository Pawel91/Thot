#if !defined(__CORE_CAMERA_COMPONENT_H__)
#define __CORE_CAMERA_COMPONENT_H__

#include "Core/Components/ComponentBase.h"

class CORE_API CCameraComponentBase: public CComponetBase<CCameraComponentBase>
{

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
     CCameraComponentBase();
    ~CCameraComponentBase();

//*********************************************
//            INTERFACE
//*********************************************
public:
    virtual void        OnUpdate( float deltaTime )     = 0;

//*********************************************
//            MEMBERS
//*********************************************
protected:

};




#endif //__CORE_CAMERA_COMPONENT_H__