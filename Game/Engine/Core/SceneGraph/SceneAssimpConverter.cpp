#include "Core_PCH.h"
#include "SceneAssimpConverter.h"

#include "Render/Mesh/Mesh.h"
#include "Render/Buffers/Vertex.h"
#include "Core/SceneGraph/SceneRenderableNode.h"
#include "Core/SceneGraph/AssimpNode.h"
#include "Render/Materials/Material.h"
#include "Render/SkeletonAnimation/Bone.h"
#include "Render/SkeletonAnimation/BoneTrack.h"
#include "Render/SkeletonAnimation/Skeleton.h"


// ASSIMP INCLUDES
#include "assimp/types.h"
#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/cimport.h"


#if !defined(THOT_TRACE_LINE)
#   error wtf?
#endif

#ifdef _DEBUG

//#define ASSERT_ON_TRACE

#ifndef TRACE_SCENE_ASSIMP_CONVERTER
#   ifndef ASSERT_ON_TRACE
#       define TRACE_CONVERTER(_format, ...) do{THOT_TRACE_LINE(_format, __VA_ARGS__);}while(false);
#else
#       define TRACE_CONVERTER(_format, ...) do{ THOT_TRACE_LINE(_format, __VA_ARGS__); /*THOT_ASSERT(0);*/ }while(false)
#endif /*ASSERT_ON_TRACE*/
#   else
#       error TRACE_CONVERTER allready defined; change macro name to resolve conflict;
#   endif /*TRACE_SCENE_ASSIMP_CONVERTER*/
#else
#   define TRACE_CONVERTER(_format, ...)
#endif /*_DEBUG*/




CSceneAssimpConverter::CSceneAssimpConverter( const aiScene* assimpScene )
    :m_assimpScene      ( assimpScene )
    ,m_skeleton         ( NULL ) //[TODO] temp to do some fast testing with skeletons; remove after;
{
}

CSceneAssimpConverter::~CSceneAssimpConverter( )
{
    RestoreDefaultSkel();
}


void CSceneAssimpConverter::SetRootTransformToNull ()
{
    if( !m_assimpScene)
    {
        return;
    }

    aiNode* rootNode = m_assimpScene->mRootNode;
    m4x4 rootTransform = (*((m4x4*)& m_assimpScene->mRootNode->mTransformation) );

    rootTransform = Transpose(rootTransform);

    for( u32 i=0; i<rootNode->mNumChildren; i++ )
    {
        aiNode* child = rootNode->mChildren[i];
        
        m4x4 childLocalTM;
        GetLocalTM(child, childLocalTM );

        m4x4 childTM = childLocalTM * rootTransform;

        SetLocalTM(child, childTM );
    }

    SetLocalTM( rootNode, i4x4 );
}


Bool CSceneAssimpConverter::MoveSkeletonToModelSpace ()
{
    CString strScene    = "Scene";
    CString strArmature = "Armature";
    CString strRoot     = "root";
    CString strModel    = "golem";

    aiNode* assimpScene     = NULL;
    aiNode* assimpArmature  = NULL;
    aiNode* assimpRoot      = NULL;
    aiNode* assimpModel     = NULL;

    if( !FindAssimpNodeByName( strScene, assimpScene) )
    {
        return (false);
    }

    if( !FindAssimpNodeByName( strArmature, assimpArmature) )
    {
        return (false);
    }

    if( !FindAssimpNodeByName( strRoot, assimpRoot) )
    {
        return (false);
    }

    if( !FindAssimpNodeByName( strModel, assimpModel) )
    {
        return (false);
    }

    m4x4 mScene     = i4x4;
    m4x4 mArmature  = i4x4;
    m4x4 mRoot      = i4x4;
    m4x4 mModel     = i4x4;

    GetLocalTM( assimpScene,    mScene );
    GetLocalTM( assimpArmature, mArmature );
    GetLocalTM( assimpRoot,     mRoot );
    GetLocalTM( assimpModel,    mModel );

    m4x4 invModel = i4x4;
    InvMat(mModel, invModel );

    m4x4 newRootTM = mRoot * mArmature * invModel;

    SetLocalTM( assimpRoot, newRootTM );
    assimpRoot->mParent = assimpModel;
    
    assimpArmature->mNumChildren = 0;
    assimpArmature->mChildren = NULL;

    assimpModel->mNumChildren = 1;
    assimpModel->mChildren = new aiNode*[1];
    assimpModel->mChildren[0] = assimpRoot;

    return true;
}


