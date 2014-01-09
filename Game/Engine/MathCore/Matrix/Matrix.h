#ifndef __MATHCORE_MATRIX_H__
#define __MATHCORE_MATRIX_H__

#include "Kernel/Memory/Memory.h"
#include "MathCore/Vector/Vector.h"
#include "MathCore/Matrix/Mat3.h"
#include "MathCore/Matrix/Mat4.h"


#define AXEX(mat)       ((mat)[1])
#define AXEY(mat)       ((mat)[2])
#define AXEZ(mat)       ((mat)[3])
#define POS(mat)        ((mat)[4])

struct tQuat;


inline tVect3 operator*        ( const tVect3& vect, const m3x3& mat );
inline tVect3 operator*        ( const tVect3& vect, const m4x4& mat );
inline tVect3 operator*        ( const m4x4& mat, const tVect3& v );

//******** Rotation matrix
// TO DO: macro for left and right handed system
#define __RIGHT_HAND_SYSTEM // not used yet

inline          void    MATHCORE_API    MakeXMat            ( float xAng, m3x3& mat );
inline          void    MATHCORE_API    MakeXMat            ( float xAng, m4x4& mat );

inline          void    MATHCORE_API    MakeYMat            ( float yAng, m3x3& mat );
inline          void    MATHCORE_API    MakeYMat            ( float yAng, m4x4& mat );

inline          void    MATHCORE_API    MakeZMat            ( float zAng, m3x3& mat );
inline          void    MATHCORE_API    MakeZMat            ( float zAng, m4x4& mat );

inline          void    MATHCORE_API    MakeYXZMat          ( float yAng, float xAng, float zAng, m3x3& mat );
inline          void    MATHCORE_API    MakeYXZMat          ( float yAng, float xAng, float zAng, m4x4& mat );

inline          void    MATHCORE_API    MakeAnyRotMat       ( const tVect3& axis, float fAng, m3x3& mat  );
inline          void    MATHCORE_API    MakeAnyRotMat       ( const tVect3& axis, float fAng, m4x4& mat  );
void                    MATHCORE_API    MakeMatFromQuat     ( const tQuat&q, m3x3& out );
void                    MATHCORE_API    MakeMatFromQuat     ( const tQuat&q, m4x4& out );


inline      Bool    MATHCORE_API    MatEquals           ( const m4x4& m1, const m4x4& m2, float eps = 0.00001f );

//******** liniar algebra

inline      void    MATHCORE_API    PerspectiveMat  ( float fov, float aspect, float znear, float zfar, m4x4& outProjection );
inline      void    MATHCORE_API    Transpose       ( const m3x3& mat, m3x3& out );
inline      void    MATHCORE_API    Transpose       ( const m4x4& mat, m4x4& out );
inline      m3x3    MATHCORE_API    Transpose       ( const m3x3& mat );
inline      m4x4    MATHCORE_API    Transpose       ( const m4x4& mat );

inline    float MATHCORE_API    Det                ( const m3x3& mat );
inline    float MATHCORE_API    Det                ( const m4x4& mat ); // ignores 4th collum; same effect as 3x3 matrix because in allmost all cases we will ignore 4th collumn
inline    float MATHCORE_API    sDet4            ( const m4x4& mat );
inline    m3x3  MATHCORE_API   GetMinor        ( const m4x4& mat, int row, int col );
inline    void  MATHCORE_API   GetMinor        ( const m4x4& mat, int row, int col, m3x3& out );
inline    void  MATHCORE_API   Adjoint            ( const m3x3& mat, m3x3& out );
inline    void  MATHCORE_API   Adjoint            ( const m4x4& mat, m4x4& out );
inline    void  MATHCORE_API   sAdjoint4        ( const m4x4& mat, m4x4& out );
inline    Bool  MATHCORE_API   sInvMat4        ( const m4x4& mat, m4x4& out );
inline    Bool  MATHCORE_API   InvMat            ( const m3x3& mat, m3x3& out );
inline    Bool  MATHCORE_API   InvMat            ( const m4x4& mat, m4x4& out );
inline    Bool  MATHCORE_API   IsOrtho            ( const m3x3& mat, float fEps = 0.00005f );        // for debug and assertion
inline    Bool  MATHCORE_API   IsOrtho            ( const m4x4& mat, float fEps = 0.00005f );        // for debug and assertion
inline    Bool  MATHCORE_API   InvOrthoMat        ( const m3x3& mat, m3x3& out );
inline    Bool  MATHCORE_API   InvRotTransMat    ( const m4x4& mat, m4x4& out );    // inverse of a matrix that contains a translation and a rotation;

