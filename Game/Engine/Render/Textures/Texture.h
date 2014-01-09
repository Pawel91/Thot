//  [11/11/2013 Radu]
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

class CString;

struct SGLTextureHeader
{
static  const u32   MAGIC_NUMBER = 'OPGL';
static  const u32   MAX_MIP_MAP_COUNT = 12;

    //Must be GL_TEXTURE_2D, GL_PROXY_TEXTURE_2D, GL_TEXTURE_1D_ARRAY, GL_PROXY_TEXTURE_1D_ARRAY, GL_TEXTURE_RECTANGLE,
    //GL_PROXY_TEXTURE_RECTANGLE, GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 
    //GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, or GL_PROXY_TEXTURE_CUBE_MAP
    u32     m_magicNumber;
    u32     m_target; 

    // number of mipmaps of this texture
    union
    {
        u32     m_levels;
        u32     m_mipMapCount;
    };

    //Specifies the number of color components in the texture. Must be one of base internal formats given in Table 1, 
    //one of the sized internal formats given in Table 2, or one of the compressed internal formats given in Table 3, below.
    u32     m_internalFormat;

    // the width of the texture
    u32     m_width;

    // height of the texture
    u32     m_height;

    // depth of the texture; for 3D textures
    u32     m_depth;

    u32     m_format;
    u32     m_pixelType;

    u32     m_isCompressed;
    u32     m_totalSize;    // total size of the texture

    u32     m_mipOffsets[MAX_MIP_MAP_COUNT];    //offsets to the mip data; miplevel "i" data is found between m_mipOffsets[i] and m_mipOffsets[i+1];
    u32     m_mipSizes[MAX_MIP_MAP_COUNT];      // size of each mip
};

#include "Render/Textures/TextureTypes.h"

u32 DebugLoadTexture( const CString& fileName );


struct RENDER_API STextureProperties
{
    STextureProperties();

    TNativeTextureHandle            m_nativeTextureHandle;
    u32                             m_textureType;
    u32                             m_textureUnit;
};


class RENDER_API CTexture
{

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
     CTexture();
    ~CTexture();



//*********************************************
//            INTERFACE
//*********************************************
public:

            void                        DebugLoad( const CString& fileName);
            

            const STextureProperties&   GetProperties()const        { return m_properties;}
            STextureProperties          GetProperties()             { return m_properties;}
            Bool                        IsValid()const;
            void                        Bind()const;
            void                        SetTextureUnit( u32 textureUnit) { m_properties.m_textureUnit = textureUnit;}

//*********************************************
//            MEMBERS
//*********************************************
private:
    STextureProperties          m_properties;
};

#endif