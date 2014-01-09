#include "Render_PCH.h"
#include "Bone.h"
#include "BoneTrack.h"

#ifndef DECLARE_DEFAULT_CONSTRUCTOR_LIST
#   define DECLARE_DEFAULT_CONSTRUCTOR_LIST \
    :m_parent               (NULL)\
    ,m_invDefaultModelTM    (i4x4)\
    ,m_boneIdx              ( 0xFFFFFFFF )\
    ,m_defaultLocalPos      ( i4x4 )
    
#else
#   error DECLARE_DEFAULT_CONSTRUCTOR_LIST allready defined
#endif DECLARE_DEFAULT_CONSTRUCTOR_LIST

 CBone::CBone()
     DECLARE_DEFAULT_CONSTRUCTOR_LIST
 {
 }

CBone::~CBone()
{

    for( u64 i=0; i<m_childs.Size(); i++ )
    {
        THOT_ASSERT(m_childs[i]);
        THOT_DELETE(m_childs[i]);
    }

    for( u64 i=0; i<m_animations.Size(); i++ )
    {
        THOT_ASSERT(m_animations[i]);
        THOT_DELETE(m_animations[i]);

    }
}


#undef DECLARE_DEFAULT_CONSTRUCTOR_LIST

CString& CBone::GetName(  )
{
    return m_name;
}

const CString& CBone::GetName(  )const
{
    return m_name;
}

const CBone* CBone::GetParent( )const
{
    return m_parent;
}

CBone*  CBone::GetParent( )
{
    return m_parent;
}

const CBone* CBone::GetChild ( u32 index )const
{
    return m_childs[index];
}

CBone* CBone::GetChild ( u32 index )
{
    return m_childs[index];
}

const CBone::TBoneArray& CBone::GetChilds( )const
{
    return m_childs;
}

CBone::TBoneArray&  CBone::GetChilds( )
{
    return m_childs;
}

u32 CBone::GetChildCount( )const
{
    return (u32)m_childs.Size();
}

void CBone::GetDefaultLocalTM( m4x4& outTM )const
{
    outTM = m_defaultLocalPos;
}

void CBone::GetDefaultModelTM( m4x4& outDefModelTM )const
{
    m4x4 localTM;
    GetDefaultLocalTM( localTM);

    //get parent world TM;
    m4x4 parentModelTM = i4x4;
    if( m_parent )
    {
        m_parent->GetDefaultModelTM( parentModelTM);
    }

    outDefModelTM = localTM * parentModelTM;
}


void CBone::GetModelTM( u32 animationIdx, float fTimeRatio, m4x4& outModelTM )const
{
    THOT_ASSERT( fTimeRatio>=0.f && fTimeRatio<=1.f );
       // local TM
    m4x4 localTM;
    GetLocalTM( animationIdx, fTimeRatio, localTM);

    //get parent world TM;
    m4x4 parentModelTM = i4x4;
   
    if( m_parent )
    {
        m_parent->GetModelTM( animationIdx, fTimeRatio, parentModelTM);
    }

    outModelTM = localTM * parentModelTM;
}

void CBone::GetLocalTM( u32 animationIdx, float fTimeRatio, m4x4& outLocalTM )const
{
    THOT_ASSERT( fTimeRatio>=0.f && fTimeRatio<=1.f );

    const CBoneTrack* boneTrack = m_animations[animationIdx];
    boneTrack->GetMatrixFromTime( fTimeRatio, outLocalTM );
}


void CBone::GetBoneAndLocalMatrix ( u32 animationIdx, float fTimeRatio, const m4x4&  parentModelMatrix, m4x4& outBoneMatrix, m4x4& outLocalMatrix)const
{
    THOT_ASSERT( animationIdx < m_animations.Size() );
    THOT_ASSERT( fTimeRatio >=0.f && fTimeRatio<=1.f );

    const CBoneTrack* boneTrack = m_animations[animationIdx];
    boneTrack->GetMatrixFromTime( fTimeRatio, outLocalMatrix );

    outBoneMatrix = m_invDefaultModelTM * outLocalMatrix * parentModelMatrix;

    THOT_ASSERT( IsOrtho(outBoneMatrix) );
}

void CBone::SetName( const CString& name )
{
    m_name = name;
}

u32 CBone::AddBoneTrack( CBoneTrack* boneTrack )
{
    return (u32)m_animations.PushBack( boneTrack );
}

void CBone::SetParent( CBone* parent )
{
    m_parent = parent;
}

u32 CBone::AddChild( CBone* child )
{
    THOT_ASSERT(child, "cannot add a null child");

    return (u32)m_childs.PushBack(child);
}