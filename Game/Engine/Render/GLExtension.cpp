#include "Render_PCH.h"
#include "GLExtension.h"
#include "Textures/Texture.h"


template<>
u32 GetGlTypeID<float>( const float& dummy )
{
    return gl::FLOAT;
}

template<>
GLenum GetGlTypeID<u8>( const u8& dummy )
{
    return gl::UNSIGNED_BYTE;
}

template<>
GLenum GetGlTypeID<u16>( const u16& dummy)
{
    return gl::UNSIGNED_SHORT;
}

template<>
GLenum GetGlTypeID<u32>( const u32& dummy )
{
    return gl::UNSIGNED_INT;
}

template<>
GLenum GetGlTypeID<s32>( const s32& dummy )
{ 
    return gl::INT;
}



GLenum  gl::GetEnum   ( EBufferAcces acces )
{
    static const GLenum s_aAcces[] = {
                                     gl::READ_ONLY
                                    ,gl::WRITE_ONLY
                                    ,gl::READ_WRITE
                                    };

    return s_aAcces[acces];
}


GLenum gl::GetEnum ( EBufferUsage usage )
{
    static const GLenum s_aUsage[] = {
                                         gl::STREAM_DRAW
                                        ,gl::STREAM_READ
                                        ,gl::STREAM_COPY
                                        ,gl::STATIC_DRAW
                                        ,gl::STATIC_READ
                                        ,gl::STATIC_COPY
                                        ,gl::DYNAMIC_DRAW
                                        ,gl::DYNAMIC_READ
                                        ,gl::DYNAMIC_COPY
                                    };

    return s_aUsage[usage];
}



GLenum gl::GetEnum ( eGeometricPrimitive geomPrimitive )
{
    static const GLenum s_aGeomPrim[] = { 
                                             gl::POINTS
                                            ,gl::LINES
                                            ,gl::LINE_STRIP
                                            ,gl::LINE_LOOP
                                            ,gl::TRIANGLES
                                            ,gl::TRIANGLE_STRIP
                                            ,gl::TRIANGLE_FAN
                                            ,gl::QUADS
                                            };

    return s_aGeomPrim[geomPrimitive];
}

//void    DrawElements( eGeometricPrimitive primitive, u32 count, u32* indices )
//{
//RENDER_GUARD_BLOCK
//    gl::DrawElements( gl::GetEnum(primitive), count, gl::UNSIGNED_INT, indices );
//}

void gl::DrawArrays ( eGeometricPrimitive primitive, u32 beginIdx, u32 count, Bool dummy )
{
RENDER_GUARD_BLOCK
    gl::DrawArrays( gl::GetEnum(primitive), beginIdx, count );
}


#undef GL_ARRAY_ENUM_ASSERT