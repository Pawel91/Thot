#include "MathCore_PCH.h"
#include "Mat4.h"

m4x4::m4x4( )
{
}

m4x4::m4x4(    float _11, float _12, float _13, float _14
            ,float _21, float _22, float _23, float _24
            ,float _31, float _32, float _33, float _34 
            ,float _41, float _42, float _43, float _44
)
{
    this->_11 = _11;
    this->_12 = _12;
    this->_13 = _13;
    this->_14 = _14;

    this->_21 = _21;
    this->_22 = _22;
    this->_23 = _23;
    this->_24 = _24;

    this->_31 = _31;
    this->_32 = _32;
    this->_33 = _33;
    this->_34 = _34;

    this->_41 = _41;
    this->_42 = _42;
    this->_43 = _43;
    this->_44 = _44;

}

m4x4::m4x4( const m4x4& other )
{
    for( register int i=0; i<16; i++ )
        m[i] = other.m[i];
}


void m4x4::DebugTrace    ( )const
{
    for( register int i=1; i<=4; i++ )
    {
        for( register int j=1; j<=4; j++  )
            THOT_TRACE("%.3f  ", m[4*(i-1) + j-1]);
        THOT_TRACE("\n");
    }

}


void m4x4::DebugTrace( const char* tag )const
{
    if( tag != NULL)
    {
        THOT_TRACE_LINE("%s", tag);
    }
    DebugTrace();
}