#if !defined(__CORE_SCENE_CAMERA_H__)
#define __CORE_SCENE_CAMERA_H__

#include "Core/SceneGraph/SceneNode.h"

//[TODO] REFACTOR; this is a fast port of old free camera;
class CSceneCameraBase: public ISceneNode
{

public:
     CSceneCameraBase();
    ~CSceneCameraBase();

public:
    virtual void        OnInit()override;
            void        GetCameraTM( m4x4& outTM );
            void        Apply();
            void        GetRotation ( m3x3& out )const;

protected:
    virtual void        OnUpdateThis( float fDeltaTime )  override;


protected:
        tVect3      m_vRot;
        tVect3      m_vPos;
        float       m_fFov;
        float       m_fCameraSpeed;
};

#endif  //__CORE_SCENE_CAMERA_H__