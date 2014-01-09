#pragma once
#ifndef __MAT4_H__
#define __MAT4_H__

//#include "MathCore\MathCoreDef.h"
#include "MathCore\Vector\Vector.h"

__declspec(align(16)) struct MATHCORE_API m4x4: public CArrayTypeBase<float>
{
    m4x4(   );
    m4x4(   float _11, float _12, float _13, float _14
            ,float _21, float _22, float _23, float _24
            ,float _31, float _32, float _33, float _34 
            ,float _41, float _42, float _43, float _44
            );
    m4x4( const m4x4& other );

    union
    {
        float m[16];
        struct
        {
            float _11, _12, _13, _14;
            float _21, _22, _23, _24;
            float _31, _32, _33, _34;
            float _41, _42, _43, _44;
        };
        //struct
        //{
        //    __m128      xAxis;
        //    __m128      yAxis;
        //    __m128      zAxis;
        //    __m128      wAxis;
        //};
    };

    void            DebugTrace      ( )const;
    void            DebugTrace      ( const char* tag )const;

inline      m4x4            operator/               ( float fScale );
inline      tVect3&         operator[]              ( int nRow );
inline      const tVect3&   operator[]              ( int nRow ) const;
inline      m4x4            operator*               ( const m4x4& other )const;
inline      const m4x4&     operator*=              ( const m4x4& other );
inline                      operator const float*   ( )const;
inline                      operator float*         ( );

inline      tVect3          Project( const tVect3& v);


};

THOT_COMPILE_ASSERT2( sizeof(m4x4)==sizeof(float)*16, "m4x4 must be 16 floats" );

const m4x4 i4x4 (   1.f, 0.f, 0.f, 0.f
                    ,0.f, 1.f, 0.f, 0.f
                    ,0.f, 0.f, 1.f, 0.f
                    ,0.f, 0.f, 0.f, 1.f
                );


inline m4x4::operator const float*   ()const
{
    return (const float*)m;
}

inline m4x4::operator float* ( )
{
    return (float*)m;
}

inline m4x4 m4x4::operator/ ( float fScale )
{
    m4x4 ret;
    for( register int i=0; i<16; i++ )
        ret.m[i] = m[i] / fScale;

    return ret;
}

inline tVect3& m4x4::operator[] ( int nRow )
{
    THOT_ASSERT(nRow>=1 && nRow<=4);
    return (tVect3&)( m[ 4 * (nRow-1)] );
}

inline const tVect3& m4x4::operator[] ( int nRow ) const
{
    THOT_ASSERT(nRow>=1 && nRow<=4);
    return (tVect3&)( m[ 4 * (nRow-1)] );
}

inline m4x4 m4x4::operator* ( const m4x4& other )const
{
    m4x4 rez = i4x4;

    rez._11 = _11 * other._11 + _12 * other._21 + _13 * other._31 + _14 * other._41;
    rez._12 = _11 * other._12 + _12 * other._22 + _13 * other._32 + _14 * other._42;
    rez._13 = _11 * other._13 + _12 * other._23 + _13 * other._33 + _14 * other._43;
    rez._14 = _11 * other._14 + _12 * other._24 + _13 * other._34 + _14 * other._44;


    rez._21 = _21 * other._11 + _22 * other._21 + _23 * other._31 + _24 * other._41;
    rez._22 = _21 * other._12 + _22 * other._22 + _23 * other._32 + _24 * other._42;
    rez._23 = _21 * other._13 + _22 * other._23 + _23 * other._33 + _24 * other._43;
    rez._24 = _21 * other._14 + _22 * other._24 + _23 * other._34 + _24 * other._44;
    
    rez._31 = _31 * other._11 + _32 * other._21 + _33 * other._31 + _34 * other._41;
    rez._32 = _31 * other._12 + _32 * other._22 + _33 * other._32 + _34 * other._42;
    rez._33 = _31 * other._13 + _32 * other._23 + _33 * other._33 + _34 * other._43;
    rez._34 = _31 * other._14 + _32 * other._24 + _33 * other._34 + _34 * other._44;


    rez._41 = _41 * other._11 + _42 * other._21 + _43 * other._31 + _44 * other._41;
    rez._42 = _41 * other._12 + _42 * other._22 + _43 * other._32 + _44 * other._42;
    rez._43 = _41 * other._13 + _42 * other._23 + _43 * other._33 + _44 * other._43;
    rez._44 = _41 * other._14 + _42 * other._24 + _43 * other._34 + _44 * other._44;
    return rez;
}

inline tVect3 m4x4::Project( const tVect3& v)
{
    tVect3 rez = nullVect;

    rez.x = v.x * _11 + v.y * _21 * v.z *_31 + _41;
    rez.y = v.x * _12 + v.y * _22 * v.z *_32 + _42;
    rez.z = v.x * _13 + v.y * _23 * v.z *_33 + _43;

    float w  = v.x * _14 + v.y * _24 * v.z *_34 + _44;
    rez = rez * (1.f/w);

    return rez;
}

inline const m4x4& m4x4::operator*= ( const m4x4& other )
{
    (*this) = operator*( other );
    return *this;
}

#endif