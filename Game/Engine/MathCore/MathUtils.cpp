#include "MathCore_PCH.h"
#include "MathUtils.h"

#include "Kernel\Kernel.h"
#include "MathCore\Matrix\Matrix.h"
#include "MathCore\Quaternion\Quat.h"


void MathUtils::GetMatFromZDir ( const tVect3& dir, m3x3& mOut )
{
    mOut = i3x3;
    THOT_ASSERT(dir!=nullVect);
    AXEZ(mOut) = Unit(dir);
    AXEX(mOut) = Cross( yAxis, AXEZ(mOut) );
    AXEY(mOut) = Unit ( Cross( AXEZ(mOut), AXEX(mOut) ) );
}

void MathUtils::GetMatFromZDir ( const tVect3& dir, m4x4& mOut )
{
    mOut = i4x4;
    THOT_ASSERT( dir != nullVect );
    AXEZ(mOut) = Unit(dir);
    AXEX(mOut) = Unit (Cross( yAxis, AXEZ(mOut) ) );
    AXEY(mOut) = Unit ( Cross( AXEZ(mOut), AXEX(mOut) ) );
}

m3x3 MathUtils::GetMatFromZDir ( const tVect3& dir )
{
    m3x3 ret;
    GetMatFromZDir( dir, ret );
    return ret;
}


void MathUtils::GetQuatFromZDir ( const tVect3& dir, tQuat& q )
{
    m3x3 mat;
    GetMatFromZDir(dir, mat);
    MakeQuatFromMat( mat, q );
}

tQuat MathUtils::GetQuatFromZDir ( const tVect3& dir )
{
    tQuat ret;
    GetQuatFromZDir( dir, ret );
    return ret;
}



void MakeCanonicalEuler ( tVect3& ang )
{
    // First, wrap pitch in range -pi ... pi
    ang *= TO_RAD;
    ang.pitch = WrapPI(ang.pitch);

    // Now, check for "the back side" of the matrix, pitch outside
    // the canonical range of -pi/2 ... pi/2
    if (ang.pitch < -HALF_PI) 
    {
        ang.pitch    = -PI - ang.pitch;
        ang.heading += PI;
        ang.bank    += PI;
    } 
    else if (ang.pitch > HALF_PI) 
    {
        ang.pitch    = PI - ang.pitch;
        ang.heading += PI;
        ang.bank    += PI;
    }

    // OK, now check for the gimbel lock case (within a slight
    // tolerance)
    if (fabs(ang.pitch) > HALF_PI - 1e-4) 
    {
        // We are in gimbel lock.  Assign all rotation
        // about the vertical axis to heading
        ang.heading += ang.bank;
        ang.bank = 0.0f;

    } else 
    {
        // Not in gimbel lock.  Wrap the bank angle in
        // canonical range 
        ang.bank = WrapPI(ang.bank);
    }
    // Wrap heading in canonical range
    ang.heading = WrapPI( ang.heading );

    ang*=TO_DEG;
}


void GetEuler ( const m3x3& m, tVect3& ang )
{
    THOT_ASSERT( IsOrtho(m) );
    // Extract sin(pitch) from m23.

    float    sp = -m._23;

    // Check for Gimbel lock
    if (fabs(sp) > 0.99999f) 
    {
        // Looking straight up or down
        ang.pitch = HALF_PI * sp;
        // Compute heading, slam bank to zero
        ang.heading = atan2(-m._31, m._11);
        ang.bank = 0.0f;

    } else 
    {
        // Compute angles.  We don't have to use the "safe" asin
        // function because we already checked for range errors when
        // checking for Gimbel lock
        ang.heading = atan2(m._13, m._33);
        ang.pitch    = asin(sp);
        ang.bank    = atan2(m._21, m._22);
    }

    ang*=TO_DEG;
}

tVect3 GetEuler ( const m3x3& mat )
{
    tVect3 ret;
    GetEuler(mat, ret);
    return ret;
}

tVect3 GetEuler ( const m4x4& mat )
{
    tVect3 ret;
    GetEuler( mat, ret );
    return ret;
}

