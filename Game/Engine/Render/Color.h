#ifndef __COLOR_H__
#define __COLOR_H__

#include "Kernel/Basics.h"
#include "Kernel/DataStructures/ArrayTypeBase.h"
#include "Render/RenderDef.h"

class RENDER_API CColor: public CArrayTypeBase<float>
{

public:
     CColor();
     CColor( const CColor& other );
     CColor( float r, float g, float b );
     CColor( float r, float g, float b, float a );
    ~CColor();



    operator    float*          ( );
    operator    const float*    ( )const;
    const CColor& operator =    ( const CColor& other ); 
    CColor          operator +  ( const CColor& other );
    CColor          operator *  ( float factor );
    CColor          operator *  ( const CColor& other );


    union 
    {
        float c[4];
        struct
        {
            float r,g,b,a;
        };
    };
};

extern RENDER_API const CColor    black;
extern RENDER_API const CColor    red;
extern RENDER_API const CColor    green;
extern RENDER_API const CColor    blue;

THOT_FORCE_INLINE CColor CColor::operator *  ( float factor )
{
    CColor outColor = *this;
    outColor.r *= factor;
    outColor.g *= factor;
    outColor.b *= factor;
    outColor.a *= factor;

    return outColor;
}

THOT_FORCE_INLINE CColor CColor::operator *  ( const CColor& other )
{
    CColor outColor = *this;
    outColor.r *= other.r;
    outColor.g *= other.g;
    outColor.b *= other.b;
    outColor.a *= other.a;

    return outColor;
}

inline const CColor& CColor::operator =    ( const CColor& other )
{
    for( int i=0; i<4; i++ )
        c[i] = other.c[i];

    return *this;
}

THOT_FORCE_INLINE CColor::operator float*()
{
    return c;
}

THOT_FORCE_INLINE CColor::operator const float*    ( )const
{
    return c;
}

THOT_FORCE_INLINE CColor CColor::operator+( const CColor& other )
{
    CColor color;
    for( int i=0; i<4; i++ )
        {
            color.c[i] = c[i] + other.c[i];
        }

    return color;
}

#endif