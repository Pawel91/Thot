#pragma once
#ifndef __QUAT_H__
#define __QUAT_H__

//#include "MathCore\MathCoreDef.h"
#include "MathCore\Matrix\Matrix.h"

struct MATHCORE_API tQuat
{
    tQuat   ( );
    tQuat   ( float _w, float _x, float _y, float _z);
    tQuat   ( float _w, const tVect3& v );
    tQuat   ( const tVect3& axis, float alpha );
    tQuat   ( const tQuat& other );
    ~tQuat  ( ){}

    union
    {
        float    q[4];
        struct
        {
            float w, x, y, z;
        };
    };

inline      float           Lenght              ( )const;
inline      tQuat           GetConjugate        ( )const;
inline      tVect3&         GetVectorPart       ( );
inline      const tVect3&   GetVectorPart       ( )const;
inline      void            Conjugate           ( );
inline      void            Normalize           ( );
inline      void            GetRotAxis          ( tVect3& out )const;
inline      tVect3          GetRotAxis          ( )const;
inline      float           GetRotAngle         ( )const;


inline      Bool            operator==          ( const tQuat& other )const;
inline      tQuat           operator*           ( const tQuat& other )const; // cross product
inline      tQuat           operator*           ( const tVect3& v )const;
inline      tQuat           operator*           ( )const; // conjugate of a quaterion; in practice the opposite angular displacement
inline      tQuat           operator*           ( float fScale )const;
inline      tQuat           operator/           ( float fScale )const;
inline      const tQuat&    operator/=          ( float fScale );
inline      const tQuat&    operator*=          ( float fScale );
inline      const tQuat&    operator*=          ( const tQuat& other ); // TO DO:
};
const tQuat nullRot( 1.f, 0.f, 0.f, 0.f );

inline    float         Dot                     ( const tQuat& q1, const tQuat& q2 );
inline    tQuat         InvQuat                 ( const tQuat& q );
inline    tQuat         Unit                    ( const tQuat& q );
inline    float         QuatNor                 ( tQuat& q );                                        // return lenght before normalization;
inline    Bool          IsUnit                  ( const tQuat& q, float eps = 0.00001f );            // mainly for debug;
inline    void          MakeRotQuat             ( const tVect3& axis, float alpha, tQuat& out );
inline    tQuat         Pow                     ( const tQuat& q, float exp );
inline    tQuat         Slerp                   ( const tQuat& q0 ,const tQuat& q1, float t );
inline    void          Slerp                   ( const tQuat& q0 ,const tQuat& q1, float t, tQuat& out );
inline    void          MakeQuatFromMat         ( const m3x3& mat, tQuat& q );
inline    void          MakeQuatFromMat         ( const m4x4& mat, tQuat& q );
inline    void          MakeQuatFromEul         ( const tVect3& ang, tQuat& q );

inline void tQuat::Normalize ( )
{
    tQuat::operator/=(Lenght());    
}

inline void tQuat::GetRotAxis ( tVect3& out )const
{
    // Compute sin^2(theta/2).  Remember that w = cos(theta/2),
    // and sin^2(x) + cos^2(x) = 1

    float sinThetaOver2Sq = 1.0f - w*w;

    // Protect against numerical imprecision
    if (sinThetaOver2Sq <= 0.0f) 
    {
        THOT_ASSERT(0); // invalid quat; 
        // Identity quaternion, or numerical imprecision.  Just
        // return any valid vector, since it doesn't matter

        //return Vector3(1.0f, 0.0f, 0.0f);
    }

    // Compute 1 / sin(theta/2)
    float    oneOverSinThetaOver2 = 1.0f / sqrt(sinThetaOver2Sq);

    // Return axis of rotation
    out.x = x * oneOverSinThetaOver2;
    out.y = y * oneOverSinThetaOver2;
    out.z = z * oneOverSinThetaOver2;
}

