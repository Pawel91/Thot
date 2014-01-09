#ifndef __RENDER_BONE_STATE_H__
#define __RENDER_BONE_STATE_H__

#include "MathCore/Vector/Vector.h"
#include "MathCore/Quaternion/Quat.h"

class CBoneKeyFrame
{
public:

    float           m_fTimeRatio;
    tVect3          m_position;
    tQuat           m_rotation;

    void            GetMatrix( m4x4& outMatrix )const;

};



THOT_FORCE_INLINE void CBoneKeyFrame::GetMatrix( m4x4& outMatrix )const
{
    THOT_ASSERT(IsUnit( m_rotation));
    MakeMatFromQuat(m_rotation, outMatrix);
    POS(outMatrix) = m_position;
}


#endif /*__RENDER_BONE_STATE_H__*/