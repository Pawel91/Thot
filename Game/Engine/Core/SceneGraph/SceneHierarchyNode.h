#pragma once
#ifndef __RENDER_SCENE_HIERARCHY_NODE_H__
#define __RENDER_SCENE_HIERARCHY_NODE_H__

#include "SceneTransformNode.h"

template class CORE_API CVector<ISceneNode*>;

// scene node that has Hierarchy info implemented;
class CORE_API CSceneHierarchyNode: public CSceneTransformNode
{

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
             CSceneHierarchyNode();
    virtual ~CSceneHierarchyNode();


//*********************************************
//            INTERFACE
//*********************************************
public:
    typedef CVector<ISceneNode*> TSceneNodes;

    //draw function that will not be called if the node is not renderable;
    virtual     u32                 GetChildCount       ( )const            override;
    virtual     ISceneNode*         GetChild            ( u32 index )       override;
    virtual     const ISceneNode*   GetChild            ( u32 index ) const override;
    virtual     ISceneNode*         GetParent           ( )                 override;
    virtual     const ISceneNode*   GetParent           ( )const            override;

    // set functions
    virtual     void                AppendChild         ( ISceneNode* sceneNode )   override;
    virtual     void                SetParent           ( ISceneNode* )             override;

    virtual     CString&            GetName             ( )                     override;
    virtual     const CString&      GetName             ( )const                override;
    virtual     Bool                SetName             ( const CString& name ) override;


//*********************************************
//            MEMBERS
//*********************************************
protected:
    ISceneNode*         m_parent;
    TSceneNodes         m_childs;
    CString             m_name;

};


#endif /*__RENDER_SCENE_HIERARCHY_NODE_H__*/