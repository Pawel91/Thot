#ifndef __MATH_UTILS_H__
#define __MATH_UTILS_H__

//#include "MathCore\MathCoreDef.h"
#include "Constants.h"
//#include "math.h"

extern float floor( float _X );

struct tVect3;
struct m4x4;
struct m3x3;
struct tQuat;

namespace MathUtils
{
    void    MATHCORE_API       GetMatFromZDir          ( const tVect3& dir, m3x3& mOut );
    m3x3    MATHCORE_API       GetMatFromZDir          ( const tVect3& dir );
    void    MATHCORE_API       GetMatFromZDir          ( const tVect3& dir, m4x4& mOut );
    void    MATHCORE_API       GetQuatFromZDir         ( const tVect3& dir, tQuat& q );
    tQuat   MATHCORE_API       GetQuatFromZDir         ( const tVect3& dir );

    float   MATHCORE_API        GetRatio                ( float value, float start, float end );

    void    MATHCORE_API        GetBarycentricCoordinates   ( const tVect3& A, const tVect3& B, const tVect3& C, const tVect3& Q, tVect3& out);
    void    MATHCORE_API        ApplyInterpolation          ( const tVect3& A, const tVect3& B, const tVect3& C, const tVect3& baryCoords, tVect3& out );

    Bool    MATHCORE_API        PointInTriangle             ( const tVect3& A, const tVect3& B, const tVect3& C, const tVect3& Q );
    Bool    MATHCORE_API        RayVsTriangle               (
                                                                const tVect3& P
                                                                ,const tVect3& dir
                                                                ,float rayLenght
                                                                ,const tVect3& A
                                                                ,const tVect3& B
                                                                ,const tVect3& C
                                                                ,tVect3& out
                                                            );
    Bool    MATHCORE_API        SegmentVsTriangle           (          
                                                                const tVect3& FromPoint
                                                                ,const tVect3& ToPoint
                                                                ,const tVect3& A
                                                                ,const tVect3& B
                                                                ,const tVect3& C
                                                                ,tVect3& out
                                                            );

int MATHCORE_API intersect3D_RayTriangle( const tVect3& P0, const tVect3& P1, const tVect3& V0, const tVect3& V1, const tVect3& V2, tVect3& outIntersection );
bool MATHCORE_API intersect_RayVsTriangle( const tVect3& P0, const tVect3& P1, const tVect3& V0, const tVect3& V1, const tVect3& V2, tVect3& outIntersection);     
}

//****Declarations
inline  float   MATHCORE_API    WrapPI                      ( float rad );
        void    MATHCORE_API    MakeCanonicalEuler          ( tVect3& eulerAngle );
        void    MATHCORE_API    GetEuler                    ( const m3x3& mat, tVect3& outAng );
        void    MATHCORE_API    GetEuler                    ( const m4x4& mat, tVect3& outAng );
        tVect3  MATHCORE_API    GetEuler                    ( const m3x3& mat );
        tVect3  MATHCORE_API    GetEuler                    ( const m4x4& mat );
        tVect3  MATHCORE_API    GetEuler                    ( const tQuat& q );
        void    MATHCORE_API    GetEuler                    ( const tQuat& q, tVect3& outAng );

template<class T>
        T            Lerp                        ( T start, T target, float t );



//***** Inline Definitions
inline float WrapPI ( float rad )
{
    rad += PI;
    rad -= floor( rad / _2PI ) * _2PI;
    rad -= PI;
    return rad;
}

template< class T>
inline T Lerp ( T start, T target, float t )
{
    return (1.f - t ) * start + t * target;
}


THOT_FORCE_INLINE float MathUtils::GetRatio( float value, float start, float end )
{
#ifdef _DEBUG
    THOT_ASSERT(value>=start && value <=end);
#else
    if( value <start )
    {
        return start;
    }
    if( value > end )
    {
        return end;
    }
#endif 


    return (value - start)/(end-start);
}

#endif /*__MATH_UTILS_H__*/