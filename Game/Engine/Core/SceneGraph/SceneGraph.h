#ifndef __RENDER_SCENE_GRAPH_H__
#define __RENDER_SCENE_GRAPH_H__

#include "Kernel/DataStructures/Array/Vector.h"

class ISceneNode;
class CAssimpSceneNode;
class IMesh;

class CORE_API CSceneGraph
{

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
     CSceneGraph();
    ~CSceneGraph();

//*********************************************
//            INTERFACE
//*********************************************
public:
    void                OnUpdate        ( float fDeltaTime );
    void                DbgRender       ( ISceneNode* node)const;

    ISceneNode*         GetRoot         ( );
    const ISceneNode*   GetRoot         ( )const;


    CAssimpSceneNode*       GetNodeByName( ISceneNode* node, const char* nodeName );
    void                    GetRenderableNodes(ISceneNode* node, thVector<IMesh*>& outNodes);    

    // node will be owned by scene
    Bool                SetRoot         ( ISceneNode* node );


//*********************************************
//            HELPERS
//*********************************************
protected:
    //void        UpdateRecursive( ISceneNode* node, float fDeltaTime );

//*********************************************
//            MEMBERS
//*********************************************
protected:
        ISceneNode*     m_rootNode;
};


#endif /*__RENDER_SCENE_GRAPH_H__*/