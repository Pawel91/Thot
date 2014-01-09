#ifndef __TEXTURE_TYPES_H__
#define __TEXTURE_TYPES_H__


//--------------------------------------------------------------------------------
class CTexture;
typedef unsigned int        TNativeTextureHandle;
const TNativeTextureHandle  INVALID_TEXTURE_HANDLE(-1);
const u32                   INVALID_TEXTURE_PROP_VALUE(-1);

enum
{
     TEXTURE_MAX_TEXTURE_UNITS      = 80
    ,TEXTURE_TYPE_COUNT             = 4 // 1D, 2D, 3D, CubeMap

    //LINEAR
    //NEAREST_MIPMAP_NEAREST        // use the mipmap level closest to the polygon resolution and use nearest on that level
    //NEAREST_MIPMAP_LINEAR         // use the mipmap level closest to the polygon resolution and use linear on that level
    //LINEAR_MIPMAP_NEAREST         // use nearest on the two levels closest to the polygon resolution  and lineary interpolate between the two values
    //LINEAR_MIPMAP_LINEAR          // use bilinear filtering to obtain samples from the two levels closest  to the polygon resolution and then lineary interpolate between them. aka trilinear filtering
    ,TEXTURE_MIN_FILTER_COUNT       = 6
    ,TEXTURE_MAX_FILTER_COUNT       = 2 // nearest and linear
};

enum eTextureWrapMode
{
     E_WRAP_MODE_NONE        = -1
    
     ,E_WRAP_MODE_CLAMP
     ,E_WRAP_MODE_REPEAT
     ,E_WRAP_MODE_CLAMP_TO_EDGE
     ,E_WRAP_MODE_CLAMP_TO_BORDER
     ,E_WRAP_MODE_MIRRORED_REPEAT

     ,E_WRAP_MODE_COUNT
};


//enum eTextureWrapCoord
//{
//     E_TEXTURE_WRAP_COORD_NONE      = -1
//    ,E_TEXTURE_WRAP_COORD_S
//    ,E_TEXTURE_WRAP_COORD_T
//    ,E_TEXTURE_WRAP_COORD_R
//
//    ,E_TEXTURE_WRAP_COORD_COUNT
//};



enum ECubemapFace
{
     E_CUBMAP_FACE_NONE      =-1
    ,E_CUBMAP_FACE_POSITIVE_X
    ,E_CUBMAP_FACE_NEGATIVE_X
    ,E_CUBMAP_FACE_POSITIVE_Y
    ,E_CUBMAP_FACE_NEGATIVE_Y
    ,E_CUBMAP_FACE_POSITIVE_Z
    ,E_CUBMAP_FACE_NEGATIVE_Z

    ,E_CUBMAP_FACE_COUNT

};
THOT_COMPILE_ASSERT2( E_CUBMAP_FACE_COUNT == 6, "Cubmap faces must equal 6" );




#endif /*__TEXTURE_TYPES_H__*/