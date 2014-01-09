#if !defined(__CORE_CAMERA_SYSTEM_H__)
#define __CORE_CAMERA_SYSTEM_H__


#include "Core/System/SystemBase.h"


class CORE_API CCameraSystem: public CSystemBase<CCameraSystem>
{
//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
     CCameraSystem();
    ~CCameraSystem();


//*********************************************
//            INTERFACE
//*********************************************
public:
    virtual     void        OnInit() override;
    virtual     void        Execute( ) override;
    virtual     void        RegisterComponents() override;
    virtual     void        OnEntityComponentChange(    const CEntityHandle& handle,
                                                        IComponent* component,
                                                        bool Added ) override; 


//*********************************************
//            MEMBERS
//*********************************************
protected:
    thVector<CEntityHandle>  m_cameraEntities;
    u32                     m_activeCameraIndex;
};





#endif //__CORE_CAMERA_SYSTEM_H__