#define    InvRotMat InvOrthoMat

inline tVect3 operator* ( const tVect3& vect, const m3x3& mat )
{
    return tVect3 (  vect.x * mat._11+ vect.y * mat._21 + vect.z * mat._31
                    ,vect.x * mat._12+ vect.y * mat._22 + vect.z * mat._32
                    ,vect.x * mat._13+ vect.y * mat._23 + vect.z * mat._33
                    );
}

inline tVect3 operator* ( const tVect3& v, const m4x4& m )
{
    return tVect3(     v.x * m._11 + v.y * m._21 + v.z * m._31 + m._41 
                    ,v.x * m._12 + v.y * m._22 + v.z * m._32 + m._42 
                    ,v.x * m._13 + v.y * m._23 + v.z * m._33 + m._43
                );
}

inline tVect3 operator* ( const m4x4& m, const tVect3& v )
{
    return tVect3(
                     m._11 * v.x + m._12 * v.y + m._13 * v.z + m._14
                    ,m._21 * v.x + m._22 * v.y + m._23 * v.z + m._24
                    ,m._31 * v.x + m._32 * v.y + m._33 * v.z + m._34
                );
}

inline    void MakeXMat ( float xAng, m3x3& mat )
{
    mat = i3x3;

    float _sin = sinf(xAng*TO_RAD);
    float _cos = cosf(xAng*TO_RAD);

    //mat = i3x3;
    mat._22 = _cos;
    mat._23 = -_sin;
    mat._32 = _sin;
    mat._33 = _cos;
}

inline void    MakeXMat ( float xAng, m4x4& mat )
{
    mat = i4x4;

    float _sin = sinf(xAng*TO_RAD);
    float _cos = cosf(xAng*TO_RAD);

    mat._22 = _cos;
    mat._23 = -_sin;
    mat._32 = _sin;
    mat._33 = _cos;
}


inline    void MakeYMat ( float yAng, m3x3& mat )
{
    mat = i3x3;
 
    float _sin = sinf(yAng*TO_RAD);
    float _cos = cosf(yAng*TO_RAD);

    mat._11 = _cos;
    mat._13 = _sin;
    mat._31 = -_sin;
    mat._33 = _cos;
}

inline void    MakeYMat ( float yAng, m4x4& mat )
{
    mat = i4x4;

    float _sin = sinf(yAng*TO_RAD);
    float _cos = cosf(yAng*TO_RAD);

    mat._11 = _cos;
    mat._13 = _sin;
    mat._31 = -_sin;
    mat._33 = _cos;
}

inline    void MakeZMat ( float zAng, m3x3& mat )
{
    mat = i3x3;

    float _sin = sinf(zAng*TO_RAD);
    float _cos = cosf(zAng*TO_RAD);

    mat._11 = _cos;
    mat._12 = -_sin;
    mat._21 = _sin;
    mat._22 = _cos;

}

inline void    MakeZMat ( float zAng, m4x4& mat )
{
    mat = i4x4;

    float _sin = sinf(zAng*TO_RAD);
    float _cos = cosf(zAng*TO_RAD);

    mat._11 = _cos;
    mat._12 = -_sin;
    mat._21 = _sin;
    mat._22 = _cos;
}

inline void    MakeYXZMat ( float yAng, float xAng, float zAng, m3x3& m )
{
    m = i3x3;

    float sinh = sinf(yAng*TO_RAD);
    float cosh = cosf(yAng*TO_RAD);

    float sinp = sinf(xAng*TO_RAD);
    float cosp = cosf(xAng*TO_RAD);

    float sinb = sinf(zAng*TO_RAD);
    float cosb = cosf(zAng*TO_RAD);

    m._11 = cosh * cosb + sinh * sinp * sinb;
    m._12 = -cosh * sinb + sinh * sinp * cosb;
    m._13 = sinh * cosp;
    m._21 = sinb * cosp;
    m._22 = cosb * cosp;
    m._23 = -sinp;
    m._31 = -sinh * cosb + cosh * sinp * sinb;
    m._32 = sinb * sinh + cosh * sinp * cosb;
    m._33 = cosh * cosp;
}

