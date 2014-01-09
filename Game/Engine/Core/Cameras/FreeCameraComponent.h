#if !defined(__CORE_FREE_CAMERA_COMPONENT_H__)
#define __CORE_FREE_CAMERA_COMPONENT_H__

#include "Core/Components/CameraComponent.h"

class CORE_API CFreeCameraComponent: public CCameraComponentBase
{

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
     CFreeCameraComponent();
    ~CFreeCameraComponent();


//*********************************************
//            INTERFACE
//*********************************************
public:
    virtual void        OnUpdate( float deltaTime ) override;

            void        GetCameraTM( m4x4& outTM );
            void        Apply();
            void        GetRotation ( m3x3& out )const;

//*********************************************
//            MEMBERS
//*********************************************
protected:
        tVect3      m_vRot;
        tVect3      m_vPos;
        float       m_fFov;
        float       m_fCameraSpeed;
};



#endif //__CORE_FREE_CAMERA_COMPONENT_H__