inline float tQuat::GetRotAngle ( )const
{
    // Compute the half angle.  Remember that w = cos(theta / 2)

    float thetaOver2 = acos(w);

    // Return the rotation angle
    return thetaOver2 * 2.0f * TO_DEG;
}

inline tVect3 tQuat::GetRotAxis ( )const
{
    // Compute sin^2(theta/2).  Remember that w = cos(theta/2),
    // and sin^2(x) + cos^2(x) = 1

    float sinThetaOver2Sq = 1.0f - w*w;

    // Protect against numerical imprecision
    if (sinThetaOver2Sq <= 0.0f) 
    {
        THOT_ASSERT(0); // invalid quat; 
        // Identity quaternion, or numerical imprecision.  Just
        // return any valid vector, since it doesn't matter

        //return Vector3(1.0f, 0.0f, 0.0f);
    }

    // Compute 1 / sin(theta/2)

    float    oneOverSinThetaOver2 = 1.0f / sqrt(sinThetaOver2Sq);

    // Return axis of rotation

    return tVect3(
                    x * oneOverSinThetaOver2,
                    y * oneOverSinThetaOver2,
                    z * oneOverSinThetaOver2
                );

}



//inline tQuat tQuat::operator- (  )
//{
//    return tQuat( -w, -x, -y, -z);
//}

inline Bool tQuat::operator== ( const tQuat& other )const
{
    return w == other.w && x == other.x && y == other.y && z == other.z;
}


inline Bool IsUnit ( const tQuat& q, float eps )
{
    return fequals( q.Lenght(), 1.f, eps );
}

inline tQuat Unit ( const tQuat& q )
{
    return q/q.Lenght();
}

inline float QuatNor ( tQuat& q )
{
    float fLen = q.Lenght();
    THOT_ASSERT(fLen!=0.f);
    q/=fLen;
    return fLen;
}

inline void MakeRotQuat ( const tVect3& axis, float alpha, tQuat& out )
{
    tVect3 n = Unit(axis);

    float cos = cosf(alpha*0.5f*TO_RAD);
    float sin = sinf(alpha*0.5f*TO_RAD);

    out.w = cos;
    out.x = n.x * sin;
    out.y = n.y * sin;
    out.z = n.z * sin;
}

inline tQuat Pow ( const tQuat& q, float exp )
{
    if( fabs(q.w) > 0.9999f )
        return q;

    // Extract the half angle alpha (alpha = theta/2)
    float    alpha = acos(q.w);

    // Compute new alpha value
    float    newAlpha = alpha * exp;

    // Compute new w value
    tQuat result;
    result.w = cos(newAlpha);

    // Compute new xyz values
    float    mult = sin(newAlpha) / sin(alpha);
    result.x = q.x * mult;
    result.y = q.y * mult;
    result.z = q.z * mult;

    // Return it
    return result;
}

inline tQuat Slerp ( const tQuat& q0 ,const tQuat& q1, float t )
{
    // Check for out-of range parameter and return edge points if so
    THOT_ASSERT(IsUnit(q0) && IsUnit(q1), "QUATERNIONS FOR SLERP MUST BE NORMALIZED" );

    if (t <= 0.0f) return q0;
    if (t >= 1.0f) return q1;

    // Compute "cosine of angle between quaternions" using dot product
    float cosOmega = Dot(q0, q1);

    // If negative dot, use -q1.  Two quaternions q and -q
    // represent the same rotation, but may produce
    // different slerp.  We chose q or -q to rotate using
    // the acute angle.

    float q1w = q1.w;
    float q1x = q1.x;
    float q1y = q1.y;
    float q1z = q1.z;
    if (cosOmega < 0.0f) 
    {
        q1w = -q1w;
        q1x = -q1x;
        q1y = -q1y;
        q1z = -q1z;
        cosOmega = -cosOmega;
    }

    // We should have two unit quaternions, so dot should be <= 1.0
    THOT_ASSERT(cosOmega < 1.0001f);

    // Compute interpolation fraction, checking for quaternions
    // almost exactly the same
    float k0, k1;
    if (cosOmega > 0.999999f) 
    {
        // Very close - just use linear interpolation,
        // which will protect againt a divide by zero
        k0 = 1.0f-t;
        k1 = t;

    } else 
    {
        // Compute the sin of the angle using the
        // trig identity sin^2(omega) + cos^2(omega) = 1

        float sinOmega = sqrt(1.0f - cosOmega*cosOmega);

        // Compute the angle from its sin and cosine
        float omega = atan2(sinOmega, cosOmega);

        // Compute inverse of denominator, so we only have
        // to divide once

        float oneOverSinOmega = 1.0f / sinOmega;

        // Compute interpolation parameters
        k0 = sin((1.0f - t) * omega) * oneOverSinOmega;
        k1 = sin(t * omega) * oneOverSinOmega;
    }

    // Interpolate

    tQuat out;
    out.x = k0*q0.x + k1*q1x;
    out.y = k0*q0.y + k1*q1y;
    out.z = k0*q0.z + k1*q1z;
    out.w = k0*q0.w + k1*q1w;

    // Return it
    return out;
}

