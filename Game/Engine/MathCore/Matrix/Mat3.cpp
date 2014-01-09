#include "MathCore_PCH.h"
#include "Mat3.h"

m3x3::m3x3 ()
{
    // no init
}

m3x3::m3x3 ( const m3x3& other )
{
    for( register int i=0; i<9; i++ )
        m[i] = other.m[i];
}

m3x3::m3x3 (    float _11, float _12, float _13
                ,float _21, float _22, float _23
                ,float _31, float _32, float _33 )
{
    this->_11 = _11;
    this->_12 = _12;
    this->_13 = _13;

    this->_21 = _21;
    this->_22 = _22;
    this->_23 = _23;

    this->_31 = _31;
    this->_32 = _32;
    this->_33 = _33;
}


void m3x3::DebugTrace    ( )
{
    for( register int i=1; i<=3; i++ )
    {
        for( register int j=1; j<=3; j++  )
            THOT_TRACE("%.3f  ", m[3*(i-1) + j-1]);
        THOT_TRACE("\n");
    }
}