void GetEuler ( const m4x4& m, tVect3& ang )
{    
    THOT_ASSERT( IsOrtho(m) );
    // Extract sin(pitch) from m23.

    float    sp = -m._23;

    // Check for Gimbel lock
    if (fabs(sp) > 0.99999f) 
    {
        // Looking straight up or down
        ang.pitch = HALF_PI * sp;
        // Compute heading, slam bank to zero
        ang.heading = atan2(-m._31, m._11);
        ang.bank = 0.0f;

    } else 
    {
        // Compute angles.  We don't have to use the "safe" asin
        // function because we already checked for range errors when
        // checking for Gimbel lock
        ang.heading = atan2(m._13, m._33);
        ang.pitch    = asin(sp);
        ang.bank    = atan2(m._21, m._22);
    }

    ang*=TO_DEG;
}


tVect3 GetEuler ( const tQuat& q )
{
    tVect3 ret;
    GetEuler( q, ret);
    return ret;
}

void GetEuler ( const tQuat& q, tVect3& ang )
{
    // Extract sin(pitch)
    float sp = -2.0f * ( q.y*q.z - q.w*q.x );

    // Check for Gimbel lock, giving slight tolerance for numerical imprecision
    if (fabs(sp) > 0.9999f) 
    {
        // Looking straight up or down
        ang.pitch    = HALF_PI * sp;
        // Compute heading, slam bank to zero
        ang.heading = atan2( -q.x*q.z + q.w*q.y, 0.5f - q.y*q.y - q.z*q.z );
        ang.bank    = 0.0f;

    } else 
    {
        // Compute angles.  We don't have to use the "safe" asin
        // function because we already checked for range errors when
        // checking for Gimbel lock
        ang.pitch    = asin(sp);
        ang.heading    = atan2(q.x*q.z + q.w*q.y, 0.5f - q.x*q.x - q.y*q.y);
        ang.bank    = atan2(q.x*q.y + q.w*q.z, 0.5f - q.x*q.x - q.z*q.z);
    }

    ang*=TO_DEG;
}


void MathUtils::GetBarycentricCoordinates ( const tVect3& A, const tVect3& B, const tVect3& C, const tVect3& Q, tVect3& out)
{
    float area  = VectLen( Cross( B - A, C - A ) );
    out.x       = VectLen( Cross( C - B, Q - B ) ) / area;
    out.y       = VectLen( Cross( A - C, Q - C ) ) / area;
    out.z       = VectLen( Cross( B - A, Q - A ) ) / area;
}

void MathUtils::ApplyInterpolation( const tVect3& A, const tVect3& B, const tVect3& C, const tVect3& baryCoords, tVect3& out )
{
    out = A * baryCoords.x + B * baryCoords.y + C * baryCoords.z;
}


Bool MathUtils::PointInTriangle( const tVect3& A, const tVect3& B, const tVect3& C, const tVect3& Q )
{
    tVect3 n = Cross( B - A, C-A );
    VectNor(n);


    if(    Dot( Cross( B - A, Q - A ), n ) >=0 
        && Dot( Cross( C - B, Q - B ), n ) >=0 
        && Dot( Cross( A - C, Q - C ), n ) >=0 
        )
    {
        return true;
    }

    return false;
}

bool MathUtils::intersect_RayVsTriangle( const tVect3& P0, const tVect3& P1, const tVect3& V0, const tVect3& V1, const tVect3& V2, tVect3& outIntersection)     
{               
        tVect3 dir = P1-P0;
        //VectNor(dir);
        tVect3 unitDir = Unit(dir);
        //float rayLenght = VectNor(dir);
        tVect3 v0v1 = V1 - V0;                                                                                                                                                                                                                
        tVect3 v0v2 = V2 - V0;                                                                                                                                                                                                                
        tVect3 N = Cross(v0v1, v0v2);                                                                                                                                                                                                         
        float nDotRay = Dot(N, dir);                                                                                                                                                                         
        if( fequals( Dot(N, dir), 0.f ) )
        {
            return false; // ray parallel to triangle 
        }
        float d = Dot(N, V0);
        float t = -(Dot(N, P0) + d) / nDotRay;
  
        // inside-out test
        tVect3 Phit = P0 + unitDir*t;  //r(t);
  
       // inside-out test edge0
        tVect3 v0p = Phit - V0;
        float v = Dot(N, Cross(v0v1, v0p));
        if (v < 0)
        {
            return false; // P outside triangle
        }
 
        // inside-out test edge1
        tVect3 v1p = Phit - V1;
        tVect3 v1v2 = V2 - V1;
        float w = Dot(N, Cross(v1v2, v1p));
        if (w < 0)
        {
            return false; // P outside triangle
        }
 
        // inside-out test edge2
        tVect3 v2p = Phit - V2;
        tVect3 v2v0 = V0 - V2;
        float u = Dot(N, Cross(v2v0, v2p));
        if (u < 0)
        {
            return false; // P outside triangle
        }
 
        //isectData.t = t;
        outIntersection = P0 + unitDir*t;
  
       return true;
}


