#include "Render_PCH.h"
#include "Skeleton.h"
#include "Kernel/Profiler/Profiler.h"
#include "Render/ShaderFramework/ShaderParameterProvider.h"


//------------------------------------------------------------------------------------------
class CSkeletonParameterProvider:public CShaderParameterProviderBase<CSkeletonParameterProvider>
{
public:
      CSkeletonParameterProvider(){}
     ~CSkeletonParameterProvider(){}

    static void CreateParameterMap();

    Bool            BuildFromSkeleton       ( const CSkeleton& skeleton );

private:
    CShaderParameter<m4x4, 124>     m_boneMatrices;
};

//------------------------------------------------------------------------------------------
void CSkeletonParameterProvider::CreateParameterMap()
{
    CSkeletonParameterProvider& parameterProvider = *((CSkeletonParameterProvider*)(0));

    SetProviderName( "CSkeletonParameterProvider" );

    AddParameter(  parameterProvider.m_boneMatrices, "uBoneMatrices" );
}

//------------------------------------------------------------------------------------------
Bool CSkeletonParameterProvider::BuildFromSkeleton( const CSkeleton& skeleton )
{
    const CSkeleton::TMatrixArray& boneMatrices =  skeleton.GetBoneMatrices();
    
    for( u64 i=0; i<boneMatrices.Size(); i++ )
    {
        m_boneMatrices[ThNumericCast<u32>(i)] = boneMatrices[i];
    }

    return true;
}

//------------------------------------------------------------------------------------------
#ifdef THOT_ENABLE_DEBUG

#define ASSERT_ON_TRACE

#ifndef TRACE_SCENE_ASSIMP_CONVERTER
#   ifndef ASSERT_ON_TRACE
#       define TRACE_SKEL(_format, ...) do{THOT_TRACE_LINE(_format, __VA_ARGS__)}while(false);
#else
#       define TRACE_SKEL(_format, ...) do{ THOT_TRACE_LINE(_format, __VA_ARGS__); THOT_ASSERT(0); }while(false)
#endif /*ASSERT_ON_TRACE*/
#   else
#       error TRACE_SKEL allready defined; change macro name to resolve conflict;
#   endif /*TRACE_SCENE_ASSIMP_CONVERTER*/
#else
#   define TRACE_SKEL(_format, ...)
#endif /*_DEBUG*/


#ifndef DECLARE_DEFAULT_CONSTRUCTOR_LIST
#define DECLARE_DEFAULT_CONSTRUCTOR_LIST    \
    :m_rootBone     (NULL)

#endif /*DECLARE_DEFAULT_CONSTRUCTOR_LIST*/




//------------------------------------------------------------------------------------------
CSkeleton::CSkeleton()
    DECLARE_DEFAULT_CONSTRUCTOR_LIST

#ifdef DEBUG_BONE_UPDATE
    ,m_timeRatio(0.f)
#endif 
{

}

//------------------------------------------------------------------------------------------
CSkeleton::~CSkeleton()
{
    if( m_rootBone )
    {
        THOT_DELETE(m_rootBone);
    }
}

#undef DECLARE_DEFAULT_CONSTRUCTOR_LIST

//------------------------------------------------------------------------------------------
const CSkeleton::TBoneArray& CSkeleton::GetBones()const
{
    return m_bones;
}

//------------------------------------------------------------------------------------------
CSkeleton::TBoneArray&  CSkeleton::GetBones()
{
    return m_bones;
}

//------------------------------------------------------------------------------------------
const CBone* CSkeleton::GetRootBone     ()const
{
    return m_rootBone;
}

//------------------------------------------------------------------------------------------
CBone*  CSkeleton::GetRootBone     ()
{
    return m_rootBone;
}

//------------------------------------------------------------------------------------------
void CSkeleton::Update( float fDeltaTime )
{
    DECLARE_PROFILE_SCOPED( "CSkeleton::Update" );

    static const float fAnimTime = 2.f;
    static float fCurrTime = 0.f;
    fCurrTime += fDeltaTime;
    if( fCurrTime > fAnimTime )
    {
        fCurrTime = fCurrTime - fAnimTime;
    }

    float fTimeRatio = fCurrTime/fAnimTime;

    BuildBoneMatrices( 0, fTimeRatio );

#ifdef DEBUG_BONE_UPDATE
    m_timeRatio = fTimeRatio;
#endif

}