inline void    MakeYXZMat ( float yAng, float xAng, float zAng, m4x4& m )
{
    m = i4x4;

    float sinh = sinf(yAng*TO_RAD);
    float cosh = cosf(yAng*TO_RAD);

    float sinp = sinf(xAng*TO_RAD);
    float cosp = cosf(xAng*TO_RAD);

    float sinb = sinf(zAng*TO_RAD);
    float cosb = cosf(zAng*TO_RAD);

    m._11 = cosh * cosb + sinh * sinp * sinb;
    m._12 = -cosh * sinb + sinh * sinp * cosb;
    m._13 = sinh * cosp;
    m._21 = sinb * cosp;
    m._22 = cosb * cosp;
    m._23 = -sinp;
    m._31 = -sinh * cosb + cosh * sinp * sinb;
    m._32 = sinb * sinh + cosh * sinp * cosb;
    m._33 = cosh * cosp;
}



inline void MakeAnyRotMat ( const tVect3& axis, float fAng, m3x3& mat  )
{
    tVect3 n = Unit(axis);
    mat = i3x3;

    float _sin = sinf(-fAng*TO_RAD);
    float _cos = cosf(-fAng*TO_RAD);
    float alpha = 1.f - _cos;

    mat._11 = n.x * n.x * alpha + _cos;
    mat._12 = n.x * n.y * alpha + n.z * _sin;
    mat._13 = n.x * n.z * alpha - n.y * _sin;
    
    mat._21 = n.x * n.y * alpha - n.z * _sin;
    mat._22 = n.y * n.y * alpha + _cos;
    mat._23 = n.y * n.z * alpha + n.x * _sin;
    
    mat._31 = n.x * n.z * alpha + n.y * _sin;
    mat._32 = n.y * n.z * alpha - n.x * _sin;
    mat._33 = n.z * n.z * alpha + _cos;
}

inline void    MakeAnyRotMat ( const tVect3& axis, float fAng, m4x4& mat  )
{
    tVect3 n = Unit(axis);
    mat = i4x4;

    float _sin = sinf( -fAng*TO_RAD);
    float _cos = cosf( -fAng*TO_RAD);
    float alpha = 1.f - _cos;

    mat._11 = n.x * n.x * alpha + _cos;
    mat._12 = n.x * n.y * alpha + n.z * _sin;
    mat._13 = n.x * n.z * alpha - n.y * _sin;
    
    mat._21 = n.x * n.y * alpha - n.z * _sin;
    mat._22 = n.y * n.y * alpha + _cos;
    mat._23 = n.y * n.z * alpha + n.x * _sin;
    
    mat._31 = n.x * n.z * alpha + n.y * _sin;
    mat._32 = n.y * n.z * alpha - n.x * _sin;
    mat._33 = n.z * n.z * alpha + _cos;
}

//inline void    MakeMatFromQuat    ( const tQuat& q, m3x3 out )
//{
//    out = i3x3;
//    out._11 = 1.f - 2.f * (q.y * q.y + q.z * q.z );
//    out._12 = 2.f * ( q.x * q.y + q.w * q.z );
//    out._13 = 2.f * ( q.x * q.z - q.w * q.y );
//    out._21 = 2.f * ( q.x * q.y - q.w * q.z );
//    out._22 = 1.f - 2.f * ( q.x * q.x + q.z * q.z );
//    out._23 = 2.f * ( q.y * q.z + q.w * q.x );
//    out._31 = 2.f * ( q.x * q.z + q.w * q.y );
//    out._32 = 2.f * ( q.y * q.z - q.w * q.x );
//    out._33 = 1.f - 2.f * ( q.x * q.x + q.y * q.y );
//}
//
//inline void    MakeMatFromQuat    ( const tQuat&q, m4x4 out )
//{
//
//}