void CSceneAssimpConverter::RestoreDefaultSkel( )
{
    CString strModel        = "golem";
    aiNode* assimpModel     = NULL;
 
    if( !FindAssimpNodeByName( strModel, assimpModel) )
    {
        return ;
    }
    m4x4 mModel     = i4x4;
    GetLocalTM( assimpModel, mModel );

    assimpModel->mNumChildren = 0;
    delete assimpModel->mChildren[0];
}

CSceneGraph* CSceneAssimpConverter::CreateScene ( )
{
    if( !m_assimpScene )
    {
        return NULL;
    }

    SetRootTransformToNull( );
    MoveSkeletonToModelSpace( );
    
    if( !CreateAnimations( ) )
    {
       // TRACE_CONVERTER( "failed to create animations!!" );
    }

#ifdef _DEBUG
    
    CString nodeName;
    for(u32 i=0; i<m_assimpScene->mNumAnimations; i++)
    {
        aiAnimation* assimpAnimation = m_assimpScene->mAnimations[i];
        for( u32 i=0; i<assimpAnimation->mNumChannels; i++  )
        {
            aiNodeAnim* assimpNodeAnim = assimpAnimation->mChannels[i];
            nodeName = assimpNodeAnim->mNodeName.C_Str();
            THOT_TRACE_LINE("[%d] [%s]",i,  nodeName.GetBuffer() );
        }
    }
    u32 nbNodes = GetSubtreeChildCount(m_assimpScene->mRootNode );

#endif /*_DEBUG*/


    //create scene and root node;
    CSceneGraph* scene = THOT_NEW CSceneGraph;
    ISceneNode* root = CreateNode( m_assimpScene->mRootNode );
    if ( !scene->SetRoot( root ) )
    {
        return NULL;
    }

    //create scene recursive from root node;
    CreateRecursive( scene, root, m_assimpScene, m_assimpScene->mRootNode );

    return scene;
}

void CSceneAssimpConverter::CreateRecursive( CSceneGraph* scene, ISceneNode* parent, const aiScene* m_assimpScene, const aiNode* assimpNode )
{
    if( !assimpNode || !parent || !scene || !m_assimpScene )
    {
        return;
    }

    for( uint i=0; i<assimpNode->mNumChildren; i++ )
    {
        const aiNode* childrenNode = assimpNode->mChildren[i];
        ISceneNode* node = CreateNode( childrenNode );
        if( !node )
        {
            THOT_ASSERT(0);
            return;
        }
        node->SetParent(parent);
        parent->AppendChild(node);
        CreateRecursive( scene, node, m_assimpScene,  childrenNode );
    }


}

ISceneNode* CSceneAssimpConverter::CreateNode( const aiNode* assimpNode )
{
    if( !assimpNode || !m_assimpScene)
    {
        return NULL;
    }

    //create proper node type
    ISceneNode* node = NULL;
    if( assimpNode->mNumMeshes>0 )
    {
        node = THOT_NEW CAssimpSceneNode;
    }
    else if ( AssimpNodeIsBone( assimpNode) )
    {
        // create a bone;
        int a=0; a++;
        node = THOT_NEW CBoneNode;
    }
    else
    {
        node = THOT_NEW CEmptySceneNode;
    }

    node->SetName( assimpNode->mName.C_Str() );

    // set local transform for this node;
    THOT_COMPILE_ASSERT(sizeof(m4x4) == sizeof(aiMatrix4x4) );
    m4x4* mTM (NULL);
    aiMatrix4x4 aiMatrix = assimpNode->mTransformation;
    aiTransposeMatrix4( &aiMatrix );
    mTM = reinterpret_cast<m4x4*>(&aiMatrix);
    
    
    if(!IsOrtho(*mTM))
    {
        THOT_TRACE_LINE( "matrix:" );
        mTM->DebugTrace();

        //VectNor(AXEX(*mTM));
        //VectNor(AXEY(*mTM));
        //VectNor(AXEZ(*mTM));
        //THOT_ASSERT(0);
    }

    node->SetLocalTM(*mTM);

    //add meshes to this node if there is is any
    if( assimpNode->mNumMeshes>0 )
    {

        for( uint i=0; i<assimpNode->mNumMeshes; i++ )
        {
            uint meshIndex = assimpNode->mMeshes[i];
            THOT_ASSERT(meshIndex < m_assimpScene->mNumMeshes );

            IMesh* mesh = CreateMesh( m_assimpScene->mMeshes[meshIndex] );
            

            if( mesh != NULL )
            {
                CAssimpSceneNode* renderableNode = reinterpret_cast<CAssimpSceneNode*>(node);
                Bool rezult = renderableNode->AppendMesh(mesh);
                THOT_ASSERT(rezult == true);

                if( m_assimpScene->mMeshes[meshIndex]->HasBones() )
                {
                    THOT_ASSERT(m_skeleton, "we have a mesh with bones and the skeleton was not created");
                    renderableNode->SetSkeleton( m_skeleton );
                }




            }
        }
    }

    return node;
}