inline void Slerp ( const tQuat& q0 ,const tQuat& q1, float t, tQuat& out )
{
    // Check for out-of range parameter and return edge points if so

    if (t <= 0.0f) 
    {
        out =  q0;
        return;
    }

    if (t >= 1.0f) 
    {
        out =  q1;
        return;
    }

    // Compute "cosine of angle between quaternions" using dot product
    float cosOmega = Dot(q0, q1);

    // If negative dot, use -q1.  Two quaternions q and -q
    // represent the same rotation, but may produce
    // different slerp.  We chose q or -q to rotate using
    // the acute angle.

    float q1w = q1.w;
    float q1x = q1.x;
    float q1y = q1.y;
    float q1z = q1.z;
    if (cosOmega < 0.0f) 
    {
        q1w = -q1w;
        q1x = -q1x;
        q1y = -q1y;
        q1z = -q1z;
        cosOmega = -cosOmega;
    }

    // We should have two unit quaternions, so dot should be <= 1.0
    THOT_ASSERT(cosOmega < 1.0001f);

    // Compute interpolation fraction, checking for quaternions
    // almost exactly the same
    float k0, k1;
    if (cosOmega > 0.9999f) 
    {
        // Very close - just use linear interpolation,
        // which will protect againt a divide by zero
        k0 = 1.0f-t;
        k1 = t;

    } else 
    {

        // Compute the sin of the angle using the
        // trig identity sin^2(omega) + cos^2(omega) = 1

        float sinOmega = sqrt(1.0f - cosOmega*cosOmega);

        // Compute the angle from its sin and cosine

        float omega = atan2(sinOmega, cosOmega);

        // Compute inverse of denominator, so we only have
        // to divide once

        float oneOverSinOmega = 1.0f / sinOmega;

        // Compute interpolation parameters
        k0 = sin((1.0f - t) * omega) * oneOverSinOmega;
        k1 = sin(t * omega) * oneOverSinOmega;
    }

    // Interpolate
    out.x = k0*q0.x + k1*q1x;
    out.y = k0*q0.y + k1*q1y;
    out.z = k0*q0.z + k1*q1z;
    out.w = k0*q0.w + k1*q1w;
}

inline float tQuat::Lenght( )const
{
    return sqrtf( w * w +  x *  x + y * y + z * z );
}

inline tQuat tQuat::GetConjugate () const
{
    return tQuat( w, -x, -y, -z );
}

inline tVect3& tQuat::GetVectorPart    ( )
{
    return (tVect3&)q[1];
}

inline const tVect3& tQuat::GetVectorPart    ( )const
{
    return (tVect3&)q[1];
}


