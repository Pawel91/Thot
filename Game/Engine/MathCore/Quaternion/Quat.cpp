#include "MathCore_PCH.h"
#include "Quat.h"

tQuat::tQuat( ){}
tQuat::tQuat( float _w, float _x, float _y, float _z)
{
    w = _w;
    x = _x;
    y = _y;
    z = _z;
}
tQuat::tQuat( const tQuat& other )
{
    w = other.w;
    x = other.x;
    y = other.y;
    z = other.z;
}

tQuat::tQuat ( const tVect3& axis, float alpha )
{
    MakeRotQuat( axis, alpha, (*this) );
}

tQuat::tQuat ( float _w, const tVect3& v )
{
    w = w;
    x = v.x;
    y = v.y;
    z = v.z;
}
