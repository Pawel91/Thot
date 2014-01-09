#pragma once
#ifndef __RENDER_SCENE_TRANSFORM_NODE_H__
#define __RENDER_SCENE_TRANSFORM_NODE_H__

#include "SceneNode.h"

// scene node that has the transformations implemented;
class CORE_API CSceneTransformNode: public ISceneNode
{

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
             CSceneTransformNode();
    virtual ~CSceneTransformNode();


//*********************************************
//            INTERFACE
//*********************************************
public:
    virtual     void                GetLocalTM          ( m4x4& outTM ) const   override;
    virtual     const m4x4&         GetLocalTM          ( )const;
    virtual     Bool                IsRenderable        ( )const                override;
    virtual     void                SetLocalTM          ( const m4x4& TM )      override;

//*********************************************
//            MEMBERS
//*********************************************
protected:
    m4x4            m_localTM;
    m4x4            m_worldTM;
};




#endif /*__RENDER_SCENE_TRANSFORM_NODE_H__*/