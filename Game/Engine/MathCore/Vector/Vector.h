#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "Kernel/KernelUtils.h"
#include "Kernel/DataStructures/ArrayTypeBase.h"
#include "MathCore/MathCoreDef.h"
#include "math.h"

#define _VECT_VERIFY


struct MATHCORE_API tVect2:public CArrayTypeBase<float>
{
    tVect2();
    tVect2( float _x, float _y );
    tVect2( const tVect2& other );

    union
    {
        float v[2];

        struct
        {
            float x, y;
        };
    
    };

    float&            operator[]    ( int nIdx );
    const float&    operator[]    ( int nIdx )const;

    tVect2            operator*    ( float fScale ) const;
    tVect2            operator/    ( float fScale ) const;
    tVect2            operator-    ()const;
    tVect2            operator+    ( const tVect2& other )const ;
    tVect2            operator-    ( const tVect2& other )const ;

    const tVect2&    operator*=    ( float fScale );
    const tVect2&    operator/=    ( float fScale );
    const tVect2&    operator+=    ( const tVect2& other );


static const tVect2     nullVect;
static const tVect2        xAxis;
static const tVect2        yAxis;
};

THOT_COMPILE_ASSERT2( sizeof(tVect2) == sizeof(float) * 2, "tVect2 must have 2 floats");

#pragma region Vect2_Inline_Functions

inline tVect2 operator * ( float fScale, const tVect2& v )
{
    return v.operator*(fScale);
}

inline float& tVect2::operator[] ( int nIdx )
{
    return this->v[nIdx];
}

inline const float& tVect2::operator[] ( int nIdx )const
{
    return this->v[nIdx];
}


inline tVect2 tVect2::operator*    ( float fScale ) const
{
    return tVect2( x * fScale, y * fScale );
}

inline tVect2 tVect2::operator/ ( float fScale ) const
{
#ifdef _VECT_VERIFY
    THOT_ASSERT( fScale != 0.f );
#endif
    return tVect2( x/fScale, y/fScale );
}

inline tVect2 tVect2::operator- ()const
{
    return tVect2( -x, -y );
}

inline tVect2 tVect2::operator+    ( const tVect2& other )const
{
    return tVect2( x + other.x, y + other.y );
}

inline tVect2 tVect2::operator- ( const tVect2& other )const
{
    return tVect2( x - other.x, y - other.y );
}

inline const tVect2& tVect2::operator*= ( float fScale )
{
    x *= fScale;
    y *= fScale;
    return *this;
}

inline const tVect2& tVect2::operator/= ( float fScale )
{
    x /= fScale;
    y /= fScale;
    return *this;
}

inline const tVect2& tVect2::operator+= ( const tVect2& other )
{
    x += other.x;
    y += other.y;
    return *this;
}

#pragma endregion Vect2_Inline_Functions
struct tQuat;

struct MATHCORE_API tVect3:public CArrayTypeBase<float>
{

    tVect3();
    tVect3( const tQuat& q );
    tVect3( float _x, float _y, float _z );
    tVect3( const tVect3& other );

    union
    {
        float v[3];

        struct
        {
            float x, y, z;
        };

        struct
        {
            float    pitch;
            float    heading;
            float    bank;
        };
    
    };

    void                DbgTrace            ( )const;
    Bool                Equals              ( const tVect3& other, float fEps = 0.000001f )const;

    Bool                operator==              ( const tVect3& other )const;
    Bool                operator!=              ( const tVect3& other )const;
    const tVect3&       operator=               ( const tQuat& q);
    tVect3              operator*               ( float fScale ) const;
    tVect3              operator/               ( float fScale ) const;
    tVect3              operator-               ()const;                // standart negation;
    tVect3              operator+               ( const tVect3& other )const;
    tVect3              operator-               ( const tVect3& other )const;

                        operator float*            ();
                        operator const float*    ()const;

    const tVect3&        operator*=                ( float fScale );
    const tVect3&        operator/=                ( float fScale );
    const tVect3&        operator+=                ( const tVect3& other );
};

THOT_COMPILE_ASSERT2( sizeof(tVect3) == sizeof(float) * 3, "tVect3 must have 3 floats" );

inline const tVect3& tVect3::operator+= ( const tVect3& other )
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

inline Bool tVect3::operator== ( const tVect3& other )const
{
    return ( x == other.x && y == other.y && z == other.z );
}

inline Bool tVect3::operator!= ( const tVect3& other )const
{
    //return operator ==(*this, other);
    return !this->operator==(other);
}