inline void Transpose ( const m3x3& mat, m3x3& out )
{
    const int size = 3;
    for( register int i=1; i<=size; i++ )
        for( register int j=1; j<=size; j++ )
            out.m[size*(i-1)+j -1 ] = mat.m[ size*(j-1)+i -1];
}
 
inline void Transpose ( const m4x4& mat, m4x4& out )
{
    const int size = 4;
    for( register int i=1; i<=size; i++ )
        for( register int j=1; j<=size; j++ )
            out.m[size*(i-1)+j -1 ] = mat.m[ size*(j-1)+i -1];
}

inline    m3x3 Transpose ( const m3x3& mat )
{
    m3x3 out;
    Transpose(mat, out );
    return out;
}

inline    m4x4 Transpose ( const m4x4& mat )
{
    m4x4 out;
    Transpose(mat, out );
    return out;
}



inline float Det ( const m3x3& mat )
{
    return (      mat._11 * ( mat._22 * mat._33 - mat._23 * mat._32 )
                + mat._12 * ( mat._23 * mat._31 - mat._21 * mat._33 )
                + mat._13 * ( mat._21 * mat._32 - mat._22 * mat._31 )
            );
}

inline float Det ( const m4x4& m )
{
    //return (
    //              m._11 * ( m._22*( m._33*m._44 - m._34*m._43 ) -  m._32 * ( m._23*m._44 + m._24 * m._43 ) + m._42 * ( m._23 * m._34 - m._24 * m._33 ) )
    //            - m._21 * ( m._12*( m._33*m._44 - m._34*m._43 ) -  m._32 * ( m._13*m._44 + m._14 * m._43 ) + m._42 * ( m._13 * m._34 - m._14 * m._33 ) )
    //            + m._31 * ( m._12*( m._23*m._44 - m._24*m._43 ) -  m._22 * ( m._13*m._44 + m._14 * m._43 ) + m._42 * ( m._13 * m._24 - m._14 * m._23 ) )
    //            - m._41 * ( m._12*( m._23*m._34 - m._24*m._33 ) -  m._22 * ( m._13*m._34 + m._14 * m._33 ) + m._32 * ( m._13 * m._24 - m._14 * m._23 ) )
    //        );

    //return (
    //          m._11 * ( m._22*( m._33*m._44 - m._34*m._43 ) +  m._23 * ( m._34*m._42 - m._32 * m._44 ) + m._24 * ( m._32 * m._43 - m._33 * m._42 ) )
    //        - m._12 * ( m._21*( m._33*m._44 - m._34*m._43 ) +  m._23 * ( m._34*m._41 - m._31 * m._44 ) + m._24 * ( m._31 * m._43 - m._33 * m._41 ) )
    //        + m._13 * ( m._21*( m._32*m._44 - m._34*m._42 ) +  m._22 * ( m._34*m._41 - m._31 * m._44 ) + m._24 * ( m._31 * m._42 - m._32 * m._41 ) )
    //        - m._14 * ( m._21*( m._32*m._43 - m._33*m._42 ) +  m._22 * ( m._33*m._41 - m._31 * m._43 ) + m._23 * ( m._31 * m._42 - m._32 * m._41 ) )
    //    );

    return (      m._11 * ( m._22 * m._33 - m._23 * m._32 )
                + m._12 * ( m._23 * m._31 - m._21 * m._33 )
                + m._13 * ( m._21 * m._32 - m._22 * m._31 )
            );
}



inline float sDet4 ( const m4x4& m )
{
    return (
              m._11 * ( m._22*( m._33*m._44 - m._34*m._43 ) +  m._23 * ( m._34*m._42 - m._32 * m._44 ) + m._24 * ( m._32 * m._43 - m._33 * m._42 ) )
            - m._12 * ( m._21*( m._33*m._44 - m._34*m._43 ) +  m._23 * ( m._34*m._41 - m._31 * m._44 ) + m._24 * ( m._31 * m._43 - m._33 * m._41 ) )
            + m._13 * ( m._21*( m._32*m._44 - m._34*m._42 ) +  m._22 * ( m._34*m._41 - m._31 * m._44 ) + m._24 * ( m._31 * m._42 - m._32 * m._41 ) )
            - m._14 * ( m._21*( m._32*m._43 - m._33*m._42 ) +  m._22 * ( m._33*m._41 - m._31 * m._43 ) + m._23 * ( m._31 * m._42 - m._32 * m._41 ) )
        );
}