IMesh* CSceneAssimpConverter::CreateMesh( const aiMesh* assimpMesh)
{
    if( !assimpMesh )   
    {
        return NULL;
    }
    
    //get primitive from first face; latter we have to verify that all the faces has same primitive type;
    EMeshPrimitive primitiveType = GetMeshPrimitive ( &assimpMesh->mFaces[0] );
    if( primitiveType == EMeshPrimitive::E_MESH_PRIMITIVE_NONE ) // if primitive is not supported
    {
        return NULL;
    }
   
    thVector<RenderLowLevel::SVertex_PNTB4> vertices;
    vertices.Resize(assimpMesh->mNumVertices);
    thVector<u32> indices;

    if( assimpMesh->HasBones() )
    {
        static Bool uniqueMesh = true;
        THOT_ASSERT(uniqueMesh);
        uniqueMesh = false;

        for( u32 i=0; i<assimpMesh->mNumBones; i++ )
        {
            aiBone* bone = assimpMesh->mBones[i];

            for( u32 j=0; j<bone->mNumWeights; j++  )
            {
                const aiVertexWeight& assimpVertexWeight = bone->mWeights[j];

                THOT_ASSERT( m_skeleton, "Skeleton was not created" );
                CBone* nativeBone = m_skeleton->GetBoneByName( bone->mName.C_Str() );
                THOT_ASSERT( nativeBone, "Cannot find bone[%s] in native skeleton", bone->mName.C_Str() );

                if( nativeBone )
                {
                    Bool added = vertices[ assimpVertexWeight.mVertexId ].AddBoneData( nativeBone->GetBoneIdx(), assimpVertexWeight.mWeight);

                    THOT_ASSERT( added, "FAIL TO ADD BONE DATA TO VERTEX");
                }
            }

        }

        THOT_ASSERT( ValidateVerticesAnimation(vertices), "WARNING!!!!!! vertices animation validation failed for mesh [%s]", assimpMesh->mName.C_Str() );
    }

        
    for( uint i=0; i<assimpMesh->mNumVertices; i++  )
    {
        THOT_COMPILE_ASSERT2(sizeof(tVect3) == sizeof(assimpMesh->mVertices[0]), "SIZEOF VECTOR MUST EQUALS SIZE OF VECTOR USE BY ASSIMP" );
        
        // set position of the vertex;
        tVect3* vec = (tVect3*)&assimpMesh->mVertices[i];
        vertices[i].m_vertex = *vec;

        if( assimpMesh->HasNormals() )
        {
            THOT_COMPILE_ASSERT( sizeof(tVect3) == sizeof(assimpMesh->mNormals[0]) );
            tVect3* normal = (tVect3*)&assimpMesh->mNormals[i];
            
            //THOT_ASSERT( IsUnit(*normal));
            VectNor(*normal);
            vertices[i].m_normal = *normal;
        }
        
        if( assimpMesh->HasVertexColors(0) )
        {
            THOT_COMPILE_ASSERT(sizeof(CColor) == sizeof(assimpMesh->mColors[0][0]) );
            CColor* color = reinterpret_cast<CColor*>( &assimpMesh->mColors[0][i]);
            //mesh->AppendColor(*color);
        }


        if( assimpMesh->HasTextureCoords(0) )
        {
            THOT_COMPILE_ASSERT(sizeof(tVect3) == sizeof(assimpMesh->mTextureCoords[0][0]) );
            tVect3* texCoord;
            texCoord = reinterpret_cast<tVect3*> ( &assimpMesh->mTextureCoords[0][i] );
            //int a =0;
            //vertex.m_textCoord3 = *texCoord;
            //mesh->AppendTexCoord(*texCoord);

            vertices[i].m_textCoord3 = *texCoord;
        }
    }

    // populate indices
    for( uint i=0; i<assimpMesh->mNumFaces; i++)
    {
        const aiFace* face = &assimpMesh->mFaces[i];
        THOT_ASSERT( primitiveType == GetMeshPrimitive(face));
        for( uint j=0; j<face->mNumIndices; j++)
        {

            //mesh->AppendIndex(face->mIndices[j]);
            indices.PushBack( face->mIndices[j] );
        }

    }

    IMesh* mesh = MeshFactory::CreateMesh( vertices, indices );
    mesh->SetPrimitiveType( primitiveType );

    CMaterial material;
    
    if( !GetNativeMaterial( m_assimpScene->mMaterials[ assimpMesh->mMaterialIndex ], material ) )
    {
        THOT_TRACE_LINE( "WARNING!! FAILED TO LOAD A MATERIAL\n" );
    }

    //material.m_ambient  = CColor(0.2f, 0.5f, 0.6f, 1.f );
    //material.m_diffuse  = CColor(0.2f, 0.5f, 0.6f, 1.f );
    //material.m_specular = CColor(0.2f, 0.5f, 0.6f, 1.f );
    //material.m_opacity = 0.3f;
    mesh->SetMaterial( material );


#ifdef DEBUG_SKINNING
    if(assimpMesh->HasBones())
    {
        THOT_ASSERT(m_skeleton);
        m_skeleton->m_debugMesh.Resize( vertices.GetSize() );
        for( u64 i=0; i<vertices.GetSize(); i++ )
        {
            m_skeleton->m_debugMesh[i] = vertices[i];
        }
    }
#endif /*DEBUG_SKINNING*/


    return mesh;
}


