#include "Core_PCH.h"
#include "AssimpNode.h"

#include "Render/Mesh/MeshBase.h"
#include "Render/SkeletonAnimation/Skeleton.h"

#define TEST_LOAD_MESH

#if defined TEST_LOAD_MESH



THOT_TODO("REMOVE ASSIMP INCLUDES FROM HERE AND PUT LOADING MESH SOMEWHERE ELSE");
#include "assimp/types.h"
#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/cimport.h"

#include "Core/SceneGraph/SceneRenderableNode.h"
#include "Core/SceneGraph/SceneGraph.h"
#include "Core/SceneGraph/SceneAssimpConverter.h"
#include "Core/SceneGraph/AssimpNode.h"

#include "Core/Components/RenderableComponent.h"

void DebugLoadRenderableComponent( CRenderableComponent* component, const char* filePath, const char* nodeName )
{
    CSceneGraph*            m_sceneGraph = NULL;
    Assimp::Importer*       m_importer = NULL;

    std::string extensionList;
    m_importer = THOT_NEW Assimp::Importer;
    m_importer->GetExtensionList(extensionList);
    THOT_TRACE_LINE("Extensions:[%s]", extensionList.c_str());

    //const char* modelName = "Data\\models\\golem_clean.dae";
    const aiScene* scene = m_importer->ReadFile( filePath, aiProcessPreset_TargetRealtime_MaxQuality  );

    if( !scene )
    {
        THOT_TRACE_LINE( "%s", m_importer->GetErrorString() );
        THOT_ASSERT(0);
    }

    CSceneAssimpConverter* sceneConverter = THOT_NEW CSceneAssimpConverter(scene);
    m_sceneGraph = sceneConverter->CreateScene( );

    //CAssimpSceneNode* assimpNode = m_sceneGraph->GetNodeByName( m_sceneGraph->GetRoot(), nodeName );
    //THOT_ASSERT(assimpNode, "FAILED TO LOAD NODE[%s]", nodeName);
    //for(u64 i=0; i<assimpNode->m_meshes.GetSize();i++)
    //{
    //    component->InsertMesh( assimpNode->m_meshes[i]);
    //}

    thVector<IMesh*> meshes;
    m_sceneGraph->GetRenderableNodes(m_sceneGraph->GetRoot(), meshes);
    THOT_ASSERT(meshes.Size()>0);
    
    for( u64 i=0; i<meshes.Size(); i++)
    {
        component->InsertMesh(meshes[i]);
    }



    if( scene->HasTextures() )
    {
        THOT_TRACE_LINE("SCENE HAS TEXTURES");
    }

    if( scene->HasMaterials() )
    {
        THOT_TRACE_LINE( "NUMBER OF MATERIALS:[%d]", scene->mNumMaterials );
    }
    
    if( scene->HasMeshes() )
    {
       
        THOT_TRACE_LINE( "NUMBER OF MESHES:[%d]",scene->mNumMeshes );
    }
    else
    {
        THOT_ASSERT(0, "nothing to render? wtf?");
    }
}

#endif //


CAssimpSceneNode::~CAssimpSceneNode()
{
    for( u32 i=0; i<m_meshes.Size(); i++ )
    {
        if( m_meshes[i] )
        {
            THOT_DELETE(m_meshes[i]);
        }
    }

    if( m_skeleton )
    {
        THOT_DELETE(m_skeleton);
    }
}
//--------------------------------------------------------------------------
CAssimpSceneNode::CAssimpSceneNode()
    : m_skeleton        ( NULL )
{
    
}

//--------------------------------------------------------------------------
Bool CAssimpSceneNode::AppendMesh( IMesh* mesh )
{
    if( mesh == NULL )
    {
        return false;
    }

    m_meshes.PushBack(mesh);

    return true;
}

//--------------------------------------------------------------------------
const CSkeleton* CAssimpSceneNode::GetSkeleton( )const
{
    return m_skeleton;
}

//--------------------------------------------------------------------------
CSkeleton* CAssimpSceneNode::GetSkeleton( )
{
    return m_skeleton;
}

//--------------------------------------------------------------------------
Bool CAssimpSceneNode::SetSkeleton( CSkeleton* skeleton )
{
    if( !skeleton )
    {
        return false;
    }

    if( m_skeleton )
    {
        THOT_DELETE( m_skeleton );
    }

    m_skeleton = skeleton;

    return true;
}

//--------------------------------------------------------------------------
void CAssimpSceneNode::OnUpdateThis( float dt) 
{

}

//-----------------------------------------------------------------------------
void CAssimpSceneNode::OnInit() 
{

}
