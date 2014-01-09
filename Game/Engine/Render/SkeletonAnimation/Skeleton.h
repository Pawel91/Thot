#pragma once
#ifndef __RENDER_SKELETON_H__
#define __RENDER_SKELETON_H__

#include "Bone.h"


#ifdef THOT_ENABLE_DEBUG
#   define DEBUG_BONE_UPDATE 
//#   define DEBUG_SKINNING
#endif /*_DEBUG*/

class  CSkeleton
{
    friend class CSceneAssimpConverter;
//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
    RENDER_API  CSkeleton();
    RENDER_API  ~CSkeleton();


//*********************************************
//            INTERFACE
//*********************************************
public:
    typedef thVector<CBone*>     TBoneArray;
    typedef thVector<m4x4>       TMatrixArray;

    RENDER_API void                         Update              ( float fDeltaTime );

    RENDER_API  const TBoneArray&           GetBones            ( )const;
    RENDER_API  TBoneArray&                 GetBones            ( );
    RENDER_API  const CBone*                GetRootBone         ( )const;
    RENDER_API  CBone*                      GetRootBone         ( );
    RENDER_API  void                        BuildBoneMatrices   ( u32 animationIdx, float fTimeRatio );

    RENDER_API  const TMatrixArray&         GetBoneMatrices     ( )const;

    RENDER_API  CBone*                      GetBone             ( u32 index );
    RENDER_API  CBone*                      GetBone             ( const CString& name );
    RENDER_API  u32                         GetBoneCount        ( );

    RENDER_API  CBone*                      GetBoneByName       ( const CString& boneName );
    RENDER_API  const CBone*                GetBoneByName       ( const CString& boneName )const;
   
    RENDER_API  void                        ComputeBonesDefaultInvMat();


//*********************************************
//            HELPERS
//*********************************************
protected:
    void    BuildBoneMatrices_Recursive     ( u32 animationIdx, float fTimeRatio, const CBone* parent, const m4x4& mTM );

//*********************************************
//            MEMBERS
//*********************************************
protected:
    CBone*                  m_rootBone;
    TBoneArray              m_bones;
    mutable TMatrixArray    m_boneMatrices;

    
#ifdef DEBUG_BONE_UPDATE
    float m_timeRatio;
    thVector<Bool>           m_updatedBoneIndexes;
    void DbgReset()
    { 
        THOT_ASSERT( m_boneMatrices.Size() == m_bones.Size() );
        m_updatedBoneIndexes.Resize( m_boneMatrices.Size() );
        for(u64 i=0; i<m_updatedBoneIndexes.Size(); i++)
        {
            m_updatedBoneIndexes[i]=false;
        }
    }
    Bool                    DbgAllAreUpdated()
    {
        for(u64 i=0; i<m_updatedBoneIndexes.Size(); i++)
        if( !m_updatedBoneIndexes[i])
        {
           return false; 
        }
        return true;
    }
#endif /*DEBUG_BONE_UPDATE*/
};





#endif /*__RENDER_SKELETON_H__*/