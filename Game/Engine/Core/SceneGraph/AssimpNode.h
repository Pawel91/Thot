#if !defined(__CORE_ASSIMP_NODE_H__)
#define __CORE_ASSIMP_NODE_H__

#include "Core/SceneGraph/SceneNode.h"

class IMesh;
class CSkeleton;

THOT_DECLARE_TEMPLATE_API( CORE_TEMPLATE_API, thVector<IMesh*>);

class CORE_API CAssimpSceneNode:public ISceneNode
{
public:
    typedef thVector<IMesh*>  TMeshes;
public:
    CAssimpSceneNode();
    ~CAssimpSceneNode();

    virtual bool        IsRenderable(){return true;}
    virtual void        OnUpdateThis( float dt) override;
    virtual void        OnInit()override;

                Bool                AppendMesh          ( IMesh* mesh );
                
                const CSkeleton*    GetSkeleton         ( )const;
                CSkeleton*          GetSkeleton         ( );
                Bool                SetSkeleton         ( CSkeleton* skeleton );
public:
    TMeshes     m_meshes;
    CSkeleton*  m_skeleton;
};

class CRenderableComponent;
#define TEST_LOAD_MESH
void CORE_API DebugLoadRenderableComponent( CRenderableComponent* component, const char* filePath, const char* nodeName );

#endif //__CORE_ASSIMP_NODE_H__