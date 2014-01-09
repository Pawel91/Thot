#include "MathCore_PCH.h"
#include "MathCore\Vector\Vector.h"
#include "MathCore\Quaternion\Quat.h"


#pragma region VECT2
const tVect2     tVect2::nullVect( 0.f, 0.f );
const tVect2    tVect2::xAxis( 1.f, 0.f );
const tVect2    tVect2::yAxis( 0.f, 1.f );


tVect2::tVect2()
{
    // no init
}

tVect2::tVect2( float _x, float _y  )
:x(_x)
,y(_y)
{
}

tVect2::tVect2( const tVect2& other )
:x (other.x)
,y (other.y)
{
}

//float& tVect2::operator[] ( int nIdx )
//{
//    return this->v[nIdx];
//}
//
//const float& tVect2::operator[] ( int nIdx )const
//{
//    return this->v[nIdx];
//}

#pragma endregion VECT2

tVect3::tVect3()
{
    // no init
}

tVect3::tVect3( float _x, float _y, float _z )
:x(_x)
,y(_y)
,z(_z)
{
}

tVect3::tVect3( const tVect3& other )
:x(other.x)
,y(other.y)
,z(other.z)
{
}

tVect3::tVect3( const tQuat& q )
{
    x = q.x;
    y = q.y;
    z = q.z;
}

const tVect3&    tVect3::operator= ( const tQuat& q)
{
    x = q.x;
    y = q.y;
    z = q.z;

    return *this;
}

void tVect3::DbgTrace ( )const
{
    THOT_TRACE( "%.3f, %.3f, %.3f", x, y, z );
}


Bool tVect3::Equals ( const tVect3& other, float fEps )const
{
    for( u32 i=0; i<3; i++ )
    {
        if( !fequals( v[i], other.v[i], fEps ) )
        {
            return false;
        }
    }

    return true;
}