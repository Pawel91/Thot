#if !defined(__CORE_SCENE_ROOT_H__)
#define __CORE_SCENE_ROOT_H__

#include "Core/SceneGraph/SceneNode.h"

class CORE_API CSceneRoot:public ISceneNode
{

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
      CSceneRoot(){}
     ~CSceneRoot(){}



//*********************************************
//            INTERFACE
//*********************************************
public:
    virtual void        OnInit          () override;
    virtual void        OnUpdateThis    ( float fDeltaTime ) override;


//*********************************************
//            MEMBERS
//*********************************************
protected:

};


#endif //__CORE_SCENE_ROOT_H__