Bool CSceneAssimpConverter::GetNativeMaterial   ( const aiMaterial* assimpMaterial, CMaterial& outNativeMaterial  )
{
    aiColor4D ambient, diffuse, specular, transparent;

    if( AI_SUCCESS == aiGetMaterialColor( assimpMaterial, AI_MATKEY_COLOR_DIFFUSE, &diffuse) )
    {
        memcpy( &outNativeMaterial.m_diffuse, &diffuse, sizeof(CColor) );
    }
    else
    {
        return false;
    }


    if( AI_SUCCESS == aiGetMaterialColor( assimpMaterial, AI_MATKEY_COLOR_AMBIENT, &ambient) )
    {
        memcpy( &outNativeMaterial.m_ambient, &ambient, sizeof(CColor) );

#if defined(THOT_LICENTA)
        outNativeMaterial.m_ambient = CColor(0.f, 0.25f, 0.28f, 0.23f);
#endif

    }
    else
    {
        return false;
    }


    if( AI_SUCCESS == aiGetMaterialColor( assimpMaterial, AI_MATKEY_COLOR_SPECULAR, &specular) )
    {
        memcpy( &outNativeMaterial.m_specular, &specular, sizeof(CColor) );
    }
    else
    {
        return false;
    }


    unsigned int max;
    aiGetMaterialFloatArray( assimpMaterial, AI_MATKEY_SHININESS, &outNativeMaterial.m_shininess, &max);

    //opacity of the material;
    outNativeMaterial.m_opacity = 1.f;
    aiGetMaterialFloatArray(assimpMaterial, AI_MATKEY_OPACITY, &outNativeMaterial.m_opacity, &max);

    return true;
}

EMeshPrimitive CSceneAssimpConverter::GetMeshPrimitive( const aiFace* assimpFace )
{
    switch ( assimpFace->mNumIndices)
    {
        case 1:
            return EMeshPrimitive::E_MESH_PRIMITIVE_POINTS;
        break;

        case 2:
            return EMeshPrimitive::E_MESH_PRIMITIVE_LINES;
        break;

        case 3:
            return EMeshPrimitive::E_MESH_PRIMITIVE_TRIANGLES;
        break;



        default:
            return EMeshPrimitive::E_MESH_PRIMITIVE_NONE;
        break;
    }
}


