#ifndef __RENDER_BONE_TRACK_H__
#define __RENDER_BONE_TRACK_H__

#include "BoneKeyFrame.h"
#include "Kernel/DataStructures/Array/Vector.h"
#include "MathCore/MathUtils.h"

class CBoneTrack
{
    THOT_DECLARE_NOCOPY_CLASS(CBoneTrack);

public:
    RENDER_API CBoneTrack();

    thVector<CPositionKeyFrame>      m_positionKeys;
    thVector<CRotationKeyFrame>      m_rotationsKeys;

    RENDER_API void        GetMatrixFromTime   ( float fTimeRatio, m4x4& outMatrix )const;
    RENDER_API Bool        AddKeyFrame         ( const CPositionKeyFrame& posKey );
    RENDER_API Bool        AddKeyFrame         ( const CRotationKeyFrame& rotKey );

    RENDER_API Bool        AddKeyFrame         (float fTime, const tVect3& position );
    RENDER_API Bool        AddKeyFrame         (float fTime, const tQuat& rotation );


protected:
        void        GetRotation         ( float fTimeRatio, tQuat& outRot )const;
        void        GetPosition         ( float fTimeRatio, tVect3& outPos )const;

static  void        BuildMatrix         ( const tQuat& rotation, const tVect3& position, m4x4& outRotation );
};


THOT_FORCE_INLINE void CBoneTrack::GetRotation( float fTimeRatio, tQuat& outRot )const
{
    THOT_ASSERT( fTimeRatio >=0.f && fTimeRatio<=1.f, "time ratio should be between 0 and 1");

    if( m_rotationsKeys.Size() == 1 )
    {
        outRot = m_rotationsKeys[0].m_rotation;
        return;
    }

    float currentTimeRatio = 0.f;
    float nextTimeRatio = 0.f;
    for( u64 i=0; i<m_rotationsKeys.Size()-1; i++ )
    {
        currentTimeRatio = m_rotationsKeys[i].m_fTimeRatio;
        nextTimeRatio = m_rotationsKeys[i+1].m_fTimeRatio;
        if( fTimeRatio >= currentTimeRatio && fTimeRatio <= nextTimeRatio )
        {
            float t = MathUtils::GetRatio(fTimeRatio, currentTimeRatio, nextTimeRatio );
            Slerp( m_rotationsKeys[i].m_rotation, m_rotationsKeys[i+1].m_rotation, t, outRot );

            THOT_ASSERT(IsUnit(outRot, 0.001f), "ERROR!!! QUATERNIONS MUST BE UNIT. BUT THE LENGHT IS [%f]", outRot.Lenght() );
            QuatNor(outRot);

            //outRot = m_rotationsKeys[i].m_rotation;
            return;
        }
    }

    THOT_ASSERT(false,"ERROR!!! CANNOT FOUND ROTATION FOR CURRENT TIME. VERIFY BONE KEY FRAMES");
}

THOT_FORCE_INLINE void CBoneTrack::GetPosition( float fTimeRatio, tVect3& outPos )const
{
    THOT_ASSERT( fTimeRatio >=0.f && fTimeRatio<=1.f, "time ratio should be between 0 and 1");
    
    // TODO: make a binary search in the array of key frames
    // TODO: interpolate between key frames;

    if( m_positionKeys.Size() == 1)
    {
        outPos = m_positionKeys[0].m_position;
        return;
    }

    for( u64 i=0; i<m_positionKeys.Size()-1; i++ )
    {
        if( fTimeRatio >= m_positionKeys[i].m_fTimeRatio && fTimeRatio <= m_positionKeys[i+1].m_fTimeRatio )
        {
            float t = MathUtils::GetRatio( fTimeRatio, m_positionKeys[i].m_fTimeRatio, m_positionKeys[i+1].m_fTimeRatio );
            outPos = Lerp( m_positionKeys[i].m_position, m_positionKeys[i+1].m_position, t );
            return;
        }
    }

    THOT_ASSERT(false," cannot found position for current time. verify bone key frames");
}

THOT_FORCE_INLINE void CBoneTrack::BuildMatrix( const tQuat& rotation, const tVect3& position, m4x4& outRotation )
{
    MakeMatFromQuat( rotation, outRotation);
    POS(outRotation) = position;
}


THOT_FORCE_INLINE void CBoneTrack::GetMatrixFromTime( float fTimeRatio, m4x4& outMatrix )const
{
    THOT_ASSERT( fTimeRatio >=0.f && fTimeRatio<=1.f, "time ratio should be between 0 and 1");

    tQuat rotation; tVect3 position;
    GetPosition( fTimeRatio, position );
    GetRotation( fTimeRatio, rotation );

    BuildMatrix( rotation, position, outMatrix );
};


#endif /*__RENDER_BONE_TRACK_H__*/