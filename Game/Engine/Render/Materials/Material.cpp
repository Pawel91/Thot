#include "Render_PCH.h"
#include "Material.h"
#include "../ShaderFramework/Shader.h"

#ifndef DECLARE_DEFAULT_CONSTRUCTOR_LIST
#define DECLARE_DEFAULT_CONSTRUCTOR_LIST \
    :m_diffuse      ( 1.f, 0.f, 0.f, 1.f )    \
    ,m_ambient      ( 1.f, 0.f, 0.f, 1.f )   \
    ,m_specular     ( 1.f, 0.f, 0.f, 1.f )\
    ,m_shininess    ( 200.f )   \
    ,m_opacity      ( 1.f )
#else
#error DECLARE_DEFAULT_CONSTRUCTOR_LIST is allready defined

#endif /*DECLARE_DEFAULT_CONSTRUCTOR_LIST*/


CMaterial::CMaterial   ( )
    DECLARE_DEFAULT_CONSTRUCTOR_LIST
{

}


CMaterial::~CMaterial  ( )
{

}


#undef DECLARE_DEFAULT_CONSTRUCTOR_LIST




Bool CMaterial::Bind( )
{
    //if( !CShader::GetCurrentShader() )
    {
        return false;
    }



    //return true;
}


CMaterial CMaterial::GetMaterial( const CColor& color )
{
    CMaterial material;
    material.m_ambient = color;
    material.m_diffuse = color;
    material.m_specular = color;

    return material;
}