Bool CSceneAssimpConverter::ValidateVerticesAnimation( const thVector<RenderLowLevel::SVertex_PNTB4>& vertices )
{

    for( u64 i=0; i<vertices.Size(); i++ )
    {
        //THOT_TRACE_LINE("%s", vertices[i].ToString().GetBuffer());
        if( ! (vertices[i].WeightsAreOk()) )
        {
            return false;
        }
    }


    return true;
}


Bool CSceneAssimpConverter::FindAssimpNodeByName( const CString& nodeName, aiNode*& outAssimpNode )
{
    outAssimpNode = NULL;
    if( !m_assimpScene )
    {
        return false;
    }

    if( !FindNodeByNameRecursive( m_assimpScene->mRootNode, nodeName, outAssimpNode ) )
    {
        return false;
    }

    return true;
}

Bool CSceneAssimpConverter::FindNodeByNameRecursive( const aiNode* assimpNode, const CString& nodeName, aiNode*& outAssimpNode )
{
    if( !assimpNode )
    {
        return false;
    }

    if( nodeName == assimpNode->mName.C_Str() )
    {
        outAssimpNode = const_cast<aiNode*>(assimpNode);
        return true;
    }

    for( u32 i=0; i<assimpNode->mNumChildren; i++ )
    {
        if( FindNodeByNameRecursive( assimpNode->mChildren[i], nodeName, outAssimpNode ) )
        {
            return true;
        }
    }

    return false;
}

Bool CSceneAssimpConverter::AssimpNodeIsBone( const aiNode* assimpNode )
{
    if( !m_assimpScene || !assimpNode )
    {
        return false;
    }

    // search in all animations;
    CString nodeName;
    for(u32 i=0; i<m_assimpScene->mNumAnimations; i++)
    {
        aiAnimation* assimpAnimation = m_assimpScene->mAnimations[i];
        
        //search all bones;
        for( u32 i=0; i<assimpAnimation->mNumChannels; i++  )
        {
            aiNodeAnim* assimpNodeAnim = assimpAnimation->mChannels[i];
            nodeName = assimpNodeAnim->mNodeName.C_Str();
            if( nodeName == assimpNode->mName.C_Str() )
            {
#ifdef _DEBUG
                for( u32 i=0; i<assimpNodeAnim->mNumRotationKeys; i++ )
                {
                    aiQuaternion assimpQuat = assimpNodeAnim->mRotationKeys[i].mValue;
                    if( !DbgVerifyQuaternion(assimpQuat) )
                    {
                        THOT_ASSERT(false, "Failed to convert from assimp to native quaternion");
                    }

                    if( i>0)
                    {
                        aiQuaternion assimpQuat2 = assimpNodeAnim->mRotationKeys[i-1].mValue;
                        if ( !DbgVerifyQuaternionSlerp( assimpQuat, assimpQuat2 ) )
                        {
                           THOT_ASSERT(false, "Native quaternion slerp failed");
                        }
                    }

                }

                for( u32 i=0; i<assimpNodeAnim->mNumScalingKeys; i++ )
                {
                    tVect3* scale = (tVect3*)( &(assimpNodeAnim->mScalingKeys[i].mValue) );
                    if( !fequals(scale->x, 1.f) || !fequals(scale->y, 1.f) || !fequals(scale->z, 1.f) )
                    {
                        THOT_ASSERT(false, "anim node has scale" );  
                    }
                }
#endif /*_DEBUG*/



                return true;
            }

        }
    }

    // 
    return false;
}


Bool CSceneAssimpConverter::CreateAnimations( )
{

    if( !m_assimpScene || !m_assimpScene->HasAnimations()  )
    {
        return false;
    }

    Bool bSucces = true;

    for(u32 i=0; i<m_assimpScene->mNumAnimations; i++)
    {
        aiAnimation* assimpAnimation = m_assimpScene->mAnimations[i];
        CSkeleton* skeleton = CreateAnimation( assimpAnimation );

        if( !skeleton )
        {
            TRACE_CONVERTER( "failed to create skeleton" );
            bSucces = false;
        }
        else // [TODO]: temp hack; to be removed after testing skeletons
        {
            m_skeleton = skeleton;
            return true;
        }
    }

    return bSucces;
}

