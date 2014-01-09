#if !defined(__CORE_SCENE_RENDERABLE_NODE_H__)
#define __CORE_SCENE_RENDERABLE_NODE_H__

#include "SceneNode.h"
#include "Core/SceneGraph/SceneNode.h"

class CORE_API CSceneRenderableNode: public ISceneNode
{

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
             CSceneRenderableNode();
    virtual ~CSceneRenderableNode();

//*********************************************
//            INTERFACE
//*********************************************
public:

    virtual     void                OnInit              () override;
    virtual     void                OnUpdateThis        ( float fDeltaTime )override;

//*********************************************
//            MEMBERS
//*********************************************
protected:
};

class CORE_API CSceneRenderableDemo: public CSceneRenderableNode
{
public:
    CSceneRenderableDemo(){}
    ~CSceneRenderableDemo(){}

public:
    virtual     void                OnInit              () override;
    virtual     void                OnUpdateThis        ( float fDeltaTime )override;
};


class CORE_API CBoneNode: public CSceneRenderableNode
{
public:
    CBoneNode(){}

    typedef CSceneRenderableNode super;
    virtual ~CBoneNode(){}
};


#endif //__CORE_SCENE_RENDERABLE_NODE_H__