//inline float sDet4 ( const m4x4& mat )
//{
//    m3x3 min14, min24, min34, min44;
//    GetMinor( mat, 1, 4, min14 );
//    GetMinor( mat, 2, 4, min24 );
//    GetMinor( mat, 3, 4, min34 );
//    GetMinor( mat, 4, 4, min44 );
//
//    return (-mat._14) * Det(min14) + mat._24 * Det(min24) - mat._34 * Det(min34) + mat._44 * Det(min44);
//}


inline    m3x3 GetMinor ( const m4x4& mat, int row, int col )
{
    THOT_ASSERT( row >= 1 && row <= 4 && col >= 1 && col <= 4 );

    m3x3 ret;
    int idx = -1;

    for( register int i=1; i<=4; i++ )
    {
        if( i == row )
            continue;

        for( register int j=1; j<=4; j++ )
        if( j!=col )
        {
            ret.m[++idx] = mat.m[4*(i-1)+j -1 ];
        }
    }

    return ret;
}

inline void    GetMinor ( const m4x4& mat, int row, int col, m3x3& out )
{
    THOT_ASSERT( row >= 1 && row <= 4 && col >= 1 && col <= 4 );

    register int idx = -1;

    for( register int i=1; i<=4; i++ )
    {
        if( i == row )
            continue;

        for( register int j=1; j<=4; j++ )
        if( j!=col )
        {
            out.m[++idx] = mat.m[4*(i-1)+j -1 ];
        }
    }
}

inline void    Adjoint ( const m3x3& mat, m3x3& out )
{
    float c11 = mat._22 * mat._33 - mat._23 * mat._32;
    float c12 = mat._23 * mat._31 - mat._21 * mat._33;
    float c13 = mat._21 * mat._32 - mat._22 * mat._31;
    float c21 = mat._13 * mat._32 - mat._12 * mat._33;
    float c22 = mat._11 * mat._33 - mat._13 * mat._31;
    float c23 = mat._12 * mat._31 - mat._11 * mat._32;
    float c31 = mat._12 * mat._23 - mat._13 * mat._22;
    float c32 = mat._13 * mat._21 - mat._11 * mat._23;
    float c33 = mat._11 * mat._22 - mat._12 * mat._21;

    out._11 = c11;
    out._12 = c21;
    out._13 = c31;
    out._21 = c12;
    out._22 = c22;
    out._23 = c32;
    out._31 = c13;
    out._32 = c23;
    out._33 = c33;
}

inline void    Adjoint ( const m4x4& mat, m4x4& out )
{
    float c11 = mat._22 * mat._33 - mat._23 * mat._32;
    float c12 = mat._23 * mat._31 - mat._21 * mat._33;
    float c13 = mat._21 * mat._32 - mat._22 * mat._31;
    float c21 = mat._13 * mat._32 - mat._12 * mat._33;
    float c22 = mat._11 * mat._33 - mat._13 * mat._31;
    float c23 = mat._12 * mat._31 - mat._11 * mat._32;
    float c31 = mat._12 * mat._23 - mat._13 * mat._22;
    float c32 = mat._13 * mat._21 - mat._11 * mat._23;
    float c33 = mat._11 * mat._22 - mat._12 * mat._21;

    out._11 = c11;
    out._12 = c21;
    out._13 = c31;
    out._21 = c12;
    out._22 = c22;
    out._23 = c32;
    out._31 = c13;
    out._32 = c23;
    out._33 = c33;
}

