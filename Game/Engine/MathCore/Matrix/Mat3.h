#pragma once
#ifndef __MAT3_H__
#define __MAT3_H__

//#include "MathCore\MathCoreDef.h"
#include "MathCore\Vector\Vector.h"

struct MATHCORE_API m3x3
{
    m3x3    ( );
    m3x3    (    float _11, float _12, float _13
                ,float _21, float _22, float _23
                ,float _31, float _32, float _33 );
    m3x3    ( const m3x3& other );

    union
    {
        float m[9];
        struct
        {
            float _11, _12, _13;
            float _21, _22, _23;
            float _31, _32, _33;
        };
    };


        void            DebugTrace    ( );

#pragma region OPERATORS
        const m3x3&        operator=    ( const m3x3& other );
        const m3x3&        operator+=    ( const m3x3& other );
        const m3x3&        operator-=    ( const m3x3& other );
        const m3x3&        operator*=    ( const m3x3& other );

        m3x3            operator-    (  )const;
        m3x3            operator*    (float fScale)const;
        m3x3            operator/    (float fScale)const;
        m3x3            operator+    ( const m3x3& other )    const;
        m3x3            operator-    ( const m3x3& other )    const;
        m3x3            operator*    ( const m3x3& other )    const;

        tVect3&            operator[]( int nRow );
        const tVect3&    operator[]( int nRow ) const;
        operator float*         () { return m; }
        operator const float*   ()const { return m;}


friend    tVect3        operator*    ( const tVect3& vect, const m3x3& mat );
#pragma endregion

};

const m3x3    o3x3(    0.f, 0.f, 0.f
                    ,0.f, 0.f, 0.f
                    ,0.f, 0.f, 0.f
                );


const m3x3    i3x3(    1.f, 0.f, 0.f
                    ,0.f, 1.f, 0.f
                    ,0.f, 0.f, 1.f
                );



inline const m3x3& m3x3::operator= ( const m3x3& other )
{
    for( register int i=0; i<9; i++ )
        m[i] = other.m[i];

    return *this;
}

inline m3x3 m3x3::operator-    (  )const
{
    return m3x3( -_11, -_12, -_13, -_21, -_22, -_23, -_31, -_32, -_33 );
}

inline const m3x3& m3x3::operator+=    ( const m3x3& other )
{
    // first row
    _11 += other._11;
    _12 += other._12;
    _13 += other._13;

    // 2nd row
    _21 += other._21;
    _22 += other._22;
    _23 += other._23;

    // 3nd row
    _31 += other._31;
    _32 += other._32;
    _33 += other._33;

    return *this;
}

inline const m3x3& m3x3::operator-=    ( const m3x3& other )
{
    // first row
    _11 -= other._11;
    _12 -= other._12;
    _13 -= other._13;

    // 2nd row
    _21 -= other._21;
    _22 -= other._22;
    _23 -= other._23;
        
    // 3nd row
    _31 -= other._31;
    _32 -= other._32;
    _33 -= other._33;

    return *this;
}

inline const m3x3& m3x3::operator*=    ( const m3x3& other )
{
    (*this)    = operator*( other );

    return *this;
}

inline m3x3 m3x3::operator* (float fScale)const
{
    m3x3 rez;
    for( register int i=0; i<9; i++ )
        rez.m[i] = m[i] * fScale;

    return rez;
}

inline m3x3 m3x3::operator/ (float fScale)const
{
    m3x3 rez;
    for( register int i=0; i<9; i++ )
        rez.m[i] = m[i] / fScale;

    return rez;
}


inline m3x3 m3x3::operator+    ( const m3x3& other ) const
{
    m3x3 rez;

    // first row
    rez._11 =  _11 + other._11;
    rez._12 =  _12 + other._12;
    rez._13 =  _13 + other._13;

    // 2nd row
    rez._21 = _21 + other._21;
    rez._22 = _22 + other._22;
    rez._23 = _23 + other._23;
        
    // 3nd row
    rez._31 = _31 + other._31;
    rez._32 = _32 + other._32;
    rez._33 = _33 + other._33;

    return rez;
}

inline m3x3 m3x3::operator-    ( const m3x3& other )    const
{
    m3x3 rez;

    // first row
    rez._11 =  _11 - other._11;
    rez._12 =  _12 - other._12;
    rez._13 =  _13 - other._13;

    // 2nd row
    rez._21 = _21 - other._21;
    rez._22 = _22 - other._22;
    rez._23 = _23 - other._23;
        
    // 3nd row
    rez._31 = _31 - other._31;
    rez._32 = _32 - other._32;
    rez._33 = _33 - other._33;

    return rez;
}

inline m3x3 m3x3::operator*    ( const m3x3& other )    const
{
    m3x3 rez;

    rez._11 = _11 * other._11 + _12 * other._21 + _13 * other._31;
    rez._12 = _11 * other._12 + _12 * other._22 + _13 * other._32;
    rez._13 = _11 * other._13 + _12 * other._23 + _13 * other._33;

    rez._21 = _21 * other._11 + _22 * other._21 + _23 * other._31;
    rez._22 = _21 * other._12 + _22 * other._22 + _23 * other._32;
    rez._23 = _21 * other._13 + _22 * other._23 + _23 * other._33;
    
    rez._31 = _31 * other._11 + _32 * other._21 + _33 * other._31;
    rez._32 = _31 * other._12 + _32 * other._22 + _33 * other._32;
    rez._33 = _31 * other._13 + _32 * other._23 + _33 * other._33;

    return rez;
}

inline tVect3& m3x3::operator[]( int nRow )
{
    THOT_ASSERT( nRow >= 0 && nRow <=3 );
    return (tVect3&)this->m[ 3 * (nRow-1)];
}

inline const tVect3& m3x3::operator[]( int nRow ) const
{
    THOT_ASSERT( nRow >= 0 && nRow <=3 );
    return (tVect3&)this->m[ 3 * (nRow-1)];
}


#endif