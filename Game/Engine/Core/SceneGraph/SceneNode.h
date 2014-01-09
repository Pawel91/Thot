#ifndef __RENDER_SCENE_NODE_H__
#define __RENDER_SCENE_NODE_H__

#include "Kernel/DataStructures/CString.h"
#include "Kernel/DataStructures/Array/Vector.h"
#include "Core/Components/TransformationComponent.h"
#include "Core/Components/ComponentContainer.h"

class CSceneGraph;
class ISceneNode;

THOT_DECLARE_TEMPLATE_API(CORE_TEMPLATE_API, thVector<ISceneNode*> );

class CORE_API ISceneNode
{
public:
    friend class CSceneGraph;

    typedef thVector<ISceneNode*>        TSceneNodes;

//*********************************************
//            CONSTR/DESTR
//*********************************************

public:
    virtual bool IsRenderable(){return false;}
                ISceneNode();
    virtual     ~ISceneNode() = 0;


//*********************************************
//          INTERFACE
//*********************************************
public:
    // get functions;
    virtual     void                OnInit              ( )                     = 0;
                void                OnUpdate            ( float fDeltaTime );

                void                SetLocalTM          ( m4x4 TM);
                const m4x4&         GetLocalTM          ( ) const;
                const m4x4&         GetWorldTM          ( ) const;
                u32                 GetChildCount       ( ) const;
    inline      Bool                IsLeaf              ( ) const;
    inline      Bool                IsRoot              ( ) const;
                ISceneNode*         GetChild            ( u32 index );
                const ISceneNode*   GetChild            ( u32 index ) const;
                ISceneNode*         GetParent           ( );
                const ISceneNode*   GetParent           ( )const;

                const CString&      GetName             ( )const;
                Bool                SetName             ( const CString& name );

    // set functions
                void                AppendChild         ( ISceneNode* sceneNode );
                void                SetParent           ( ISceneNode* parentNode );


//*********************************************
//            HELPER FUNCTIONS
//*********************************************
protected:

    // virtual functions that update only this node; the children are updated after;
    virtual     void                OnUpdateThis        ( float fDeltaTime )            = 0;
                void                UpdateChildren      ( float fDeltaTime );

//*********************************************
//            HELPER FUNCTIONS
//*********************************************
protected:

    //CComponentContainer         m_componentContainer;

    ISceneNode*                 m_parent;
    TSceneNodes                 m_children;
    CTransformationComponent    m_transformComponent;
    CString                     m_name;
};

inline Bool ISceneNode::IsLeaf ( )const
{
    return GetChildCount() == 0;
}

inline Bool ISceneNode::IsRoot( )const
{
    return m_parent == NULL;
}


class CEmptySceneNode: public ISceneNode
{
public:
    CEmptySceneNode()
    {
        m_name = "CEmptySceneNode";
    }

public:
    virtual void OnUpdateThis( float deltaTime )override
    {
        //does nothing
    }

    virtual void OnInit() override
    {
        // does nothing
    }
};



#endif /*__RENDER_SCENE_NODE_H__*/