CSkeleton* CSceneAssimpConverter::CreateAnimation( const aiAnimation* assimpAnimation )
{
    if( !m_assimpScene || !assimpAnimation )
    {
        return NULL;
    }

    thVector<aiNode*> bones;
    bones.Resize(assimpAnimation->mNumChannels);

    thVector<CBone*> nativeBones;
    nativeBones.Resize( assimpAnimation->mNumChannels );

    for( u32 i=0; i<assimpAnimation->mNumChannels; i++)
    {
        aiNodeAnim* assimpNodeAnim = assimpAnimation->mChannels[i];
        CString nodeName = assimpNodeAnim->mNodeName.C_Str();
        aiNode* pNode = NULL;
        
        // find node in the scene
        if( !FindAssimpNodeByName( nodeName, pNode ) )
        {
            TRACE_CONVERTER("FAIL TO FIND CORESPONDING NODE [%s] IN SCENE", nodeName.GetBuffer());
            return NULL;
        }


        CBone* bone = CreateBone( assimpAnimation, assimpNodeAnim );
        nativeBones[i] = bone;

        bones[i] = (pNode);
    }

    THOT_ASSERT( nativeBones.Size() == bones.Size() );

    aiNode* rootNode = NULL;
    if( !GetRootBone( bones, rootNode ) )
    {
        return NULL;
    }

    CSkeleton* skeleton = CreateSkeleton( nativeBones, bones, rootNode );


    return skeleton;
}


CSkeleton* CSceneAssimpConverter::CreateSkeleton( thVector<CBone*>& nativeBones, const thVector<aiNode*>& assimpNodes, const aiNode* assimpRootNode)
{
    THOT_ASSERT( nativeBones.Size() == assimpNodes.Size(), "native bones count is different from assimp bone count" );
    THOT_ASSERT( assimpRootNode, "assimp root node must not be null" );

    for( u64 i=0; i<assimpNodes.Size(); i++ )
    {
        const aiNode* assimpNode = assimpNodes[i];
        CString boneName = assimpNode->mName.C_Str();

        CBone* nativeBone = FindByName( nativeBones, boneName );
        THOT_ASSERT(nativeBone);
        
        // set res pos from default assimp node transformation
        m4x4 boneResPos = i4x4; GetLocalTM( assimpNode, boneResPos );
        nativeBone->m_defaultLocalPos = boneResPos;

        // set parent node
        if( assimpNode != assimpRootNode )
        {
            CBone* parentBone = FindByName( nativeBones, assimpNode->mParent->mName.C_Str() );
            THOT_ASSERT(parentBone);
            nativeBone->SetParent(parentBone);
        }
        else
        {
            nativeBone->m_parent = NULL;
        }

        // set childs
        for( u32 childIdx=0; childIdx<assimpNode->mNumChildren; childIdx++ )
        {
            aiNode* assimpChild = assimpNode->mChildren[childIdx];

            CBone* nativeChildBone = FindByName( nativeBones, assimpChild->mName.C_Str() );
            THOT_ASSERT(nativeChildBone);

            nativeBone->AddChild( nativeChildBone );
        }
    }


    //create skeleton
    CSkeleton* skeleton = THOT_NEW CSkeleton;
   
    // set root;
    CBone* nativeRootBone = FindByName(nativeBones, assimpRootNode->mName.C_Str() );
    THOT_ASSERT(nativeRootBone);
    skeleton->m_rootBone = nativeRootBone;

    // set bone data;
    skeleton->m_bones.StoleData( nativeBones );
    skeleton->m_boneMatrices.Resize( skeleton->GetBoneCount() );
    skeleton->ComputeBonesDefaultInvMat();

    // set bone indexes;
    for( u32 i=0; i<skeleton->GetBoneCount(); i++ )
    {
        CBone* bone = skeleton->GetBone(i);
        bone->m_boneIdx = i;
    }

    return skeleton;
}


