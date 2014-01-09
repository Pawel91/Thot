#include "Core_PCH.h"
#include "SceneGraph.h"

#include "SceneNode.h"
#include "Kernel/Profiler/Profiler.h"
#include "Render/RenderGL.h"
#include "Render/Materials/Material.h"
#include "MathCore/MathUtils.h"
#include "Core/SceneGraph/AssimpNode.h"


#define TEST_TIME
#if defined(TEST_TIME)
#   include "Kernel/Time/Timer.h"
#   include "Kernel/ThotWindows.h"
#endif

CSceneGraph:: CSceneGraph()
    :m_rootNode     ( NULL )
{

}


CSceneGraph::~CSceneGraph()
{
    if( m_rootNode )
    {
        THOT_DELETE(m_rootNode);
    }
}



//void CSceneGraph::OnDraw( )const
//{
//RENDER_GUARD_BLOCK
//    DECLARE_PROFILE_SCOPED("CSceneGraph::OnDraw()");
//
//    if( m_rootNode )
//    {
//        m_rootNode->RecursiveDraw( this );
//    }
//
//
//#ifdef _DEBUG
//    if(m_rootNode)
//    {
//        //DbgRender(m_rootNode);
//    }
//#endif
//
//}

//void CSceneGraph::UpdateRecursive( ISceneNode* node, float fDeltaTime )
//{
//    if( !node )
//    {
//        return;
//    }
//
//    node->OnUpdate(fDeltaTime);
//
//    u32 childCount = node->GetChildCount();
//
//    for( u32 i=0; i<childCount; i++ )
//    {
//        UpdateRecursive( node->GetChild(i), fDeltaTime );
//    }
//}

//void CSceneGraph::DbgRender(ISceneNode* node )const
//{
//    if( node )
//    {
//        m4x4 mTM = i4x4; node->GetWorldTM(mTM);
//        tVect3 vThisPos = POS(mTM);
//
//        CShader::GetCurrentShader()->SetMaterial(CMaterial::GetMaterial(CColor(0.f, 1.f, 0.f, 1.f)));
//
//        if( node->GetName() == "root" )
//        {
//            CShader::GetCurrentShader()->SetMaterial(CMaterial::GetMaterial(CColor(0.f, 0.f, 1.f, 1.f)));
//        }
//
//        if( node->GetName() == "head" )
//             CShader::GetCurrentShader()->SetMaterial(CMaterial::GetMaterial(CColor(1.f, 0.f, 1.f, 1.f)));
//
//        for( u32 i=0; i<node->GetChildCount(); i++ )
//        {
//            m4x4 mChildTM = i4x4; 
//            ISceneNode* child = node->GetChild(i);
//            child->GetWorldTM(mChildTM);
//
//
//            tVect3 vChildPos = POS(mChildTM);
//            //gl::Begin( gl::LINES );
//            //gl::Vertex(vThisPos);
//            //gl::Vertex(vChildPos);
//            //gl::End();
//        }
//
//        for( u32 i=0; i<node->GetChildCount(); i++ )
//        {
//            DbgRender( node->GetChild(i) );
//        }
//
//    }
//}

//----------------------------------------------------------------------
CAssimpSceneNode* CSceneGraph::GetNodeByName( ISceneNode* node, const char* nodeName )
{
    if( node->GetName() == nodeName )
    {
        return (CAssimpSceneNode*)node;
    }

    for( u64 i=0; i<node->m_children.Size(); i++ )
    {
        ISceneNode* child = GetNodeByName( node->m_children[i], nodeName );
        if( child )
        {
            return (CAssimpSceneNode*)child;
        }
    }

   return NULL;
}

//--------------------------------------------------------------------------------
void CSceneGraph::GetRenderableNodes(ISceneNode* node, thVector<IMesh*>& outNodes)
{
    for( u64 i=0; i<node->m_children.Size(); i++ )
    {
        ISceneNode* child = node->m_children[i];
        if( child && child->IsRenderable() )
        {
            CAssimpSceneNode* renderable = (CAssimpSceneNode*)child;
            for( u64 i=0; i<renderable->m_meshes.Size(); i++ )
            {
                outNodes.PushBack(renderable->m_meshes[i]);
            }
        }

        GetRenderableNodes(child, outNodes);
    }
}

//----------------------------------------------------------------------
void CSceneGraph::OnUpdate( float fDeltaTime )
{
    DECLARE_PROFILE_SCOPED( "CSceneGraph::OnUpdate");

    if( !m_rootNode )
    {
        return ;
    }

    // root node will update recursively al the children
    m_rootNode->OnUpdate(fDeltaTime);
}



//----------------------------------------------------------------------
ISceneNode* CSceneGraph::GetRoot( )
{
    return m_rootNode;
}

//----------------------------------------------------------------------
const ISceneNode* CSceneGraph::GetRoot( )const
{
    return m_rootNode;
}

//----------------------------------------------------------------------
Bool CSceneGraph::SetRoot( ISceneNode* node )
{
    if( !node)
    {
        return false;
    }

    m_rootNode = node;
    return true;
}