inline    void sAdjoint4 ( const m4x4& m, m4x4& out )
{
    // TO DO:
    //THOT_ASSERT(0); // not implemented

    out._11 = m._22*m._33*m._44 + m._23*m._34*m._42 + m._24*m._32*m._43 - m._22*m._34*m._43 - m._23 * m._32 * m._44 - m._24*m._33*m._42;
    out._12 = m._12*m._34*m._43 + m._13*m._32*m._44 + m._14*m._33*m._42 - m._12*m._33*m._44 - m._13 * m._34 * m._42 - m._14*m._32*m._43;
    out._13 = m._12*m._23*m._44 + m._13*m._24*m._42 + m._14*m._22*m._43 - m._12*m._24*m._43 - m._13 * m._22 * m._44 - m._14*m._23*m._42;
    out._14 = m._12*m._24*m._33 + m._13*m._22*m._34 + m._14*m._23*m._32 - m._12*m._23*m._34 - m._13 * m._24 * m._32 - m._14*m._22*m._33;
    out._21 = m._21*m._34*m._43 + m._23*m._31*m._44 + m._24*m._33*m._31 - m._21*m._33*m._44 - m._23 * m._34 * m._41 - m._24*m._31*m._43;
    out._22 = m._11*m._33*m._44 + m._13*m._34*m._41 + m._14*m._31*m._43 - m._11*m._34*m._43 - m._13 * m._31 * m._44 - m._14*m._33*m._41;
    out._23 = m._11*m._24*m._43 + m._13*m._21*m._44 + m._14*m._23*m._41 - m._11*m._23*m._44 - m._13 * m._24 * m._41 - m._14*m._21*m._43;
    out._24 = m._11*m._23*m._34 + m._13*m._24*m._31 + m._14*m._21*m._33 - m._11*m._24*m._33 - m._13 * m._21 * m._34 - m._14*m._23*m._31;
    out._31 = m._21*m._32*m._44 + m._22*m._34*m._41 + m._24*m._31*m._42 - m._21*m._34*m._42 - m._22 * m._31 * m._44 - m._24*m._32*m._41;
    out._32 = m._11*m._34*m._42 + m._12*m._31*m._44 + m._14*m._32*m._41 - m._11*m._32*m._44 - m._12 * m._34 * m._41 - m._14*m._31*m._42;
    out._33 = m._11*m._22*m._44 + m._12*m._24*m._41 + m._14*m._21*m._42 - m._11*m._24*m._42 - m._12 * m._21 * m._44 - m._14*m._22*m._41;
    out._34 = m._11*m._24*m._32 + m._12*m._21*m._34 + m._14*m._22*m._31 - m._11*m._22*m._34 - m._12 * m._24 * m._31 - m._14*m._21*m._32;
    out._41 = m._21*m._33*m._42 + m._22*m._31*m._43 + m._23*m._32*m._41 - m._21*m._32*m._43 - m._22 * m._33 * m._41 - m._23*m._31*m._42;
    out._42 = m._11*m._32*m._43 + m._12*m._33*m._41 + m._13*m._31*m._42 - m._11*m._33*m._42 - m._12 * m._31 * m._43 - m._13*m._32*m._41;
    out._43 = m._11*m._23*m._42 + m._12*m._21*m._43 + m._13*m._22*m._41 - m._11*m._22*m._43 - m._12 * m._23 * m._41 - m._13*m._21*m._42;
    out._44 = m._11*m._22*m._33 + m._12*m._23*m._31 + m._13*m._21*m._32 - m._11*m._23*m._32 - m._12 * m._21 * m._33 - m._13*m._22*m._31;

}



inline Bool InvMat ( const m3x3& mat, m3x3& out )
{
    float fDet = Det(mat);
    if( fDet == 0.f )
        return false;

    m3x3 adjoint;
    Adjoint( mat, adjoint );

    out = adjoint / fDet;


    return true;
}

inline Bool    InvMat ( const m4x4& mat, m4x4& out )
{
    THOT_ASSERT(IsOrtho(mat));
    Bool rez =  InvRotTransMat( mat, out );

    THOT_ASSERT( MatEquals( mat * out, i4x4, 0.0001f) );

    return rez;

    //out = i4x4;

    //float fDet = Det(mat);
    //if( fDet == 0.f )
    //    return false;

    //m4x4 adjoint;
    //Adjoint( mat, adjoint );

    ////out = adjoint / fDet;
    //for( register int i=1; i<=3; i++ )
    //for( register int j=1; j<=3; j++ )
    //    out.m[ 4 * (i-1) + j-1 ] = adjoint.m[4 * (i-1) + j-1] / fDet;

    //tVect3 vPosOut = POS(out);
    //tVect3 v = -POS(mat);
    //POS(out) = (-POS(mat));
    ////out[4] = -(mat[4]);

    //return true;
}

