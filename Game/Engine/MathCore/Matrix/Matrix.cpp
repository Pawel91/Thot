#include "MathCore_PCH.h"
#include "MathCore\Matrix\Matrix.h"
#include "MathCore\Quaternion\Quat.h"
//m3x3::m3x3 (    float _11, float _12, float _13
//                ,float _21, float _22, float _23
//                ,float _31, float _32, float _33 )
//{
//    this->_11 = _11;
//    this->_12 = _12;
//    this->_13 = _13;
//
//    this->_21 = _21;
//    this->_22 = _22;
//    this->_23 = _23;
//
//    this->_31 = _31;
//    this->_32 = _32;
//    this->_33 = _33;
//}


void /*_fastcall*/    MakeMatFromQuat    ( const tQuat& q, m3x3& out )
{
    out = i3x3;
    //out._11 = 1.f - 2.f * (q.y * q.y + q.z * q.z );
    //out._12 = 2.f * ( q.x * q.y + q.w * q.z );
    //out._13 = 2.f * ( q.x * q.z - q.w * q.y );
    //out._21 = 2.f * ( q.x * q.y - q.w * q.z );
    //out._22 = 1.f - 2.f * ( q.x * q.x + q.z * q.z );
    //out._23 = 2.f * ( q.y * q.z + q.w * q.x );
    //out._31 = 2.f * ( q.x * q.z + q.w * q.y );
    //out._32 = 2.f * ( q.y * q.z - q.w * q.x );
    //out._33 = 1.f - 2.f * ( q.x * q.x + q.y * q.y );
    
    out._11 = 1.f - 2.f * (q.y * q.y + q.z * q.z );
    out._21 = 2.f * ( q.x * q.y + q.w * q.z );
    out._31 = 2.f * ( q.x * q.z - q.w * q.y );
    out._12 = 2.f * ( q.x * q.y - q.w * q.z );
    out._22 = 1.f - 2.f * ( q.x * q.x + q.z * q.z );
    out._32 = 2.f * ( q.y * q.z + q.w * q.x );
    out._13 = 2.f * ( q.x * q.z + q.w * q.y );
    out._23 = 2.f * ( q.y * q.z - q.w * q.x );
    out._33 = 1.f - 2.f * ( q.x * q.x + q.y * q.y );

}

void /*_fastcall*/    MakeMatFromQuat    ( const tQuat&q, m4x4& out )
{
    out = i4x4;
    out._11 = 1.f - 2.f * (q.y * q.y + q.z * q.z );
    out._12 = 2.f * ( q.x * q.y + q.w * q.z );
    out._13 = 2.f * ( q.x * q.z - q.w * q.y );
    out._21 = 2.f * ( q.x * q.y - q.w * q.z );
    out._22 = 1.f - 2.f * ( q.x * q.x + q.z * q.z );
    out._23 = 2.f * ( q.y * q.z + q.w * q.x );
    out._31 = 2.f * ( q.x * q.z + q.w * q.y );
    out._32 = 2.f * ( q.y * q.z - q.w * q.x );
    out._33 = 1.f - 2.f * ( q.x * q.x + q.y * q.y );

}