CBone* CSceneAssimpConverter::FindByName(thVector<CBone*>& nativeBones, const CString& name )
{
    for( u64 i=0; i<nativeBones.Size(); i++ )
    {
        if( nativeBones[i]->GetName() == name )
        {
            return nativeBones[i];
        }
    }

    return NULL;
}

CBone* CSceneAssimpConverter::CreateBone( const aiAnimation* assimpAnimation, const aiNodeAnim* assimpNodeAnim )
{
    if( !m_assimpScene || !assimpNodeAnim || !assimpAnimation )
    {
        return NULL;
    }
    
    float fAnimTime = (float)assimpAnimation->mDuration;

    // create bone and set the name
    CBone* bone = THOT_NEW CBone;
    THOT_ASSERT( assimpNodeAnim->mNodeName.C_Str(), "animation name must not be null" );
    bone->SetName( assimpNodeAnim->mNodeName.C_Str() );

    // create bone track for this animation;
    CBoneTrack* boneTrack = THOT_NEW CBoneTrack;

    //set position track;
    for( u32 i=0; i<assimpNodeAnim->mNumPositionKeys; i++ )
    {
        CPositionKeyFrame nativePosKey;

        const aiVectorKey& assimpPosKey = assimpNodeAnim->mPositionKeys[i];
        nativePosKey.m_fTimeRatio = (float)assimpPosKey.mTime / fAnimTime;
        THOT_ASSERT( nativePosKey.m_fTimeRatio>=0.f && nativePosKey.m_fTimeRatio<=1.f, "bone track ratio time should be between 0 and 1 but the value is: [%f]", nativePosKey.m_fTimeRatio );

        nativePosKey.m_position = *((tVect3*)(&assimpPosKey.mValue));

        boneTrack->AddKeyFrame( nativePosKey);
    }

    //set rotation track
    for( u32 i=0; i<assimpNodeAnim->mNumRotationKeys; i++ )
    {
        CRotationKeyFrame nativeRotKey;

        const aiQuatKey& assimpRotKey =  assimpNodeAnim->mRotationKeys[i];

        nativeRotKey.m_fTimeRatio = (float)(assimpRotKey.mTime/fAnimTime);
        nativeRotKey.m_rotation = *((tQuat*)( &assimpRotKey.mValue ));
    
        THOT_ASSERT( IsUnit( nativeRotKey.m_rotation, 0.0001f ), "quaternion must be unit" );
        //normalize the quat just to be sure;
        QuatNor(nativeRotKey.m_rotation);

        boneTrack->AddKeyFrame( nativeRotKey );
    }

    THOT_ASSERT( boneTrack->m_positionKeys.Size() > 0 && boneTrack->m_rotationsKeys.Size() > 0, "bone track must not have null key frames" );
    bone->AddBoneTrack( boneTrack );

#ifdef _DEBUG
    for( u32 i=0; i<assimpNodeAnim->mNumScalingKeys; i++ )
    {
        const aiVectorKey& assimpScaleKey = assimpNodeAnim->mScalingKeys[i];
        tVect3 scaleVector = *((tVect3*)(&assimpScaleKey.mValue));
        if( !fequals(scaleVector.x, 1.f) || !fequals(scaleVector.y, 1.f) || !fequals(scaleVector.z, 1.f) )
        {
            THOT_ASSERT(false, "scale must be 1");
        }

    }
#endif /*_DEBUG*/


    return bone;
}



Bool CSceneAssimpConverter::GetRootBone( const thVector<aiNode*>& nodeList, aiNode*& outRootNode )
{
    outRootNode = NULL;


    for( u64 i=0; i<nodeList.Size(); i++ )
    {
        if( IsRootBone( nodeList[i], nodeList ) )
        {
            outRootNode = nodeList[i];
            return true;
        }
    }

    return false;
}