inline tQuat tQuat::operator* ( const tQuat& other )const
{
#define w1 w
#define w2 other.w
#define x1 x
#define x2 other.x
#define y1 y
#define y2 other.y
#define z1 z
#define z2 other.z

    return tQuat(
                     w1 * w2 - x1 * x2 - y1 * y2 - z1 * z2
                    ,w1 * x2 + x1 * w2 + y1 * z2 - z1 * y2
                    ,w1 * y2 + y1 * w2 + z1 * x2 - x1 * z2
                    ,w1 * z2 + z1 * w2 + x1 * y2 - y1 * x2
                );

#undef w1
#undef w2
#undef x1
#undef x2
#undef y1
#undef y2
#undef z1
#undef z2
}

inline tQuat tQuat::operator* ( const tVect3& v )const
{
    // TO DO: make some optimizations;
    return operator*( tQuat( 0, v.x, v.y, v.z ) );
}

inline tQuat tQuat::operator* ( )const
{
    return tQuat( w, -x, -y, -z );
}

inline const tQuat&    tQuat::operator*= ( const tQuat& other )
{
float w1 =  w;
#define w2 other.w
float x1 = x;
#define x2 other.x
float y1 =  y;
#define y2 other.y
float z1 =  z;
#define z2 other.z

w = w1 * w2 - x1 * x2 - y1 * y2 - z1 * z2;
x = w1 * x2 + x1 * w2 + y1 * z2 - z1 * y2;
y = w1 * y2 + y1 * w2 + z1 * x2 - x1 * z2;
z = w1 * z2 + z1 * w2 + x1 * y2 - y1 * x2;

#undef w2
#undef x2
#undef y2
#undef z2    

    return (*this);
}

inline void tQuat::Conjugate ( )
{
    x = -x;
    y = -y;
    z = -z;
}

inline tQuat tQuat::operator* ( float fScale )const
{
    return tQuat( w * fScale, x * fScale, y * fScale, z * fScale );
}

inline tQuat tQuat::operator/ ( float fScale )const
{
    THOT_ASSERT(fScale!=0.f);
    return tQuat( w / fScale, x / fScale, y / fScale, z / fScale );
}

inline const tQuat&    tQuat::operator/= ( float fScale )
{
    THOT_ASSERT(fScale!=0.f);
    w /= fScale;
    x /= fScale;
    y /= fScale;
    z /= fScale;
    return *this;
}

inline const tQuat&    tQuat::operator*= ( float fScale )
{
    w /= fScale;
    x /= fScale;
    y /= fScale;
    z /= fScale;
    return *this;
}

inline tQuat InvQuat ( const tQuat& q )
{
    return ( (*q) / q.Lenght());
}


inline float Dot ( const tQuat& q1, const tQuat& q2 )
{
    return q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;  
}


inline void MakeQuatFromMat ( const m3x3& m, tQuat& q )
{
    // Determine which of w, x, y, or z has the largest absolute value
    float fourWSquaredMinus1 = m._11 + m._22 + m._33;
    float fourXSquaredMinus1 = m._11 - m._22 - m._33;
    float fourYSquaredMinus1 = m._22 - m._11 - m._33;
    float fourZSquaredMinus1 = m._33 - m._11 - m._22;
    
    int biggestIndex = 0;
    float fourBiggestSquaredMinus1 = fourWSquaredMinus1;
    if (fourXSquaredMinus1 > fourBiggestSquaredMinus1) 
    {
        fourBiggestSquaredMinus1 = fourXSquaredMinus1;
        biggestIndex = 1;
    }
    if (fourYSquaredMinus1 > fourBiggestSquaredMinus1) 
    {
        fourBiggestSquaredMinus1 = fourYSquaredMinus1;
        biggestIndex = 2;
    }
    if (fourZSquaredMinus1 > fourBiggestSquaredMinus1) 
    {
        fourBiggestSquaredMinus1 = fourZSquaredMinus1;
        biggestIndex = 3;
    }
    
    // Perform square root and division
    float biggestVal = sqrt(fourBiggestSquaredMinus1 + 1.0f) * 0.5f;
    float mult = 0.25f / biggestVal;
    
    // Apply table to compute quaternion values
    switch ( biggestIndex ) 
    {
        case 0:
            q.w = biggestVal;
            q.x = (m._23 - m._32) * mult;
            q.y = (m._31 - m._13) * mult;
            q.z = (m._12 - m._21) * mult;
        break;

        case 1:
            q.x = biggestVal;
            q.w = (m._23 - m._32) * mult;
            q.y = (m._12 + m._21) * mult;
            q.z = (m._31 + m._13) * mult;
        break;

        case 2:
            q.y = biggestVal;
            q.w = (m._31 - m._13) * mult;
            q.x = (m._12 + m._21) * mult;
            q.z = (m._23 + m._32) * mult;
        break;

        case 3:
            q.z = biggestVal;
            q.w = (m._12 - m._21) * mult;
            q.x = (m._31 + m._13) * mult;
            q.y = (m._23 + m._32) * mult;
        break;
    }

    q.Conjugate();
}

