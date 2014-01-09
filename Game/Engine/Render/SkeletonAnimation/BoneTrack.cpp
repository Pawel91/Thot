#include "Render_PCH.h"
#include "BoneTrack.h"


CBoneTrack::CBoneTrack()
{

}

Bool CBoneTrack::AddKeyFrame( const CPositionKeyFrame& posKey )
{
    if( m_positionKeys.Size() == 0 )
    {
        if( posKey.m_fTimeRatio != 0.f )
        {
            return false;
        }
    }
    else if( posKey.m_fTimeRatio < m_positionKeys[m_positionKeys.Size()-1].m_fTimeRatio )
    {
        return false;
    }

    m_positionKeys.PushBack( posKey );

    return true;
}

Bool CBoneTrack::AddKeyFrame( const CRotationKeyFrame& rotKey )
{
    if( m_rotationsKeys.Size() == 0 )
    {
        if( rotKey.m_fTimeRatio != 0.f )
        {
            return false;
        }
    }
    else if( rotKey.m_fTimeRatio < m_rotationsKeys[ m_rotationsKeys.Size()-1 ].m_fTimeRatio )
    {
        return false;
    }

    THOT_ASSERT( IsUnit(rotKey.m_rotation, 0.0001f), "ERROR!!! Adding a non-normalized quaternion to bone track!. The lenght is [%f]", rotKey.m_rotation.Lenght() );
    
    CRotationKeyFrame normalizedRotKey = rotKey;
    QuatNor( normalizedRotKey.m_rotation );

    m_rotationsKeys.PushBack( normalizedRotKey );
    return true;
}

Bool CBoneTrack::AddKeyFrame(float fTime, const tVect3& position )
{
    CPositionKeyFrame posKey ( fTime, position );
    return AddKeyFrame(posKey);
}

Bool CBoneTrack::AddKeyFrame(float fTime, const tQuat& rotation )
{
    CRotationKeyFrame rotKey( fTime, rotation );
    return AddKeyFrame( rotKey );
}

