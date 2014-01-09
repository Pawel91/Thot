#if !defined(__GAME_SPACE_SHIP_CAMERA_COMPONENT_H__)
#define __GAME_SPACE_SHIP_CAMERA_COMPONENT_H__

#include "Core/Components/CameraComponent.h"

class CRobotCameraComponent: public CCameraComponentBase
{

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
     CRobotCameraComponent();
    ~CRobotCameraComponent();


//*********************************************
//            INTERFACE
//*********************************************
public:
    virtual void        OnUpdate( float deltaTime )override;
            void        Apply();


protected:
            void        PrivateUpdate(float deltaTime);
            void        GetCameraTM( m4x4& outTM);

//*********************************************
//            MEMBERS
//*********************************************
protected:
    tVect3                  m_parentToCameraDir;
    float                   m_parentToCameraDistance;
    class CBindingComponent* m_bindingComponent;
};



#endif //__GAME_SPACE_SHIP_CAMERA_COMPONENT_H__