inline    Bool sInvMat4 ( const m4x4& mat, m4x4& out )
{
    // TO DO:
    //THOT_ASSERT(0); // not implemented

    float fDet = sDet4(mat);
    if( fDet == 0.f )
        return false;

    m4x4 adjoint;
    sAdjoint4(mat, adjoint);

    out = adjoint/fDet;

    return true;
}

inline Bool    IsOrtho ( const m3x3& mat, float fEps )
    {
    const tVect3& r1 = mat[1];
    const tVect3& r2 = mat[2];
    const tVect3& r3 = mat[3];

    return (       fequals(Dot(r1,r1), 1.f, fEps)
                && fequals(Dot(r2,r1), 0.f, fEps)
                && fequals(Dot(r3,r1), 0.f, fEps)
                && fequals(Dot(r1,r2), 0.f, fEps)
                && fequals(Dot(r2,r2), 1.f, fEps)
                && fequals(Dot(r3,r2), 0.f, fEps)
                && fequals(Dot(r1,r3), 0.f, fEps)
                && fequals(Dot(r1,r3), 0.f, fEps)
                && fequals(Dot(r3,r3), 1.f, fEps)
            );

}

inline Bool    IsOrtho ( const m4x4& mat, float fEps )
{
    const tVect3& r1 = mat[1];
    const tVect3& r2 = mat[2];
    const tVect3& r3 = mat[3];

    return (       fequals(Dot(r1,r1), 1.f, fEps)
                && fequals(Dot(r2,r1), 0.f, fEps)
                && fequals(Dot(r3,r1), 0.f, fEps)
                && fequals(Dot(r1,r2), 0.f, fEps)
                && fequals(Dot(r2,r2), 1.f, fEps)
                && fequals(Dot(r3,r2), 0.f, fEps)
                && fequals(Dot(r1,r3), 0.f, fEps)
                && fequals(Dot(r1,r3), 0.f, fEps)
                && fequals(Dot(r3,r3), 1.f, fEps)
            );
}

inline Bool    InvOrthoMat ( const m3x3& mat, m3x3& out )
{
    THOT_ASSERT( IsOrtho(mat) );
    Transpose( mat, out );
    return true;
}

inline Bool    InvRotTransMat ( const m4x4& mat, m4x4& out )
{
    THOT_ASSERT(IsOrtho(mat));
    out = i4x4;

    // transpose the 3x3 rot submatrix;
    for( register int i=1; i<=3; i++ )
    for( register int j=1; j<=3; j++ )
        out.m[ 4*(j-1) + i -1 ] = mat.m[ 4 * (i-1) + j -1 ];

    const tVect3& pos = POS(mat);
    POS(out) = tVect3 (  -(pos.x * ( out._11) + pos.y * ( out._21) + pos.z * ( out._31) )
                        ,-(pos.x * ( out._12) + pos.y * ( out._22) + pos.z * ( out._32) )
                        ,-(pos.x * ( out._13) + pos.y * ( out._23) + pos.z * ( out._33) )
                        );

    return true;
}


inline Bool MatEquals ( const m4x4& m1, const m4x4& m2, float eps )
{
    for( int i=0; i<16; i++ )
        {
            if( !fequals( m1.m[i], m2.m[i], eps  ) )
                return false;
        }

    return true;
}


inline void PerspectiveMat  ( float fov, float aspect, float znear, float zfar, m4x4& outProjection )
{
    float phi = fov*0.5f *TO_RAD;
    float f = tan( HALF_PI -  phi );
      
    Memory::Set( &outProjection, sizeof(m4x4), 0 );

    outProjection._11 = f/aspect;

    outProjection._22 = f;

    //outProjection._33 = (znear + zfar)/(znear - zfar);
    //outProjection._34 = -1.f;

    outProjection._33 = (znear + zfar)/(zfar - znear);
    outProjection._34 = 1.f;



    outProjection._43 = (2.f*znear*zfar)/(znear - zfar);
}


#endif //__MATHCORE_MATRIX_H__