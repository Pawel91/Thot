#pragma once
#ifndef __RENDER_MATERIAL_H__
#define __RENDER_MATERIAL_H__

#include "../Color.h"


class RENDER_API CMaterial
{
public:
    CMaterial   ( );
    ~CMaterial  ( );

    CColor      m_diffuse;
    CColor      m_ambient;
    CColor      m_specular;
    float       m_shininess;
    float       m_opacity;

    Bool        Bind    ( );    // send the material data to shader;


static CMaterial GetMaterial( const CColor& color );
};




#endif /*__RENDER_MATERIAL_H__*/