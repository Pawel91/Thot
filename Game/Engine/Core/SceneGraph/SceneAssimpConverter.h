#pragma once
#ifndef __RENDER_ASSIMP_CONVERTER_H__
#define __RENDER_ASSIMP_CONVERTER_H__

#include "SceneGraph.h"
#include "Render/Mesh/MeshTypes.h"
#include "Render/Buffers/Vertex.h"

#include "assimp\quaternion.h"

class IMesh;
class CMaterial;
class CBone;
class CSkeleton;

// assimp forword declares
struct aiScene;
struct aiNodeAnim;
struct aiNode;
struct aiFace;
struct aiAnimation;
struct aiNodeAnim;
struct aiMaterial;
struct aiMesh;


class CORE_API CSceneAssimpConverter
{
public:

    CSceneAssimpConverter( const aiScene* assimpScene );
    ~CSceneAssimpConverter( );

    CSceneGraph*            CreateScene         ( );


protected:

    void                    SetRootTransformToNull          ( );

    void                    CreateRecursive                 ( CSceneGraph* scene, ISceneNode* parent, const aiScene* assimpScene, const aiNode* assimpNode );
    ISceneNode*             CreateNode                      ( const aiNode* assimpNode );
    IMesh*                  CreateMesh                      ( const aiMesh* assimpMesh );
    
    Bool                    GetNativeMaterial               ( const aiMaterial* assimpMaterial, CMaterial& outNativeMaterial  );
    EMeshPrimitive          GetMeshPrimitive                ( const aiFace* assimpFace );
    Bool                    ValidateVerticesAnimation       ( const thVector<RenderLowLevel::SVertex_PNTB4>& vertices );
    Bool                    FindAssimpNodeByName            ( const CString& nodeName, aiNode*& outAssimpNode );
    Bool                    FindNodeByNameRecursive         ( const aiNode* assimpNode, const CString& nodeName, aiNode*& outAssimpNode );
    
    Bool                    AssimpNodeIsBone                ( const aiNode* assimpNode );
    
    // animation stuff
    Bool                    CreateAnimations                ( );
    CSkeleton*              CreateAnimation                 ( const aiAnimation* assimpAnimation ); // create a bone with a name and tracks
    CBone*                  CreateBone                      ( const aiAnimation* assimpAnimation, const aiNodeAnim* assimpNodeAnim  );
    CSkeleton*              CreateSkeleton                  ( thVector<CBone*>& nativeBones, const thVector<aiNode*>& assimpNodes, const aiNode* assimpRootNode);
    Bool                    GetRootBone                     ( const thVector<aiNode*>& nodeList, aiNode*& outRootNode );
    Bool                    IsRootBone                      ( const aiNode* assimpNode, const thVector<aiNode*>& assimpBoneNodes);
    CBone*                  FindByName                      ( thVector<CBone*>& nativeBones, const CString& name );
    u32                     GetSubtreeChildCount            ( const aiNode* assimpNode );
    Bool                    MoveSkeletonToModelSpace        ( );
    void                    RestoreDefaultSkel              ( );

    Bool                    GetWorldTM                      ( const aiNode* assimpNode, m4x4& out );
    Bool                    GetLocalTM                      ( const aiNode* assimpNode, m4x4& out );

    Bool                    DbgVerifyQuaternion             ( const aiQuaternion& assimpQuat);
    Bool                    DbgVerifyQuaternionSlerp        ( const aiQuaternion& assimpQuat1, const aiQuaternion& assimpQuat2);

    Bool                    SetLocalTM                      ( aiNode* assimpNode, const m4x4& TM );

//************************************
//          MEMBERS
//************************************
protected:
    const aiScene*      m_assimpScene;

    //TEMP.. [TODO] remove from here
    CSkeleton*          m_skeleton;
};


#endif /*__RENDER_ASSIMP_CONVERTER_H__*/