int MathUtils::intersect3D_RayTriangle( const tVect3& P0, const tVect3& P1, const tVect3& V0, const tVect3& V1, const tVect3& V2, tVect3& outIntersection )
{
    // copy paste from net
    float rayLenght = VectLen( P1-P0 );
    const float SMALL_NUM = 0.000001f;
    tVect3  u, v, n;        // triangle vectors
    tVect3  dir, w0, w;     // ray vectors
    float r, a, b;          // params to calc ray-plane intersect

    // get triangle edge vectors and plane normal
    u = V1 - V0;
    v = V2 - V0;
    n = Cross( u , v);              // cross product
    VectNor(n);
    if( n == nullVect )             // triangle is degenerate
    {
        return -1;                  // do not deal with this case
    }

    dir = P1 - P0;              // ray direction vector
    w0 = P0 - V0;
    a = -Dot(n,w0);
    b = Dot(n,dir);
    if (fabs(b) < SMALL_NUM)        // ray is  parallel to triangle plane
    {     
        if (a == 0)
        {
            return 2;                 // ray lies in triangle plane
        }
        else return 0;              // ray disjoint from plane
    }

    // get intersect point of ray with triangle plane
    r = a / b;
    if (r < 0.0)                    // ray goes away from triangle
        return 0;                   // => no intersect
    // for a segment, also test if (r > 1.0) => no intersect

    outIntersection = P0 + r * (dir);     // intersect point of ray and plane
    float distToIntersection = VectLen(outIntersection - P0);
    if( distToIntersection > rayLenght )
    {
        //int a=0;a++;
        return 0;
    }

    //return PointInTriangle( V0, V1, V2, outIntersection );

    // is I inside T?
    float    uu, uv, vv, wu, wv, D;
    uu = Dot(u,u);
    uv = Dot(u,v);
    vv = Dot(v,v);
    w = outIntersection - V0;
    wu = Dot(w,u);
    wv = Dot(w,v);
    D = uv * uv - uu * vv;

    // get and test parametric coords
    float s, t;
    s = (uv * wv - vv * wu) / D;
    if (s < 0.0 || s > 1.0)         // outIntersection is outside T
        return 0;
    t = (uv * wu - uu * wv) / D;
    if (t < 0.0 || (s + t) > 1.0)  // outIntersection is outside T
        return 0;



    return 1;                       // outIntersection is in T
}


Bool MathUtils::RayVsTriangle (
                                 const tVect3& P
                                ,const tVect3& dir
                                ,float rayLenght
                                ,const tVect3& A
                                ,const tVect3& B
                                ,const tVect3& C
                                ,tVect3& out
                                )
{
    out = nullVect;
    tVect3 n = Cross( B - A, C-A );
    float lenN = VectNor(n);

    float d = Dot( n, A );
    THOT_ASSERT( fequals(Dot(n,B),d ) && fequals(Dot(n,C),d ), "Dot(n,B) = [%f]", Dot(n,B) );

    if( fequals( Dot(n,dir), 0.f ))
    {
        return false;
    }

    float  t = ( d - Dot(n,P) ) / ( Dot(n,dir) );


    out = P + t * dir;
    if( t < rayLenght )
    {
        return false;
    }

    if( ! MathUtils::PointInTriangle( A, B, C, out  ) )
    {
        return false;
    }


    return true;
}

//--------------------------------------------------------------------------------
Bool MathUtils::SegmentVsTriangle           (          
                                                                const tVect3& FromPoint
                                                                ,const tVect3& ToPoint
                                                                ,const tVect3& V0
                                                                ,const tVect3& V1
                                                                ,const tVect3& V2
                                                                ,tVect3& out
                                                                )
{
    tVect3 n = Cross(V0-V1, V0-V2);
    VectNor(n);

    return false;
}









