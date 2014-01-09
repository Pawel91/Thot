#pragma once
#ifndef __GL_EXTENSION_H__
#define __GL_EXTENSION_H__

#include "MathCore\MathCore.h"
#include "Render\Color.h"

#include "Render\GLWrapper\OpenGL.h"

#include "windows.h"



#define GL_GLEXT_PROTOTYPES
//#include "glext.h"

#include "Images/ImageTypes.h"
#include "Textures/TextureTypes.h"
#include "Render\Render.h"
#include "Render/Buffers/BufferTypes.h"

namespace gl
{
 
//[TODO] remove these functions from here
GLenum  GetEnum     ( EBufferAcces acces );
GLenum  GetEnum     ( EBufferUsage usage );
GLenum  GetEnum     ( eGeometricPrimitive geomPrimitive );
void    DrawArrays  ( eGeometricPrimitive primitive, u32 beginIdx, u32 count, Bool dummy );
//void    DrawElements( eGeometricPrimitive primitive, u32 count, u32* indices );
}

template <class T>
u32  GetGlTypeID(const T& dummy )
{
    THOT_COMPILE_ASSERT2( sizeof(T)==0, "FUNCTION[GetGlTypeID]: MUST BE USE ONLY SPECIALIZED" );
}

extern template
u32  GetGlTypeID<float>( const float& dummy );

extern template
RENDER_API u32 GetGlTypeID<u8>( const u8& dummy );

extern template
u32 GetGlTypeID<u16>( const u16& dummy );


extern template
GLenum GetGlTypeID<u32>( const u32& dummy );

extern template
GLenum GetGlTypeID<s32>( const s32& dummy );


#endif /*__GL_EXTENSION_H__*/