THOT_FORCE_INLINE tVect3::operator float*    ()
{
    return v;
}

THOT_FORCE_INLINE tVect3::operator const float*    ()const
{
    return v;
}

inline tVect3 tVect3::operator*    ( float fScale ) const
{
    return tVect3( x * fScale, y * fScale, z * fScale );
}

inline tVect3 tVect3::operator/    ( float fScale ) const
{
    return tVect3( x / fScale, y / fScale, z / fScale  );
}

inline tVect3 tVect3::operator- ()const
{
    return tVect3( -x, -y, -z);
}
inline tVect3 tVect3::operator+    ( const tVect3& other )const
{
    return tVect3( x + other.x, y + other.y, z + other.z );
}

inline tVect3 tVect3::operator-    ( const tVect3& other )const
{
    return tVect3( x - other.x, y - other.y, z - other.z );
}

inline const tVect3& tVect3::operator*=    ( float fScale )
{    
    x *= fScale;
    y *= fScale;
    z *= fScale;
    return *this;
}


inline const tVect3& tVect3::operator/=    ( float fScale )
{
    x /= fScale;
    y /= fScale;
    z /= fScale;
    return *this;
}

const tVect3    nullVect        = tVect3( 0.f, 0.f, 0.f );
const tVect3    xAxis           = tVect3( 1.f, 0.f, 0.f );
const tVect3    yAxis           = tVect3( 0.f, 1.f, 0.f );
const tVect3    zAxis           = tVect3( 0.f, 0.f, 1.f );

    tVect3        operator*        ( float fScale, const tVect3& v );

    float        VectLenSquared    ( const tVect2& a );
    float        VectLenSquared    ( const tVect3& a);

    float        VectLen            ( const tVect3& a );
    float        VectLen            ( const tVect2& a );

    tVect3        Unit            ( const tVect3& a );
    tVect2        Unit            ( const tVect2& a );

    float        VectNor            ( tVect3& a ); // normalize vector and return its lenght;
    float        VectNor            ( tVect2& a );

    float        Dot                ( const tVect3& a, const tVect3& b );
    float        Dot                ( const tVect2& a, const tVect2& b );

    tVect3        Cross            ( const tVect3& a, const tVect3& b );

    Bool        IsUnit            ( const tVect3& v, float fEps = 0.00001f );
    Bool        SameDir            ( const tVect3&a, tVect3& b, float fEps = 0.00001f);
    Bool        SameDir            ( const tVect2&a, tVect2& b, float fEps = 0.00001f);


inline tVect3 operator* ( float fScale, const tVect3& v )
{
    return v.operator*( fScale);
}

inline float VectLenSquared    ( const tVect2& a )
{
    return a.x * a.x + a.y * a.y;
}

inline float VectLenSquared    ( const tVect3& a )
{
    return a.x * a.x + a.y * a.y + a.z * a.z;
}

inline    float VectLen ( const tVect3& a )
{
    return  sqrtf( VectLenSquared(a) );    
}

inline    float VectLen ( const tVect2& a )
{
    return  sqrtf( VectLenSquared(a) );    
}

inline    tVect3 Unit    ( const tVect3& a )
{
    THOT_ASSERT(VectLen(a)!=0.f);
    return a / VectLen(a);
}

inline    tVect2 Unit    ( const tVect2& a )
{
    THOT_ASSERT(VectLen(a)!=0.f);
    return a / VectLen(a);
}

inline    float VectNor ( tVect3& a )
{
    float fLen = VectLen(a);
    THOT_ASSERT(fLen!=0.f);
    a /= fLen;
    return fLen;
}

inline    float VectNor ( tVect2& a )
{
    float fLen = VectLen(a);
    a /= fLen;
    return fLen;
}

inline    float Dot ( const tVect3& a, const tVect3& b )
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline float Dot ( const tVect2& a, const tVect2& b )
{
    return a.x * b.x + a.y * b.y ;
}

inline    tVect3  Cross    ( const tVect3& a, const tVect3& b )
{
    return tVect3( a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x );
}



inline Bool IsUnit ( const tVect3& v, float fEps )
{
    return fequals( VectLen(v), 1.f, fEps );
}

inline Bool SameDir ( const tVect3&a, tVect3& b, float fEps )
{
    THOT_ASSERT(0);
    return false;
}

inline Bool SameDir ( const tVect2&a, tVect2& b, float fEps )
{
    THOT_ASSERT(0);
    return false;
}



#endif