//------------------------------------------------------------------------------------------
void CSkeleton::BuildBoneMatrices( u32 animationIdx, float fTimeRatio )
{
    if( !m_rootBone )
    {
        TRACE_SKEL("ROOT BONE NOT FOUND");
        return;
    }

#ifdef DEBUG_BONE_UPDATE
    DbgReset();
    m_updatedBoneIndexes[m_rootBone->m_boneIdx] = true;
#endif /*DEBUG_BONE_UPDATE*/

    //update root matrix;
    m4x4 rootLocalMatrix;
    m_rootBone->GetBoneAndLocalMatrix( animationIdx, fTimeRatio, i4x4, m_boneMatrices[ m_rootBone->m_boneIdx], rootLocalMatrix );
    BuildBoneMatrices_Recursive( animationIdx, fTimeRatio, m_rootBone, rootLocalMatrix);


#ifdef DEBUG_BONE_UPDATE
    THOT_ASSERT( DbgAllAreUpdated() );
    for( u64 i=0; i<m_bones.Size(); i++ )
    {
        m4x4 outModelTM;
        m_bones[i]->GetModelTM( animationIdx, fTimeRatio, outModelTM );
        m4x4 boneTM = m_bones[i]->m_invDefaultModelTM * outModelTM;
        THOT_ASSERT( MatEquals( boneTM, m_boneMatrices[i]), "fail to build bone matrices" );
    }
#endif /*DEBUG_BONE_UPDATE*/
};

//------------------------------------------------------------------------------------------
void CSkeleton::BuildBoneMatrices_Recursive ( u32 animationIdx, float fTimeRatio, const CBone* parent, const m4x4& TM )
{
    THOT_ASSERT(IsOrtho(TM));
    
    u32 childCount = parent->GetChildCount();
    for( u32 i=0; i<childCount; i++ )
    {
        const CBone* childBone = parent->GetChild(i);
       
        THOT_ASSERT(childBone->m_boneIdx < m_boneMatrices.Size());

#ifdef DEBUG_BONE_UPDATE
        THOT_ASSERT( m_updatedBoneIndexes[childBone->m_boneIdx] == false );
        m_updatedBoneIndexes[childBone->m_boneIdx] = true;
#endif /*DEBUG_BONE_UPDATE*/


        m4x4 childTM;
        childBone->GetBoneAndLocalMatrix( animationIdx, fTimeRatio, TM, m_boneMatrices[ childBone->m_boneIdx], childTM );

        childTM*= TM;
        THOT_ASSERT(IsOrtho(childTM));

        BuildBoneMatrices_Recursive( animationIdx, fTimeRatio, childBone, childTM );

    }

}

//------------------------------------------------------------------------------------------
const CSkeleton::TMatrixArray& CSkeleton::GetBoneMatrices()const
{
    return m_boneMatrices;
}

//------------------------------------------------------------------------------------------
CBone*  CSkeleton::GetBone( u32 index )
{
    THOT_ASSERT( index < m_bones.Size() );

    return m_bones[index];
}

//------------------------------------------------------------------------------------------
CBone*  CSkeleton::GetBone( const CString& name )
{
    THOT_ASSERT(false);
    return NULL;
}

//------------------------------------------------------------------------------------------
u32 CSkeleton::GetBoneCount()
{
    return (u32)m_bones.Size();
}

//------------------------------------------------------------------------------------------
CBone* CSkeleton::GetBoneByName ( const CString& boneName )
{
    for( u64 i=0; i<m_bones.Size(); i++ )
    {
        if( m_bones[i]->GetName() == boneName )
        {
            return m_bones[i];
        }
    }

    return NULL; // not found
}

//------------------------------------------------------------------------------------------
const CBone* CSkeleton::GetBoneByName( const CString& boneName )const
{

    return const_cast<CSkeleton*>(this)->GetBoneByName(boneName);
}

//------------------------------------------------------------------------------------------
void CSkeleton::ComputeBonesDefaultInvMat()
{
    for( u32 i=0; i<m_bones.Size(); i++ )
    {
        CBone* bone = m_bones[i];
        m4x4 defaultModelTM = i4x4;
        bone->GetDefaultModelTM( defaultModelTM );

        InvMat( defaultModelTM, bone->m_invDefaultModelTM );
    }
}

