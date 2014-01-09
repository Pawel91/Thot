#pragma once
#ifndef __RENDER_BONE_KEY_FRAME_H__
#define __RENDER_BONE_KEY_FRAME_H__


class CKeyFrameBase
{
public:
    CKeyFrameBase( float fTimeRatio )
        :m_fTimeRatio( fTimeRatio )
    {}

    float m_fTimeRatio;
};


class CPositionKeyFrame: public CKeyFrameBase
{
public:
    typedef CKeyFrameBase super;

    CPositionKeyFrame()
        :super      ( 0.f )
        ,m_position (nullVect)
    {}

    CPositionKeyFrame( float fTimeRatio, const tVect3& pos)
        : super         (fTimeRatio)
        ,m_position     ( pos )
    {}

    tVect3          m_position;
};


class CRotationKeyFrame:public CKeyFrameBase
{
public:
    typedef CKeyFrameBase super;
    
    CRotationKeyFrame()
        :super      ( 0.f )
        ,m_rotation ( nullRot )
    {}
            

    CRotationKeyFrame( float fTimeRatio, const tQuat& quat )
        : super     ( fTimeRatio )
        , m_rotation ( quat )
    {}

    tQuat           m_rotation;
};



#endif /*__RENDER_BONE_KEY_FRAME_H__*/