Bool CSceneAssimpConverter::IsRootBone( const aiNode* assimpNode, const thVector<aiNode*>& assimpBoneNodes)
{
    if( !assimpNode || assimpBoneNodes.Size()==0 )
    {
        return false;
    }

    for( u64 i=0; i<assimpBoneNodes.Size(); i++ )
    {
        if( assimpBoneNodes[i] == assimpNode )
            continue;

        CString name = assimpBoneNodes[i]->mName.C_Str();

        aiNode* outDummy = NULL;
        if( !FindNodeByNameRecursive( assimpNode, name, outDummy  ) )
        {
            return false;
        }

    }

    // here we found all nodes in list
    u32 subtreeCount = GetSubtreeChildCount(assimpNode);
    if( subtreeCount != assimpBoneNodes.Size()-1 )
    {
        //THOT_ASSERT(false, "found all bones but the root has something more..." );
        return false;
    }


    return true;
}

u32 CSceneAssimpConverter::GetSubtreeChildCount( const aiNode* assimpNode )
{
    if( !assimpNode )
    {
        return 0;
    }

    u32 childCount = assimpNode->mNumChildren;

    for( u32 i=0; i<assimpNode->mNumChildren; i++ )
    {
        childCount += GetSubtreeChildCount( assimpNode->mChildren[i] );
    }

    return childCount;
}

Bool CSceneAssimpConverter::DbgVerifyQuaternion( const aiQuaternion& assimpQuat )
{

    aiMatrix3x3 assimpMat3 =  assimpQuat.GetMatrix();
    assimpMat3.Transpose();

    m3x3* mat3 = (m3x3*)(&assimpMat3);

    tQuat* nativeQuat = (tQuat*)(&assimpQuat);
    
    m4x4 nativeMat4;
    MakeMatFromQuat( *nativeQuat, nativeMat4);

    if( ! (AXEX(nativeMat4).Equals) ( AXEX(*mat3) ) ||
        ! (AXEY(nativeMat4).Equals) ( AXEY(*mat3) ) ||
        ! (AXEZ(nativeMat4).Equals) ( AXEZ(*mat3) )
        )
    {
        return false;
    }

    return true;
}

Bool CSceneAssimpConverter::DbgVerifyQuaternionSlerp( const aiQuaternion& assimpQuat1, const aiQuaternion& assimpQuat2)
{
    tQuat* nativeQuat1 = (tQuat*)(&assimpQuat1);
    tQuat* nativeQuat2 = (tQuat*)(&assimpQuat2);
    
    float fLenght = (*nativeQuat1).Lenght();
    if( !fequals( fLenght, 1.f, 0.0001f ) )
    {
        THOT_ASSERT(false);
    }

    for( float t =0.f; t<=1.f; t+=0.1f )
    {
        tQuat nativeSlerp;
        Slerp( *nativeQuat1, *nativeQuat2, t, nativeSlerp );

        aiQuaternion assimpSlerp;



        aiQuaternion::Interpolate( assimpSlerp, assimpQuat1, assimpQuat2, t );

        tQuat* quat = (tQuat*)(&assimpSlerp);

        for( u32 i=0; i<4; i++ )
        {
            if( !fequals( nativeSlerp.q[i], quat->q[i] ) )
            {
                return false;
            }
        }
    }


    return true;
}

Bool CSceneAssimpConverter::GetWorldTM  ( const aiNode* assimpNode, m4x4& out )
{
    if( !assimpNode)
    {
        return false;
    }

    // local TM
    m4x4 localTM;
    GetLocalTM( assimpNode, localTM );

    //get parent world TM;
    m4x4 parentWorldTM = i4x4;
    const aiNode* parent = assimpNode->mParent;
    if( parent )
    {
        GetWorldTM( parent, parentWorldTM );
    }

    // world TM
    out = localTM * parentWorldTM;

    return true;
}

Bool CSceneAssimpConverter::GetLocalTM  ( const aiNode* assimpNode, m4x4& out )
{
    if( !assimpNode )
    {
        return false;
    }
    
    //aiMatrix4x4& transpose =  ((aiNode*)assimpNode)->mTransformation.Transpose();
    m4x4 mat = *((m4x4*)(& ((aiNode*)assimpNode)->mTransformation));
    m4x4 transpose = Transpose(mat);

    out = *((m4x4*) &transpose );

    return true;
}


Bool CSceneAssimpConverter::SetLocalTM(aiNode* assimpNode, const m4x4& TM)
{
    if( !assimpNode)
    {
        return false;
    }

    m4x4 transpose = Transpose(TM);

    assimpNode->mTransformation = *((aiMatrix4x4*)(&transpose));
    return true;
}