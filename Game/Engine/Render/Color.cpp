#include "Render_PCH.h"
#include "Color.h"

RENDER_API const CColor     black       ( 0.f, 0.f, 0.f, 1.f );
RENDER_API const CColor     red         ( 1.f, 0.f, 0.f, 1.f );
RENDER_API const CColor     green       ( 0.f, 1.f, 0.f, 1.f );
RENDER_API const CColor     blue        ( 0.f, 0.f, 1.f, 1.f );


CColor::CColor()
:r        ( 0.f )
,g        ( 0.f )
,b        ( 0.f )
,a        ( 1.f )
{}

CColor::CColor( const CColor& other )
:r        ( other.r )
,g        ( other.g )
,b        ( other.b )
,a        ( other.a )
{

}

CColor::CColor( float _r, float _g, float _b )
:r        ( _r )
,g        ( _g )
,b        ( _b )
,a        ( 1.f )
{
}

CColor::CColor( float _r, float _g, float _b, float _a )
:r        ( _r )
,g        ( _g )
,b        ( _b )
,a        ( _a )
{
}

CColor::~CColor()
{

}