inline void MakeQuatFromMat ( const m4x4& m, tQuat& q )
{
    // Determine which of w, x, y, or z has the largest absolute value
    float fourWSquaredMinus1 = m._11 + m._22 + m._33;
    float fourXSquaredMinus1 = m._11 - m._22 - m._33;
    float fourYSquaredMinus1 = m._22 - m._11 - m._33;
    float fourZSquaredMinus1 = m._33 - m._11 - m._22;
    
    int biggestIndex = 0;
    float fourBiggestSquaredMinus1 = fourWSquaredMinus1;
    if (fourXSquaredMinus1 > fourBiggestSquaredMinus1) 
    {
        fourBiggestSquaredMinus1 = fourXSquaredMinus1;
        biggestIndex = 1;
    }
    if (fourYSquaredMinus1 > fourBiggestSquaredMinus1) 
    {
        fourBiggestSquaredMinus1 = fourYSquaredMinus1;
        biggestIndex = 2;
    }
    if (fourZSquaredMinus1 > fourBiggestSquaredMinus1) 
    {
        fourBiggestSquaredMinus1 = fourZSquaredMinus1;
        biggestIndex = 3;
    }
    
    // Perform square root and division
    float biggestVal = sqrt(fourBiggestSquaredMinus1 + 1.0f) * 0.5f;
    float mult = 0.25f / biggestVal;
    
    // Apply table to compute quaternion values
    switch ( biggestIndex ) 
    {
        case 0:
            q.w = biggestVal;
            q.x = (m._23 - m._32) * mult;
            q.y = (m._31 - m._13) * mult;
            q.z = (m._12 - m._21) * mult;
        break;
        case 1:
            q.x = biggestVal;
            q.w = (m._23 - m._32) * mult;
            q.y = (m._12 + m._21) * mult;
            q.z = (m._31 + m._13) * mult;
        break;
        case 2:
            q.y = biggestVal;
            q.w = (m._31 - m._13) * mult;
            q.x = (m._12 + m._21) * mult;
            q.z = (m._23 + m._32) * mult;
        break;
        case 3:
            q.z = biggestVal;
            q.w = (m._12 - m._21) * mult;
            q.x = (m._31 + m._13) * mult;
            q.y = (m._23 + m._32) * mult;
        break;
    }
}

inline void MakeQuatFromEul ( const tVect3& ang, tQuat& q )
{
    float cosh = cosf( ang.heading * 0.5f * TO_RAD );
    float sinh = sinf( ang.heading * 0.5f * TO_RAD );

    float cosp = cosf( ang.pitch * 0.5f* TO_RAD );
    float sinp = sinf( ang.pitch * 0.5f* TO_RAD );

    float cosb = cosf( ang.bank * 0.5f* TO_RAD );
    float sinb = sinf( ang.bank * 0.5f* TO_RAD );

    q.w = cosh * cosp * cosb + sinh * sinp * sinb;
    q.x = cosh * sinp * cosb + sinh * cosp * sinb;
    q.y = sinh * cosp * cosb - cosh * sinp * sinb;
    q.z = cosh * cosp * sinb - sinh * sinp * cosb;
}




#endif