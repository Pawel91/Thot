#ifndef FUNCTION_CPP_GENERATED_HEADEROPENGL_HPP
#define FUNCTION_CPP_GENERATED_HEADEROPENGL_HPP

#include "Render/RenderDef.h"

#if defined(__glew_h__) || defined(__GLEW_H__)
#error Attempt to include auto-generated header after including glew.h
#endif
#if defined(__gl_h_) || defined(__GL_H__)
#error Attempt to include auto-generated header after including gl.h
#endif
#if defined(__glext_h_) || defined(__GLEXT_H_)
#error Attempt to include auto-generated header after including glext.h
#endif
#if defined(__gltypes_h_)
#error Attempt to include auto-generated header after gltypes.h
#endif
#if defined(__gl_ATI_h_)
#error Attempt to include auto-generated header after including glATI.h
#endif

#define __glew_h__
#define __GLEW_H__
#define __gl_h_
#define __GL_H__
#define __glext_h_
#define __GLEXT_H_
#define __gltypes_h_
#define __gl_ATI_h_

#ifndef APIENTRY
	#if defined(__MINGW32__)
		#ifndef WIN32_LEAN_AND_MEAN
			#define WIN32_LEAN_AND_MEAN 1
		#endif
		#ifndef NOMINMAX
			#define NOMINMAX
		#endif
		#include <windows.h>
	#elif (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED) || defined(__BORLANDC__)
		#ifndef WIN32_LEAN_AND_MEAN
			#define WIN32_LEAN_AND_MEAN 1
		#endif
		#ifndef NOMINMAX
			#define NOMINMAX
		#endif
		#include <windows.h>
	#else
		#define APIENTRY
	#endif
#endif /*APIENTRY*/

#ifndef CODEGEN_FUNCPTR
	#define CODEGEN_REMOVE_FUNCPTR
	#if defined(_WIN32)
		#define CODEGEN_FUNCPTR APIENTRY
	#else
		#define CODEGEN_FUNCPTR
	#endif
#endif /*CODEGEN_FUNCPTR*/

#ifndef GLAPI
	#define GLAPI extern
#endif


#ifndef GL_LOAD_GEN_BASIC_OPENGL_TYPEDEFS
#define GL_LOAD_GEN_BASIC_OPENGL_TYPEDEFS


#endif /*GL_LOAD_GEN_BASIC_OPENGL_TYPEDEFS*/

#include <stddef.h>
#ifndef GLEXT_64_TYPES_DEFINED
/* This code block is duplicated in glxext.h, so must be protected */
#define GLEXT_64_TYPES_DEFINED
/* Define int32_t, int64_t, and uint64_t types for UST/MSC */
/* (as used in the GL_EXT_timer_query extension). */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#include <inttypes.h>
#elif defined(__sun__) || defined(__digital__)
#include <inttypes.h>
#if defined(__STDC__)
#if defined(__arch64__) || defined(_LP64)
typedef long int int64_t;
typedef unsigned long int uint64_t;
#else
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
#endif /* __arch64__ */
#endif /* __STDC__ */
#elif defined( __VMS ) || defined(__sgi)
#include <inttypes.h>
#elif defined(__SCO__) || defined(__USLC__)
#include <stdint.h>
#elif defined(__UNIXOS2__) || defined(__SOL64__)
typedef long int int32_t;
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
#elif defined(_WIN32) && defined(__GNUC__)
#include <stdint.h>
#elif defined(_WIN32)
typedef __int32 int32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
/* Fallback if nothing above works */
#include <inttypes.h>
#endif
#endif
	typedef unsigned int GLenum;
	typedef unsigned char GLboolean;
	typedef unsigned int GLbitfield;
	typedef void GLvoid;
	typedef signed char GLbyte;
	typedef short GLshort;
	typedef int GLint;
	typedef unsigned char GLubyte;
	typedef unsigned short GLushort;
	typedef unsigned int GLuint;
	typedef int GLsizei;
	typedef float GLfloat;
	typedef float GLclampf;
	typedef double GLdouble;
	typedef double GLclampd;
	typedef char GLchar;
	typedef char GLcharARB;
	#ifdef __APPLE__
typedef void *GLhandleARB;
#else
typedef unsigned int GLhandleARB;
#endif
		typedef unsigned short GLhalfARB;
		typedef unsigned short GLhalf;
		typedef GLint GLfixed;
		typedef ptrdiff_t GLintptr;
		typedef ptrdiff_t GLsizeiptr;
		typedef int64_t GLint64;
		typedef uint64_t GLuint64;
		typedef ptrdiff_t GLintptrARB;
		typedef ptrdiff_t GLsizeiptrARB;
		typedef int64_t GLint64EXT;
		typedef uint64_t GLuint64EXT;
		typedef struct __GLsync *GLsync;
		struct _cl_context;
		struct _cl_event;
		typedef void (APIENTRY *GLDEBUGPROC)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
		typedef void (APIENTRY *GLDEBUGPROCARB)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
		typedef void (APIENTRY *GLDEBUGPROCAMD)(GLuint id,GLenum category,GLenum severity,GLsizei length,const GLchar *message,void *userParam);
		typedef unsigned short GLhalfNV;
		typedef GLintptr GLvdpauSurfaceNV;


#if defined(TRUE)
    const int __trueDefined = TRUE;
#   undef TRUE
    const int TRUE = __trueDefined;
#endif //TRUE


#if defined(FALSE)
    const unsigned int __falseDefined = FALSE;
#   undef FALSE
    const unsigned int FALSE = __falseDefined;
#endif //TRUE

#if defined(NO_ERROR)
    const unsigned int __noerrordefine = NO_ERROR;
#   undef NO_ERROR
    const unsigned int NO_ERROR = __noerrordefine;
#endif

#define OPENGL_API RENDER_API

namespace gl
{
	namespace exts
	{
		class LoadTest
		{
		private:
			//Safe bool idiom. Joy!
			typedef void (LoadTest::*bool_type)() const;
			void big_long_name_that_really_doesnt_matter() const {}
			
		public:
			operator bool_type() const
			{
				return m_isLoaded ? &LoadTest::big_long_name_that_really_doesnt_matter : 0;
			}
			
			int GetNumMissing() const {return m_numMissing;}
			
			LoadTest() : m_isLoaded(false), m_numMissing(0) {}
			LoadTest(bool isLoaded, int numMissing) : m_isLoaded(isLoaded), m_numMissing(numMissing) {}
		private:
			bool m_isLoaded;
			int m_numMissing;
		};
		
		extern LoadTest var_ARB_texture_compression;
		extern LoadTest var_EXT_texture_compression_s3tc;
		extern LoadTest var_ARB_program_interface_query;
		
	} //namespace exts



#define GL_ENUM(__name, __val) \
    __name = __val,

#define GL_EXPAND_ENUM \
GL_ENUM( COMPRESSED_ALPHA_ARB                                , 0x84E9 )                                     \
GL_ENUM( COMPRESSED_INTENSITY_ARB                            , 0x84EC )                                     \
GL_ENUM( COMPRESSED_LUMINANCE_ALPHA_ARB                      , 0x84EB )                                     \
GL_ENUM( COMPRESSED_LUMINANCE_ARB                            , 0x84EA )                                     \
GL_ENUM( COMPRESSED_RGBA_ARB                                 , 0x84EE )                                     \
GL_ENUM( COMPRESSED_RGB_ARB                                  , 0x84ED )                                     \
GL_ENUM( COMPRESSED_TEXTURE_FORMATS_ARB                      , 0x86A3 )                                     \
GL_ENUM( NUM_COMPRESSED_TEXTURE_FORMATS_ARB                  , 0x86A2 )                                     \
GL_ENUM( TEXTURE_COMPRESSED_ARB                              , 0x86A1 )                                     \
GL_ENUM( TEXTURE_COMPRESSED_IMAGE_SIZE_ARB                   , 0x86A0 )                                     \
GL_ENUM( TEXTURE_COMPRESSION_HINT_ARB                        , 0x84EF )                                     \
GL_ENUM( COMPRESSED_RGBA_S3TC_DXT1_EXT                       , 0x83F1 )                                     \
GL_ENUM( COMPRESSED_RGBA_S3TC_DXT3_EXT                       , 0x83F2 )                                     \
GL_ENUM( COMPRESSED_RGBA_S3TC_DXT5_EXT                       , 0x83F3 )                                     \
GL_ENUM( COMPRESSED_RGB_S3TC_DXT1_EXT                        , 0x83F0 )                                     \
GL_ENUM( ACTIVE_RESOURCES                                    , 0x92F5 )                                     \
GL_ENUM( ACTIVE_VARIABLES                                    , 0x9305 )                                     \
GL_ENUM( ARRAY_SIZE                                          , 0x92FB )                                     \
GL_ENUM( ARRAY_STRIDE                                        , 0x92FE )                                     \
GL_ENUM( ATOMIC_COUNTER_BUFFER                               , 0x92C0 )                                     \
GL_ENUM( ATOMIC_COUNTER_BUFFER_INDEX                         , 0x9301 )                                     \
GL_ENUM( BLOCK_INDEX                                         , 0x92FD )                                     \
GL_ENUM( BUFFER_BINDING                                      , 0x9302 )                                     \
GL_ENUM( BUFFER_DATA_SIZE                                    , 0x9303 )                                     \
GL_ENUM( BUFFER_VARIABLE                                     , 0x92E5 )                                     \
GL_ENUM( COMPATIBLE_SUBROUTINES                              , 0x8E4B )                                     \
GL_ENUM( COMPUTE_SUBROUTINE                                  , 0x92ED )                                     \
GL_ENUM( COMPUTE_SUBROUTINE_UNIFORM                          , 0x92F3 )                                     \
GL_ENUM( FRAGMENT_SUBROUTINE                                 , 0x92EC )                                     \
GL_ENUM( FRAGMENT_SUBROUTINE_UNIFORM                         , 0x92F2 )                                     \
GL_ENUM( GEOMETRY_SUBROUTINE                                 , 0x92EB )                                     \
GL_ENUM( GEOMETRY_SUBROUTINE_UNIFORM                         , 0x92F1 )                                     \
GL_ENUM( IS_PER_PATCH                                        , 0x92E7 )                                     \
GL_ENUM( IS_ROW_MAJOR                                        , 0x9300 )                                     \
GL_ENUM( LOCATION                                            , 0x930E )                                     \
GL_ENUM( LOCATION_INDEX                                      , 0x930F )                                     \
GL_ENUM( MATRIX_STRIDE                                       , 0x92FF )                                     \
GL_ENUM( MAX_NAME_LENGTH                                     , 0x92F6 )                                     \
GL_ENUM( MAX_NUM_ACTIVE_VARIABLES                            , 0x92F7 )                                     \
GL_ENUM( MAX_NUM_COMPATIBLE_SUBROUTINES                      , 0x92F8 )                                     \
GL_ENUM( NAME_LENGTH                                         , 0x92F9 )                                     \
GL_ENUM( NUM_ACTIVE_VARIABLES                                , 0x9304 )                                     \
GL_ENUM( NUM_COMPATIBLE_SUBROUTINES                          , 0x8E4A )                                     \
GL_ENUM( OFFSET                                              , 0x92FC )                                     \
GL_ENUM( PROGRAM_INPUT                                       , 0x92E3 )                                     \
GL_ENUM( PROGRAM_OUTPUT                                      , 0x92E4 )                                     \
GL_ENUM( REFERENCED_BY_COMPUTE_SHADER                        , 0x930B )                                     \
GL_ENUM( REFERENCED_BY_FRAGMENT_SHADER                       , 0x930A )                                     \
GL_ENUM( REFERENCED_BY_GEOMETRY_SHADER                       , 0x9309 )                                     \
GL_ENUM( REFERENCED_BY_TESS_CONTROL_SHADER                   , 0x9307 )                                     \
GL_ENUM( REFERENCED_BY_TESS_EVALUATION_SHADER                , 0x9308 )                                     \
GL_ENUM( REFERENCED_BY_VERTEX_SHADER                         , 0x9306 )                                     \
GL_ENUM( SHADER_STORAGE_BLOCK                                , 0x92E6 )                                     \
GL_ENUM( TESS_CONTROL_SUBROUTINE                             , 0x92E9 )                                     \
GL_ENUM( TESS_CONTROL_SUBROUTINE_UNIFORM                     , 0x92EF )                                     \
GL_ENUM( TESS_EVALUATION_SUBROUTINE                          , 0x92EA )                                     \
GL_ENUM( TESS_EVALUATION_SUBROUTINE_UNIFORM                  , 0x92F0 )                                     \
GL_ENUM( TOP_LEVEL_ARRAY_SIZE                                , 0x930C )                                     \
GL_ENUM( TOP_LEVEL_ARRAY_STRIDE                              , 0x930D )                                     \
GL_ENUM( TRANSFORM_FEEDBACK_VARYING                          , 0x92F4 )                                     \
GL_ENUM( TYPE                                                , 0x92FA )                                     \
GL_ENUM( UNIFORM                                             , 0x92E1 )                                     \
GL_ENUM( UNIFORM_BLOCK                                       , 0x92E2 )                                     \
GL_ENUM( VERTEX_SUBROUTINE                                   , 0x92E8 )                                     \
GL_ENUM( VERTEX_SUBROUTINE_UNIFORM                           , 0x92EE )                                     \
GL_ENUM( ALPHA                                               , 0x1906 )                                     \
GL_ENUM( ALWAYS                                              , 0x0207 )                                     \
GL_ENUM( AND                                                 , 0x1501 )                                     \
GL_ENUM( AND_INVERTED                                        , 0x1504 )                                     \
GL_ENUM( AND_REVERSE                                         , 0x1502 )                                     \
GL_ENUM( BACK                                                , 0x0405 )                                     \
GL_ENUM( BACK_LEFT                                           , 0x0402 )                                     \
GL_ENUM( BACK_RIGHT                                          , 0x0403 )                                     \
GL_ENUM( BLEND                                               , 0x0BE2 )                                     \
GL_ENUM( BLEND_DST                                           , 0x0BE0 )                                     \
GL_ENUM( BLEND_SRC                                           , 0x0BE1 )                                     \
GL_ENUM( BLUE                                                , 0x1905 )                                     \
GL_ENUM( BYTE                                                , 0x1400 )                                     \
GL_ENUM( CCW                                                 , 0x0901 )                                     \
GL_ENUM( CLEAR                                               , 0x1500 )                                     \
GL_ENUM( COLOR                                               , 0x1800 )                                     \
GL_ENUM( COLOR_BUFFER_BIT                                    , 0x00004000 )                                 \
GL_ENUM( COLOR_CLEAR_VALUE                                   , 0x0C22 )                                     \
GL_ENUM( COLOR_LOGIC_OP                                      , 0x0BF2 )                                     \
GL_ENUM( COLOR_WRITEMASK                                     , 0x0C23 )                                     \
GL_ENUM( COPY                                                , 0x1503 )                                     \
GL_ENUM( COPY_INVERTED                                       , 0x150C )                                     \
GL_ENUM( CULL_FACE                                           , 0x0B44 )                                     \
GL_ENUM( CULL_FACE_MODE                                      , 0x0B45 )                                     \
GL_ENUM( CW                                                  , 0x0900 )                                     \
GL_ENUM( DECR                                                , 0x1E03 )                                     \
GL_ENUM( DEPTH                                               , 0x1801 )                                     \
GL_ENUM( DEPTH_BUFFER_BIT                                    , 0x00000100 )                                 \
GL_ENUM( DEPTH_CLEAR_VALUE                                   , 0x0B73)                                      \
GL_ENUM( DEPTH_COMPONENT                                     , 0x1902)                                      \
GL_ENUM( DEPTH_FUNC                                          , 0x0B74)                                      \
GL_ENUM( DEPTH_RANGE                                         , 0x0B70)                                      \
GL_ENUM( DEPTH_TEST                                          , 0x0B71)                                      \
GL_ENUM( DEPTH_WRITEMASK                                     , 0x0B72)                                      \
GL_ENUM( DITHER                                              , 0x0BD0)                                      \
GL_ENUM( DONT_CARE                                           , 0x1100)                                      \
GL_ENUM( DOUBLE                                              , 0x140A)                                      \
GL_ENUM( DOUBLEBUFFER                                        , 0x0C32)                                      \
GL_ENUM( DRAW_BUFFER                                         , 0x0C01)                                      \
GL_ENUM( DST_ALPHA                                           , 0x0304)                                      \
GL_ENUM( DST_COLOR                                           , 0x0306)                                      \
GL_ENUM( EQUAL                                               , 0x0202)                                      \
GL_ENUM( EQUIV                                               , 0x1509)                                      \
GL_ENUM( EXTENSIONS                                          , 0x1F03)                                      \
GL_ENUM( FALSE                                               , 0       )                                    \
GL_ENUM( FASTEST                                             , 0x1101 )                                     \
GL_ENUM( FILL                                                , 0x1B02 )                                     \
GL_ENUM( FLOAT                                               , 0x1406 )                                     \
GL_ENUM( FRONT                                               , 0x0404 )                                     \
GL_ENUM( FRONT_AND_BACK                                      , 0x0408 )                                     \
GL_ENUM( FRONT_FACE                                          , 0x0B46 )                                     \
GL_ENUM( FRONT_LEFT                                          , 0x0400 )                                     \
GL_ENUM( FRONT_RIGHT                                         , 0x0401 )                                     \
GL_ENUM( GEQUAL                                              , 0x0206 )                                     \
GL_ENUM( GREATER                                             , 0x0204 )                                     \
GL_ENUM( GREEN                                               , 0x1904 )                                     \
GL_ENUM( INCR                                                , 0x1E02 )                                     \
GL_ENUM( INT                                                 , 0x1404 )                                     \
GL_ENUM( INVALID_ENUM                                        , 0x0500 )                                     \
GL_ENUM( INVALID_OPERATION                                   , 0x0502 )                                     \
GL_ENUM( INVALID_VALUE                                       , 0x0501 )                                     \
GL_ENUM( INVERT                                              , 0x150A )                                     \
GL_ENUM( KEEP                                                , 0x1E00 )                                     \
GL_ENUM( LEFT                                                , 0x0406 )                                     \
GL_ENUM( LEQUAL                                              , 0x0203 )                                     \
GL_ENUM( LESS                                                , 0x0201 )                                     \
GL_ENUM( LINE                                                , 0x1B01 )                                     \
GL_ENUM( LINEAR                                              , 0x2601 )                                     \
GL_ENUM( LINEAR_MIPMAP_LINEAR                                , 0x2703 )                                     \
GL_ENUM( LINEAR_MIPMAP_NEAREST                               , 0x2701 )                                     \
GL_ENUM( LINES                                               , 0x0001 )                                     \
GL_ENUM( LINE_LOOP                                           , 0x0002 )                                     \
GL_ENUM( LINE_SMOOTH                                         , 0x0B20 )                                     \
GL_ENUM( LINE_SMOOTH_HINT                                    , 0x0C52 )                                     \
GL_ENUM( LINE_STRIP                                          , 0x0003 )                                     \
GL_ENUM( LINE_WIDTH                                          , 0x0B21 )                                     \
GL_ENUM( LINE_WIDTH_GRANULARITY                              , 0x0B23 )                                     \
GL_ENUM( LINE_WIDTH_RANGE                                    , 0x0B22 )                                     \
GL_ENUM( LOGIC_OP_MODE                                       , 0x0BF0 )                                     \
GL_ENUM( MAX_TEXTURE_SIZE                                    , 0x0D33 )                                     \
GL_ENUM( MAX_VIEWPORT_DIMS                                   , 0x0D3A )                                     \
GL_ENUM( NAND                                                , 0x150E )                                     \
GL_ENUM( NEAREST                                             , 0x2600 )                                     \
GL_ENUM( NEAREST_MIPMAP_LINEAR                               , 0x2702 )                                     \
GL_ENUM( NEAREST_MIPMAP_NEAREST                              , 0x2700 )                                     \
GL_ENUM( NEVER                                               , 0x0200 )                                     \
GL_ENUM( NICEST                                              , 0x1102 )                                     \
GL_ENUM( NONE                                                , 0      )                                     \
GL_ENUM( NOOP                                                , 0x1505 )                                     \
GL_ENUM( NOR                                                 , 0x1508 )                                     \
GL_ENUM( NOTEQUAL                                            , 0x0205 )                                     \
GL_ENUM( NO_ERROR                                            , 0      )                                     \
GL_ENUM( ONE                                                 , 1      )                                     \
GL_ENUM( ONE_MINUS_DST_ALPHA                                 , 0x0305 )                                     \
GL_ENUM( ONE_MINUS_DST_COLOR                                 , 0x0307 )                                     \
GL_ENUM( ONE_MINUS_SRC_ALPHA                                 , 0x0303 )                                     \
GL_ENUM( ONE_MINUS_SRC_COLOR                                 , 0x0301 )                                     \
GL_ENUM( OR                                                  , 0x1507 )                                     \
GL_ENUM( OR_INVERTED                                         , 0x150D )                                     \
GL_ENUM( OR_REVERSE                                          , 0x150B )                                     \
GL_ENUM( OUT_OF_MEMORY                                       , 0x0505 )                                     \
GL_ENUM( PACK_ALIGNMENT                                      , 0x0D05 )                                     \
GL_ENUM( PACK_LSB_FIRST                                      , 0x0D01 )                                     \
GL_ENUM( PACK_ROW_LENGTH                                     , 0x0D02 )                                     \
GL_ENUM( PACK_SKIP_PIXELS                                    , 0x0D04 )                                     \
GL_ENUM( PACK_SKIP_ROWS                                      , 0x0D03 )                                     \
GL_ENUM( PACK_SWAP_BYTES                                     , 0x0D00 )                                     \
GL_ENUM( POINT                                               , 0x1B00 )                                     \
GL_ENUM( POINTS                                              , 0x0000 )                                     \
GL_ENUM( POINT_SIZE                                          , 0x0B11 )                                     \
GL_ENUM( POINT_SIZE_GRANULARITY                              , 0x0B13 )                                     \
GL_ENUM( POINT_SIZE_RANGE                                    , 0x0B12 )                                     \
GL_ENUM( POLYGON_MODE                                        , 0x0B40 )                                     \
GL_ENUM( POLYGON_OFFSET_FACTOR                               , 0x8038 )                                     \
GL_ENUM( POLYGON_OFFSET_FILL                                 , 0x8037 )                                     \
GL_ENUM( POLYGON_OFFSET_LINE                                 , 0x2A02 )                                     \
GL_ENUM( POLYGON_OFFSET_POINT                                , 0x2A01 )                                     \
GL_ENUM( POLYGON_OFFSET_UNITS                                , 0x2A00 )                                     \
GL_ENUM( POLYGON_SMOOTH                                      , 0x0B41 )                                     \
GL_ENUM( POLYGON_SMOOTH_HINT                                 , 0x0C53 )                                     \
GL_ENUM( PROXY_TEXTURE_1D                                    , 0x8063 )                                     \
GL_ENUM( PROXY_TEXTURE_2D                                    , 0x8064 )                                     \
GL_ENUM( QUADS                                               , 0x0007 )                                     \
GL_ENUM( R3_G3_B2                                            , 0x2A10 )                                     \
GL_ENUM( READ_BUFFER                                         , 0x0C02 )                                     \
GL_ENUM( RED                                                 , 0x1903 )                                     \
GL_ENUM( RENDERER                                            , 0x1F01 )                                     \
GL_ENUM( REPEAT                                              , 0x2901 )                                     \
GL_ENUM( REPLACE                                             , 0x1E01 )                                     \
GL_ENUM( RGB                                                 , 0x1907 )                                     \
GL_ENUM( RGB10                                               , 0x8052 )                                     \
GL_ENUM( RGB10_A2                                            , 0x8059 )                                     \
GL_ENUM( RGB12                                               , 0x8053 )                                     \
GL_ENUM( RGB16                                               , 0x8054 )                                     \
GL_ENUM( RGB4                                                , 0x804F )                                     \
GL_ENUM( RGB5                                                , 0x8050 )                                     \
GL_ENUM( RGB5_A1                                             , 0x8057 )                                     \
GL_ENUM( RGB8                                                , 0x8051 )                                     \
GL_ENUM( RGBA                                                , 0x1908 )                                     \
GL_ENUM( RGBA12                                              , 0x805A )                                     \
GL_ENUM( RGBA16                                              , 0x805B )                                     \
GL_ENUM( RGBA2                                               , 0x8055 )                                     \
GL_ENUM( RGBA4                                               , 0x8056 )                                     \
GL_ENUM( RGBA8                                               , 0x8058 )                                     \
GL_ENUM( RIGHT                                               , 0x0407 )                                     \
GL_ENUM( SCISSOR_BOX                                         , 0x0C10 )                                     \
GL_ENUM( SCISSOR_TEST                                        , 0x0C11 )                                     \
GL_ENUM( SET                                                 , 0x150F )                                     \
GL_ENUM( SHORT                                               , 0x1402 )                                     \
GL_ENUM( SRC_ALPHA                                           , 0x0302 )                                     \
GL_ENUM( SRC_ALPHA_SATURATE                                  , 0x0308 )                                     \
GL_ENUM( SRC_COLOR                                           , 0x0300 )                                     \
GL_ENUM( STENCIL                                             , 0x1802 )                                     \
GL_ENUM( STENCIL_BUFFER_BIT                                  , 0x00000400 )                                 \
GL_ENUM( STENCIL_CLEAR_VALUE                                 , 0x0B91 )                                     \
GL_ENUM( STENCIL_FAIL                                        , 0x0B94 )                                     \
GL_ENUM( STENCIL_FUNC                                        , 0x0B92 )                                     \
GL_ENUM( STENCIL_INDEX                                       , 0x1901 )                                     \
GL_ENUM( STENCIL_PASS_DEPTH_FAIL                             , 0x0B95 )                                     \
GL_ENUM( STENCIL_PASS_DEPTH_PASS                             , 0x0B96 )                                     \
GL_ENUM( STENCIL_REF                                         , 0x0B97 )                                     \
GL_ENUM( STENCIL_TEST                                        , 0x0B90 )                                     \
GL_ENUM( STENCIL_VALUE_MASK                                  , 0x0B93 )                                     \
GL_ENUM( STENCIL_WRITEMASK                                   , 0x0B98 )                                     \
GL_ENUM( STEREO                                              , 0x0C33 )                                     \
GL_ENUM( SUBPIXEL_BITS                                       , 0x0D50 )                                     \
GL_ENUM( TEXTURE                                             , 0x1702 )                                     \
GL_ENUM( TEXTURE_1D                                          , 0x0DE0 )                                     \
GL_ENUM( TEXTURE_2D                                          , 0x0DE1 )                                     \
GL_ENUM( TEXTURE_ALPHA_SIZE                                  , 0x805F )                                     \
GL_ENUM( TEXTURE_BINDING_1D                                  , 0x8068 )                                     \
GL_ENUM( TEXTURE_BINDING_2D                                  , 0x8069 )                                     \
GL_ENUM( TEXTURE_BLUE_SIZE                                   , 0x805E )                                     \
GL_ENUM( TEXTURE_BORDER_COLOR                                , 0x1004 )                                     \
GL_ENUM( TEXTURE_GREEN_SIZE                                  , 0x805D )                                     \
GL_ENUM( TEXTURE_HEIGHT                                      , 0x1001 )                                     \
GL_ENUM( TEXTURE_INTERNAL_FORMAT                             , 0x1003 )                                     \
GL_ENUM( TEXTURE_MAG_FILTER                                  , 0x2800 )                                     \
GL_ENUM( TEXTURE_MIN_FILTER                                  , 0x2801 )                                     \
GL_ENUM( TEXTURE_RED_SIZE                                    , 0x805C )                                     \
GL_ENUM( TEXTURE_WIDTH                                       , 0x1000 )                                     \
GL_ENUM( TEXTURE_WRAP_S                                      , 0x2802 )                                     \
GL_ENUM( TEXTURE_WRAP_T                                      , 0x2803 )                                     \
GL_ENUM( TRIANGLES                                           , 0x0004 )                                     \
GL_ENUM( TRIANGLE_FAN                                        , 0x0006 )                                     \
GL_ENUM( TRIANGLE_STRIP                                      , 0x0005 )                                     \
GL_ENUM( TRUE                                                , 1      )                                     \
GL_ENUM( UNPACK_ALIGNMENT                                    , 0x0CF5 )                                     \
GL_ENUM( UNPACK_LSB_FIRST                                    , 0x0CF1 )                                     \
GL_ENUM( UNPACK_ROW_LENGTH                                   , 0x0CF2 )                                     \
GL_ENUM( UNPACK_SKIP_PIXELS                                  , 0x0CF4 )                                     \
GL_ENUM( UNPACK_SKIP_ROWS                                    , 0x0CF3 )                                     \
GL_ENUM( UNPACK_SWAP_BYTES                                   , 0x0CF0 )                                     \
GL_ENUM( UNSIGNED_BYTE                                       , 0x1401 )                                     \
GL_ENUM( UNSIGNED_INT                                        , 0x1405 )                                     \
GL_ENUM( UNSIGNED_SHORT                                      , 0x1403 )                                     \
GL_ENUM( VENDOR                                              , 0x1F00 )                                     \
GL_ENUM( VERSION                                             , 0x1F02 )                                     \
GL_ENUM( VIEWPORT                                            , 0x0BA2 )                                     \
GL_ENUM( XOR                                                 , 0x1506 )                                     \
GL_ENUM( ZERO                                                , 0      )                                     \
GL_ENUM( ALIASED_LINE_WIDTH_RANGE                            , 0x846E )                                     \
GL_ENUM( BGR                                                 , 0x80E0 )                                     \
GL_ENUM( BGRA                                                , 0x80E1 )                                     \
GL_ENUM( CLAMP_TO_EDGE                                       , 0x812F )                                     \
GL_ENUM( MAX_3D_TEXTURE_SIZE                                 , 0x8073 )                                     \
GL_ENUM( MAX_ELEMENTS_INDICES                                , 0x80E9 )                                     \
GL_ENUM( MAX_ELEMENTS_VERTICES                               , 0x80E8 )                                     \
GL_ENUM( PACK_IMAGE_HEIGHT                                   , 0x806C )                                     \
GL_ENUM( PACK_SKIP_IMAGES                                    , 0x806B )                                     \
GL_ENUM( PROXY_TEXTURE_3D                                    , 0x8070 )                                     \
GL_ENUM( SMOOTH_LINE_WIDTH_GRANULARITY                       , 0x0B23 )                                     \
GL_ENUM( SMOOTH_LINE_WIDTH_RANGE                             , 0x0B22 )                                     \
GL_ENUM( SMOOTH_POINT_SIZE_GRANULARITY                       , 0x0B13 )                                     \
GL_ENUM( SMOOTH_POINT_SIZE_RANGE                             , 0x0B12 )                                     \
GL_ENUM( TEXTURE_3D                                          , 0x806F )                                     \
GL_ENUM( TEXTURE_BASE_LEVEL                                  , 0x813C )                                     \
GL_ENUM( TEXTURE_BINDING_3D                                  , 0x806A )                                     \
GL_ENUM( TEXTURE_DEPTH                                       , 0x8071 )                                     \
GL_ENUM( TEXTURE_MAX_LEVEL                                   , 0x813D )                                     \
GL_ENUM( TEXTURE_MAX_LOD                                     , 0x813B )                                     \
GL_ENUM( TEXTURE_MIN_LOD                                     , 0x813A )                                     \
GL_ENUM( TEXTURE_WRAP_R                                      , 0x8072 )                                     \
GL_ENUM( UNPACK_IMAGE_HEIGHT                                 , 0x806E )                                     \
GL_ENUM( UNPACK_SKIP_IMAGES                                  , 0x806D )                                     \
GL_ENUM( UNSIGNED_BYTE_2_3_3_REV                             , 0x8362 )                                     \
GL_ENUM( UNSIGNED_BYTE_3_3_2                                 , 0x8032 )                                     \
GL_ENUM( UNSIGNED_INT_10_10_10_2                             , 0x8036 )                                     \
GL_ENUM( UNSIGNED_INT_2_10_10_10_REV                         , 0x8368 )                                     \
GL_ENUM( UNSIGNED_INT_8_8_8_8                                , 0x8035 )                                     \
GL_ENUM( UNSIGNED_INT_8_8_8_8_REV                            , 0x8367 )                                     \
GL_ENUM( UNSIGNED_SHORT_1_5_5_5_REV                          , 0x8366 )                                     \
GL_ENUM( UNSIGNED_SHORT_4_4_4_4                              , 0x8033 )                                     \
GL_ENUM( UNSIGNED_SHORT_4_4_4_4_REV                          , 0x8365 )                                     \
GL_ENUM( UNSIGNED_SHORT_5_5_5_1                              , 0x8034 )                                     \
GL_ENUM( UNSIGNED_SHORT_5_6_5                                , 0x8363 )                                     \
GL_ENUM( UNSIGNED_SHORT_5_6_5_REV                            , 0x8364 )                                     \
GL_ENUM( ACTIVE_TEXTURE                                      , 0x84E0 )                                     \
GL_ENUM( CLAMP_TO_BORDER                                     , 0x812D )                                     \
GL_ENUM( COMPRESSED_RGB                                      , 0x84ED )                                     \
GL_ENUM( COMPRESSED_RGBA                                     , 0x84EE )                                     \
GL_ENUM( COMPRESSED_TEXTURE_FORMATS                          , 0x86A3 )                                     \
GL_ENUM( MAX_CUBE_MAP_TEXTURE_SIZE                           , 0x851C )                                     \
GL_ENUM( MULTISAMPLE                                         , 0x809D )                                     \
GL_ENUM( NUM_COMPRESSED_TEXTURE_FORMATS                      , 0x86A2 )                                     \
GL_ENUM( PROXY_TEXTURE_CUBE_MAP                              , 0x851B )                                     \
GL_ENUM( SAMPLES                                             , 0x80A9 )                                     \
GL_ENUM( SAMPLE_ALPHA_TO_COVERAGE                            , 0x809E )                                     \
GL_ENUM( SAMPLE_ALPHA_TO_ONE                                 , 0x809F )                                     \
GL_ENUM( SAMPLE_BUFFERS                                      , 0x80A8 )                                     \
GL_ENUM( SAMPLE_COVERAGE                                     , 0x80A0 )                                     \
GL_ENUM( SAMPLE_COVERAGE_INVERT                              , 0x80AB )                                     \
GL_ENUM( SAMPLE_COVERAGE_VALUE                               , 0x80AA )                                     \
GL_ENUM( TEXTURE0                                            , 0x84C0 )                                     \
GL_ENUM( TEXTURE1                                            , 0x84C1 )                                     \
GL_ENUM( TEXTURE10                                           , 0x84CA )                                     \
GL_ENUM( TEXTURE11                                           , 0x84CB )                                     \
GL_ENUM( TEXTURE12                                           , 0x84CC )                                     \
GL_ENUM( TEXTURE13                                           , 0x84CD )                                     \
GL_ENUM( TEXTURE14                                           , 0x84CE )                                     \
GL_ENUM( TEXTURE15                                           , 0x84CF )                                     \
GL_ENUM( TEXTURE16                                           , 0x84D0 )                                     \
GL_ENUM( TEXTURE17                                           , 0x84D1 )                                     \
GL_ENUM( TEXTURE18                                           , 0x84D2 )                                     \
GL_ENUM( TEXTURE19                                           , 0x84D3 )                                     \
GL_ENUM( TEXTURE2                                            , 0x84C2 )                                     \
GL_ENUM( TEXTURE20                                           , 0x84D4 )                                     \
GL_ENUM( TEXTURE21                                           , 0x84D5 )                                     \
GL_ENUM( TEXTURE22                                           , 0x84D6 )                                     \
GL_ENUM( TEXTURE23                                           , 0x84D7 )                                     \
GL_ENUM( TEXTURE24                                           , 0x84D8 )                                     \
GL_ENUM( TEXTURE25                                           , 0x84D9 )                                     \
GL_ENUM( TEXTURE26                                           , 0x84DA )                                     \
GL_ENUM( TEXTURE27                                           , 0x84DB )                                     \
GL_ENUM( TEXTURE28                                           , 0x84DC )                                     \
GL_ENUM( TEXTURE29                                           , 0x84DD )                                     \
GL_ENUM( TEXTURE3                                            , 0x84C3 )                                     \
GL_ENUM( TEXTURE30                                           , 0x84DE )                                     \
GL_ENUM( TEXTURE31                                           , 0x84DF )                                     \
GL_ENUM( TEXTURE4                                            , 0x84C4 )                                     \
GL_ENUM( TEXTURE5                                            , 0x84C5 )                                     \
GL_ENUM( TEXTURE6                                            , 0x84C6 )                                     \
GL_ENUM( TEXTURE7                                            , 0x84C7 )                                     \
GL_ENUM( TEXTURE8                                            , 0x84C8 )                                     \
GL_ENUM( TEXTURE9                                            , 0x84C9 )                                     \
GL_ENUM( TEXTURE_BINDING_CUBE_MAP                            , 0x8514 )                                     \
GL_ENUM( TEXTURE_COMPRESSED                                  , 0x86A1 )                                     \
GL_ENUM( TEXTURE_COMPRESSED_IMAGE_SIZE                       , 0x86A0 )                                     \
GL_ENUM( TEXTURE_COMPRESSION_HINT                            , 0x84EF )                                     \
GL_ENUM( TEXTURE_CUBE_MAP                                    , 0x8513 )                                     \
GL_ENUM( TEXTURE_CUBE_MAP_NEGATIVE_X                         , 0x8516 )                                     \
GL_ENUM( TEXTURE_CUBE_MAP_NEGATIVE_Y                         , 0x8518 )                                     \
GL_ENUM( TEXTURE_CUBE_MAP_NEGATIVE_Z                         , 0x851A )                                     \
GL_ENUM( TEXTURE_CUBE_MAP_POSITIVE_X                         , 0x8515 )                                     \
GL_ENUM( TEXTURE_CUBE_MAP_POSITIVE_Y                         , 0x8517 )                                     \
GL_ENUM( TEXTURE_CUBE_MAP_POSITIVE_Z                         , 0x8519 )                                     \
GL_ENUM( BLEND_DST_ALPHA                                     , 0x80CA )                                     \
GL_ENUM( BLEND_DST_RGB                                       , 0x80C8 )                                     \
GL_ENUM( BLEND_SRC_ALPHA                                     , 0x80CB )                                     \
GL_ENUM( BLEND_SRC_RGB                                       , 0x80C9 )                                     \
GL_ENUM( DECR_WRAP                                           , 0x8508 )                                     \
GL_ENUM( DEPTH_COMPONENT16                                   , 0x81A5 )                                     \
GL_ENUM( DEPTH_COMPONENT24                                   , 0x81A6 )                                     \
GL_ENUM( DEPTH_COMPONENT32                                   , 0x81A7 )                                     \
GL_ENUM( INCR_WRAP                                           , 0x8507 )                                     \
GL_ENUM( MAX_TEXTURE_LOD_BIAS                                , 0x84FD )                                     \
GL_ENUM( MIRRORED_REPEAT                                     , 0x8370 )                                     \
GL_ENUM( POINT_FADE_THRESHOLD_SIZE                           , 0x8128 )                                     \
GL_ENUM( TEXTURE_COMPARE_FUNC                                , 0x884D )                                     \
GL_ENUM( TEXTURE_COMPARE_MODE                                , 0x884C )                                     \
GL_ENUM( TEXTURE_DEPTH_SIZE                                  , 0x884A )                                     \
GL_ENUM( TEXTURE_LOD_BIAS                                    , 0x8501 )                                     \
GL_ENUM( ARRAY_BUFFER                                        , 0x8892 )                                     \
GL_ENUM( ARRAY_BUFFER_BINDING                                , 0x8894 )                                     \
GL_ENUM( BUFFER_ACCESS                                       , 0x88BB )                                     \
GL_ENUM( BUFFER_MAPPED                                       , 0x88BC )                                     \
GL_ENUM( BUFFER_MAP_POINTER                                  , 0x88BD )                                     \
GL_ENUM( BUFFER_SIZE                                         , 0x8764 )                                     \
GL_ENUM( BUFFER_USAGE                                        , 0x8765 )                                     \
GL_ENUM( CURRENT_QUERY                                       , 0x8865 )                                     \
GL_ENUM( DYNAMIC_COPY                                        , 0x88EA )                                     \
GL_ENUM( DYNAMIC_DRAW                                        , 0x88E8 )                                     \
GL_ENUM( DYNAMIC_READ                                        , 0x88E9 )                                     \
GL_ENUM( ELEMENT_ARRAY_BUFFER                                , 0x8893 )                                     \
GL_ENUM( ELEMENT_ARRAY_BUFFER_BINDING                        , 0x8895 )                                     \
GL_ENUM( QUERY_COUNTER_BITS                                  , 0x8864 )                                     \
GL_ENUM( QUERY_RESULT                                        , 0x8866 )                                     \
GL_ENUM( QUERY_RESULT_AVAILABLE                              , 0x8867 )                                     \
GL_ENUM( READ_ONLY                                           , 0x88B8 )                                     \
GL_ENUM( READ_WRITE                                          , 0x88BA )                                     \
GL_ENUM( SAMPLES_PASSED                                      , 0x8914 )                                     \
GL_ENUM( SRC1_ALPHA                                          , 0x8589 )                                     \
GL_ENUM( STATIC_COPY                                         , 0x88E6 )                                     \
GL_ENUM( STATIC_DRAW                                         , 0x88E4 )                                     \
GL_ENUM( STATIC_READ                                         , 0x88E5 )                                     \
GL_ENUM( STREAM_COPY                                         , 0x88E2 )                                     \
GL_ENUM( STREAM_DRAW                                         , 0x88E0 )                                     \
GL_ENUM( STREAM_READ                                         , 0x88E1 )                                     \
GL_ENUM( VERTEX_ATTRIB_ARRAY_BUFFER_BINDING                  , 0x889F )                                     \
GL_ENUM( WRITE_ONLY                                          , 0x88B9 )                                     \
GL_ENUM( ACTIVE_ATTRIBUTES                                   , 0x8B89 )                                     \
GL_ENUM( ACTIVE_ATTRIBUTE_MAX_LENGTH                         , 0x8B8A )                                     \
GL_ENUM( ACTIVE_UNIFORMS                                     , 0x8B86 )                                     \
GL_ENUM( ACTIVE_UNIFORM_MAX_LENGTH                           , 0x8B87 )                                     \
GL_ENUM( ATTACHED_SHADERS                                    , 0x8B85 )                                     \
GL_ENUM( BLEND_EQUATION_ALPHA                                , 0x883D )                                     \
GL_ENUM( BLEND_EQUATION_RGB                                  , 0x8009 )                                     \
GL_ENUM( BOOL                                                , 0x8B56 )                                     \
GL_ENUM( BOOL_VEC2                                           , 0x8B57 )                                     \
GL_ENUM( BOOL_VEC3                                           , 0x8B58 )                                     \
GL_ENUM( BOOL_VEC4                                           , 0x8B59 )                                     \
GL_ENUM( COMPILE_STATUS                                      , 0x8B81 )                                     \
GL_ENUM( CURRENT_PROGRAM                                     , 0x8B8D )                                     \
GL_ENUM( CURRENT_VERTEX_ATTRIB                               , 0x8626 )                                     \
GL_ENUM( DELETE_STATUS                                       , 0x8B80 )                                     \
GL_ENUM( DRAW_BUFFER0                                        , 0x8825 )                                     \
GL_ENUM( DRAW_BUFFER1                                        , 0x8826 )                                     \
GL_ENUM( DRAW_BUFFER10                                       , 0x882F )                                     \
GL_ENUM( DRAW_BUFFER11                                       , 0x8830 )                                     \
GL_ENUM( DRAW_BUFFER12                                       , 0x8831 )                                     \
GL_ENUM( DRAW_BUFFER13                                       , 0x8832 )                                     \
GL_ENUM( DRAW_BUFFER14                                       , 0x8833 )                                     \
GL_ENUM( DRAW_BUFFER15                                       , 0x8834 )                                     \
GL_ENUM( DRAW_BUFFER2                                        , 0x8827 )                                     \
GL_ENUM( DRAW_BUFFER3                                        , 0x8828 )                                     \
GL_ENUM( DRAW_BUFFER4                                        , 0x8829 )                                     \
GL_ENUM( DRAW_BUFFER5                                        , 0x882A )                                     \
GL_ENUM( DRAW_BUFFER6                                        , 0x882B )                                     \
GL_ENUM( DRAW_BUFFER7                                        , 0x882C )                                     \
GL_ENUM( DRAW_BUFFER8                                        , 0x882D )                                     \
GL_ENUM( DRAW_BUFFER9                                        , 0x882E )                                     \
GL_ENUM( FLOAT_MAT2                                          , 0x8B5A )                                     \
GL_ENUM( FLOAT_MAT3                                          , 0x8B5B )                                     \
GL_ENUM( FLOAT_MAT4                                          , 0x8B5C )                                     \
GL_ENUM( FLOAT_VEC2                                          , 0x8B50 )                                     \
GL_ENUM( FLOAT_VEC3                                          , 0x8B51 )                                     \
GL_ENUM( FLOAT_VEC4                                          , 0x8B52 )                                     \
GL_ENUM( FRAGMENT_SHADER                                     , 0x8B30 )                                     \
GL_ENUM( FRAGMENT_SHADER_DERIVATIVE_HINT                     , 0x8B8B )                                     \
GL_ENUM( INFO_LOG_LENGTH                                     , 0x8B84 )                                     \
GL_ENUM( INT_VEC2                                            , 0x8B53 )                                     \
GL_ENUM( INT_VEC3                                            , 0x8B54 )                                     \
GL_ENUM( INT_VEC4                                            , 0x8B55 )                                     \
GL_ENUM( LINK_STATUS                                         , 0x8B82 )                                     \
GL_ENUM( LOWER_LEFT                                          , 0x8CA1 )                                     \
GL_ENUM( MAX_COMBINED_TEXTURE_IMAGE_UNITS                    , 0x8B4D )                                     \
GL_ENUM( MAX_DRAW_BUFFERS                                    , 0x8824 )                                     \
GL_ENUM( MAX_FRAGMENT_UNIFORM_COMPONENTS                     , 0x8B49 )                                     \
GL_ENUM( MAX_TEXTURE_IMAGE_UNITS                             , 0x8872 )                                     \
GL_ENUM( MAX_VARYING_FLOATS                                  , 0x8B4B )                                     \
GL_ENUM( MAX_VERTEX_ATTRIBS                                  , 0x8869 )                                     \
GL_ENUM( MAX_VERTEX_TEXTURE_IMAGE_UNITS                      , 0x8B4C )                                     \
GL_ENUM( MAX_VERTEX_UNIFORM_COMPONENTS                       , 0x8B4A )                                     \
GL_ENUM( POINT_SPRITE_COORD_ORIGIN                           , 0x8CA0 )                                     \
GL_ENUM( SAMPLER_1D                                          , 0x8B5D )                                     \
GL_ENUM( SAMPLER_1D_SHADOW                                   , 0x8B61 )                                     \
GL_ENUM( SAMPLER_2D                                          , 0x8B5E )                                     \
GL_ENUM( SAMPLER_2D_SHADOW                                   , 0x8B62 )                                     \
GL_ENUM( SAMPLER_3D                                          , 0x8B5F )                                     \
GL_ENUM( SAMPLER_CUBE                                        , 0x8B60 )                                     \
GL_ENUM( SHADER_SOURCE_LENGTH                                , 0x8B88 )                                     \
GL_ENUM( SHADER_TYPE                                         , 0x8B4F )                                     \
GL_ENUM( SHADING_LANGUAGE_VERSION                            , 0x8B8C )                                     \
GL_ENUM( STENCIL_BACK_FAIL                                   , 0x8801 )                                     \
GL_ENUM( STENCIL_BACK_FUNC                                   , 0x8800 )                                     \
GL_ENUM( STENCIL_BACK_PASS_DEPTH_FAIL                        , 0x8802 )                                     \
GL_ENUM( STENCIL_BACK_PASS_DEPTH_PASS                        , 0x8803 )                                     \
GL_ENUM( STENCIL_BACK_REF                                    , 0x8CA3 )                                     \
GL_ENUM( STENCIL_BACK_VALUE_MASK                             , 0x8CA4 )                                     \
GL_ENUM( STENCIL_BACK_WRITEMASK                              , 0x8CA5 )                                     \
GL_ENUM( UPPER_LEFT                                          , 0x8CA2 )                                     \
GL_ENUM( VALIDATE_STATUS                                     , 0x8B83 )                                     \
GL_ENUM( VERTEX_ATTRIB_ARRAY_ENABLED                         , 0x8622 )                                     \
GL_ENUM( VERTEX_ATTRIB_ARRAY_NORMALIZED                      , 0x886A )                                     \
GL_ENUM( VERTEX_ATTRIB_ARRAY_POINTER                         , 0x8645 )                                     \
GL_ENUM( VERTEX_ATTRIB_ARRAY_SIZE                            , 0x8623 )                                     \
GL_ENUM( VERTEX_ATTRIB_ARRAY_STRIDE                          , 0x8624 )                                     \
GL_ENUM( VERTEX_ATTRIB_ARRAY_TYPE                            , 0x8625 )                                     \
GL_ENUM( VERTEX_PROGRAM_POINT_SIZE                           , 0x8642 )                                     \
GL_ENUM( VERTEX_SHADER                                       , 0x8B31 )                                     \
GL_ENUM( COMPRESSED_SRGB                                     , 0x8C48 )                                     \
GL_ENUM( COMPRESSED_SRGB_ALPHA                               , 0x8C49 )                                     \
GL_ENUM( FLOAT_MAT2x3                                        , 0x8B65 )                                     \
GL_ENUM( FLOAT_MAT2x4                                        , 0x8B66 )                                     \
GL_ENUM( FLOAT_MAT3x2                                        , 0x8B67 )                                     \
GL_ENUM( FLOAT_MAT3x4                                        , 0x8B68 )                                     \
GL_ENUM( FLOAT_MAT4x2                                        , 0x8B69 )                                     \
GL_ENUM( FLOAT_MAT4x3                                        , 0x8B6A )                                     \
GL_ENUM( PIXEL_PACK_BUFFER                                   , 0x88EB )                                     \
GL_ENUM( PIXEL_PACK_BUFFER_BINDING                           , 0x88ED )                                     \
GL_ENUM( PIXEL_UNPACK_BUFFER                                 , 0x88EC )                                     \
GL_ENUM( PIXEL_UNPACK_BUFFER_BINDING                         , 0x88EF )                                     \
GL_ENUM( SRGB                                                , 0x8C40 )                                     \
GL_ENUM( SRGB8                                               , 0x8C41 )                                     \
GL_ENUM( SRGB8_ALPHA8                                        , 0x8C43 )                                     \
GL_ENUM( SRGB_ALPHA                                          , 0x8C42 )                                     \
GL_ENUM( BGRA_INTEGER                                        , 0x8D9B )                                     \
GL_ENUM( BGR_INTEGER                                         , 0x8D9A )                                     \
GL_ENUM( BLUE_INTEGER                                        , 0x8D96 )                                     \
GL_ENUM( BUFFER_ACCESS_FLAGS                                 , 0x911F )                                     \
GL_ENUM( BUFFER_MAP_LENGTH                                   , 0x9120 )                                     \
GL_ENUM( BUFFER_MAP_OFFSET                                   , 0x9121 )                                     \
GL_ENUM( CLAMP_READ_COLOR                                    , 0x891C )                                     \
GL_ENUM( CLIP_DISTANCE0                                      , 0x3000 )                                     \
GL_ENUM( CLIP_DISTANCE1                                      , 0x3001 )                                     \
GL_ENUM( CLIP_DISTANCE2                                      , 0x3002 )                                     \
GL_ENUM( CLIP_DISTANCE3                                      , 0x3003 )                                     \
GL_ENUM( CLIP_DISTANCE4                                      , 0x3004 )                                     \
GL_ENUM( CLIP_DISTANCE5                                      , 0x3005 )                                     \
GL_ENUM( CLIP_DISTANCE6                                      , 0x3006 )                                     \
GL_ENUM( CLIP_DISTANCE7                                      , 0x3007 )                                     \
GL_ENUM( COLOR_ATTACHMENT0                                   , 0x8CE0 )                                     \
GL_ENUM( COLOR_ATTACHMENT1                                   , 0x8CE1 )                                     \
GL_ENUM( COLOR_ATTACHMENT10                                  , 0x8CEA )                                     \
GL_ENUM( COLOR_ATTACHMENT11                                  , 0x8CEB )                                     \
GL_ENUM( COLOR_ATTACHMENT12                                  , 0x8CEC )                                     \
GL_ENUM( COLOR_ATTACHMENT13                                  , 0x8CED )                                     \
GL_ENUM( COLOR_ATTACHMENT14                                  , 0x8CEE )                                     \
GL_ENUM( COLOR_ATTACHMENT15                                  , 0x8CEF )                                     \
GL_ENUM( COLOR_ATTACHMENT2                                   , 0x8CE2 )                                     \
GL_ENUM( COLOR_ATTACHMENT3                                   , 0x8CE3 )                                     \
GL_ENUM( COLOR_ATTACHMENT4                                   , 0x8CE4 )                                     \
GL_ENUM( COLOR_ATTACHMENT5                                   , 0x8CE5 )                                     \
GL_ENUM( COLOR_ATTACHMENT6                                   , 0x8CE6 )                                     \
GL_ENUM( COLOR_ATTACHMENT7                                   , 0x8CE7 )                                     \
GL_ENUM( COLOR_ATTACHMENT8                                   , 0x8CE8 )                                     \
GL_ENUM( COLOR_ATTACHMENT9                                   , 0x8CE9 )                                     \
GL_ENUM( COMPARE_REF_TO_TEXTURE                              , 0x884E )                                     \
GL_ENUM( COMPRESSED_RED                                      , 0x8225 )                                     \
GL_ENUM( COMPRESSED_RED_RGTC1                                , 0x8DBB )                                     \
GL_ENUM( COMPRESSED_RG                                       , 0x8226 )                                     \
GL_ENUM( COMPRESSED_RG_RGTC2                                 , 0x8DBD )                                     \
GL_ENUM( COMPRESSED_SIGNED_RED_RGTC1                         , 0x8DBC )                                     \
GL_ENUM( COMPRESSED_SIGNED_RG_RGTC2                          , 0x8DBE )                                     \
GL_ENUM( CONTEXT_FLAGS                                       , 0x821E )                                     \
GL_ENUM( CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT                 , 0x00000001 )                                 \
GL_ENUM( DEPTH24_STENCIL8                                    , 0x88F0 )                                     \
GL_ENUM( DEPTH32F_STENCIL8                                   , 0x8CAD )                                     \
GL_ENUM( DEPTH_ATTACHMENT                                    , 0x8D00 )                                     \
GL_ENUM( DEPTH_COMPONENT32F                                  , 0x8CAC )                                     \
GL_ENUM( DEPTH_STENCIL                                       , 0x84F9 )                                     \
GL_ENUM( DEPTH_STENCIL_ATTACHMENT                            , 0x821A )                                     \
GL_ENUM( DRAW_FRAMEBUFFER                                    , 0x8CA9 )                                     \
GL_ENUM( DRAW_FRAMEBUFFER_BINDING                            , 0x8CA6 )                                     \
GL_ENUM( FIXED_ONLY                                          , 0x891D )                                     \
GL_ENUM( FLOAT_32_UNSIGNED_INT_24_8_REV                      , 0x8DAD )                                     \
GL_ENUM( FRAMEBUFFER                                         , 0x8D40 )                                     \
GL_ENUM( FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE                   , 0x8215 )                                     \
GL_ENUM( FRAMEBUFFER_ATTACHMENT_BLUE_SIZE                    , 0x8214 )                                     \
GL_ENUM( FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING               , 0x8210 )                                     \
GL_ENUM( FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE               , 0x8211 )                                     \
GL_ENUM( FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE                   , 0x8216 )                                     \
GL_ENUM( FRAMEBUFFER_ATTACHMENT_GREEN_SIZE                   , 0x8213 )                                     \
GL_ENUM( FRAMEBUFFER_ATTACHMENT_OBJECT_NAME                  , 0x8CD1 )                                     \
GL_ENUM( FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE                  , 0x8CD0 )                                     \
GL_ENUM( FRAMEBUFFER_ATTACHMENT_RED_SIZE                     , 0x8212 )                                     \
GL_ENUM( FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE                 , 0x8217 )                                     \
GL_ENUM( FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE        , 0x8CD3 )                                     \
GL_ENUM( FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER                , 0x8CD4 )                                     \
GL_ENUM( FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL                , 0x8CD2 )                                     \
GL_ENUM( FRAMEBUFFER_BINDING                                 , 0x8CA6 )                                     \
GL_ENUM( FRAMEBUFFER_COMPLETE                                , 0x8CD5 )                                     \
GL_ENUM( FRAMEBUFFER_DEFAULT                                 , 0x8218 )                                     \
GL_ENUM( FRAMEBUFFER_INCOMPLETE_ATTACHMENT                   , 0x8CD6 )                                     \
GL_ENUM( FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER                  , 0x8CDB )                                     \
GL_ENUM( FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT           , 0x8CD7 )                                     \
GL_ENUM( FRAMEBUFFER_INCOMPLETE_MULTISAMPLE                  , 0x8D56 )                                     \
GL_ENUM( FRAMEBUFFER_INCOMPLETE_READ_BUFFER                  , 0x8CDC )                                     \
GL_ENUM( FRAMEBUFFER_SRGB                                    , 0x8DB9 )                                     \
GL_ENUM( FRAMEBUFFER_UNDEFINED                               , 0x8219 )                                     \
GL_ENUM( FRAMEBUFFER_UNSUPPORTED                             , 0x8CDD )                                     \
GL_ENUM( GREEN_INTEGER                                       , 0x8D95 )                                     \
GL_ENUM( HALF_FLOAT                                          , 0x140B )                                     \
GL_ENUM( INDEX                                               , 0x8222 )                                     \
GL_ENUM( INTERLEAVED_ATTRIBS                                 , 0x8C8C )                                     \
GL_ENUM( INT_SAMPLER_1D                                      , 0x8DC9 )                                     \
GL_ENUM( INT_SAMPLER_1D_ARRAY                                , 0x8DCE )                                     \
GL_ENUM( INT_SAMPLER_2D                                      , 0x8DCA )                                     \
GL_ENUM( INT_SAMPLER_2D_ARRAY                                , 0x8DCF )                                     \
GL_ENUM( INT_SAMPLER_3D                                      , 0x8DCB )                                     \
GL_ENUM( INT_SAMPLER_CUBE                                    , 0x8DCC )                                     \
GL_ENUM( INVALID_FRAMEBUFFER_OPERATION                       , 0x0506 )                                     \
GL_ENUM( MAJOR_VERSION                                       , 0x821B )                                     \
GL_ENUM( MAP_FLUSH_EXPLICIT_BIT                              , 0x0010 )                                     \
GL_ENUM( MAP_INVALIDATE_BUFFER_BIT                           , 0x0008 )                                     \
GL_ENUM( MAP_INVALIDATE_RANGE_BIT                            , 0x0004 )                                     \
GL_ENUM( MAP_READ_BIT                                        , 0x0001 )                                     \
GL_ENUM( MAP_UNSYNCHRONIZED_BIT                              , 0x0020 )                                     \
GL_ENUM( MAP_WRITE_BIT                                       , 0x0002 )                                     \
GL_ENUM( MAX_ARRAY_TEXTURE_LAYERS                            , 0x88FF )                                     \
GL_ENUM( MAX_CLIP_DISTANCES                                  , 0x0D32 )                                     \
GL_ENUM( MAX_COLOR_ATTACHMENTS                               , 0x8CDF )                                     \
GL_ENUM( MAX_PROGRAM_TEXEL_OFFSET                            , 0x8905 )                                     \
GL_ENUM( MAX_RENDERBUFFER_SIZE                               , 0x84E8 )                                     \
GL_ENUM( MAX_SAMPLES                                         , 0x8D57 )                                     \
GL_ENUM( MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS       , 0x8C8A )                                     \
GL_ENUM( MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS             , 0x8C8B )                                     \
GL_ENUM( MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS          , 0x8C80 )                                     \
GL_ENUM( MAX_VARYING_COMPONENTS                              , 0x8B4B )                                     \
GL_ENUM( MINOR_VERSION                                       , 0x821C )                                     \
GL_ENUM( MIN_PROGRAM_TEXEL_OFFSET                            , 0x8904 )                                     \
GL_ENUM( NUM_EXTENSIONS                                      , 0x821D )                                     \
GL_ENUM( PRIMITIVES_GENERATED                                , 0x8C87 )                                     \
GL_ENUM( PROXY_TEXTURE_1D_ARRAY                              , 0x8C19 )                                     \
GL_ENUM( PROXY_TEXTURE_2D_ARRAY                              , 0x8C1B )                                     \
GL_ENUM( QUERY_BY_REGION_NO_WAIT                             , 0x8E16 )                                     \
GL_ENUM( QUERY_BY_REGION_WAIT                                , 0x8E15 )                                     \
GL_ENUM( QUERY_NO_WAIT                                       , 0x8E14 )                                     \
GL_ENUM( QUERY_WAIT                                          , 0x8E13 )                                     \
GL_ENUM( R11F_G11F_B10F                                      , 0x8C3A )                                     \
GL_ENUM( R16                                                 , 0x822A )                                     \
GL_ENUM( R16F                                                , 0x822D )                                     \
GL_ENUM( R16I                                                , 0x8233 )                                     \
GL_ENUM( R16UI                                               , 0x8234 )                                     \
GL_ENUM( R32F                                                , 0x822E )                                     \
GL_ENUM( R32I                                                , 0x8235 )                                     \
GL_ENUM( R32UI                                               , 0x8236 )                                     \
GL_ENUM( R8                                                  , 0x8229 )                                     \
GL_ENUM( R8I                                                 , 0x8231 )                                     \
GL_ENUM( R8UI                                                , 0x8232 )                                     \
GL_ENUM( RASTERIZER_DISCARD                                  , 0x8C89 )                                     \
GL_ENUM( READ_FRAMEBUFFER                                    , 0x8CA8 )                                     \
GL_ENUM( READ_FRAMEBUFFER_BINDING                            , 0x8CAA )                                     \
GL_ENUM( RED_INTEGER                                         , 0x8D94 )                                     \
GL_ENUM( RENDERBUFFER                                        , 0x8D41 )                                     \
GL_ENUM( RENDERBUFFER_ALPHA_SIZE                             , 0x8D53 )                                     \
GL_ENUM( RENDERBUFFER_BINDING                                , 0x8CA7 )                                     \
GL_ENUM( RENDERBUFFER_BLUE_SIZE                              , 0x8D52 )                                     \
GL_ENUM( RENDERBUFFER_DEPTH_SIZE                             , 0x8D54 )                                     \
GL_ENUM( RENDERBUFFER_GREEN_SIZE                             , 0x8D51 )                                     \
GL_ENUM( RENDERBUFFER_HEIGHT                                 , 0x8D43 )                                     \
GL_ENUM( RENDERBUFFER_INTERNAL_FORMAT                        , 0x8D44 )                                     \
GL_ENUM( RENDERBUFFER_RED_SIZE                               , 0x8D50 )                                     \
GL_ENUM( RENDERBUFFER_SAMPLES                                , 0x8CAB )                                     \
GL_ENUM( RENDERBUFFER_STENCIL_SIZE                           , 0x8D55 )                                     \
GL_ENUM( RENDERBUFFER_WIDTH                                  , 0x8D42 )                                     \
GL_ENUM( RG                                                  , 0x8227 )                                     \
GL_ENUM( RG16                                                , 0x822C )                                     \
GL_ENUM( RG16F                                               , 0x822F )                                     \
GL_ENUM( RG16I                                               , 0x8239 )                                     \
GL_ENUM( RG16UI                                              , 0x823A )                                     \
GL_ENUM( RG32F                                               , 0x8230 )                                     \
GL_ENUM( RG32I                                               , 0x823B )                                     \
GL_ENUM( RG32UI                                              , 0x823C )                                     \
GL_ENUM( RG8                                                 , 0x822B )                                     \
GL_ENUM( RG8I                                                , 0x8237 )                                     \
GL_ENUM( RG8UI                                               , 0x8238 )                                     \
GL_ENUM( RGB16F                                              , 0x881B )                                     \
GL_ENUM( RGB16I                                              , 0x8D89 )                                     \
GL_ENUM( RGB16UI                                             , 0x8D77 )                                     \
GL_ENUM( RGB32F                                              , 0x8815 )                                     \
GL_ENUM( RGB32I                                              , 0x8D83 )                                     \
GL_ENUM( RGB32UI                                             , 0x8D71 )                                     \
GL_ENUM( RGB8I                                               , 0x8D8F )                                     \
GL_ENUM( RGB8UI                                              , 0x8D7D )                                     \
GL_ENUM( RGB9_E5                                             , 0x8C3D )                                     \
GL_ENUM( RGBA16F                                             , 0x881A )                                     \
GL_ENUM( RGBA16I                                             , 0x8D88 )                                     \
GL_ENUM( RGBA16UI                                            , 0x8D76 )                                     \
GL_ENUM( RGBA32F                                             , 0x8814 )                                     \
GL_ENUM( RGBA32I                                             , 0x8D82 )                                     \
GL_ENUM( RGBA32UI                                            , 0x8D70 )                                     \
GL_ENUM( RGBA8I                                              , 0x8D8E )                                     \
GL_ENUM( RGBA8UI                                             , 0x8D7C )                                     \
GL_ENUM( RGBA_INTEGER                                        , 0x8D99 )                                     \
GL_ENUM( RGB_INTEGER                                         , 0x8D98 )                                     \
GL_ENUM( RG_INTEGER                                          , 0x8228 )                                     \
GL_ENUM( SAMPLER_1D_ARRAY                                    , 0x8DC0 )                                     \
GL_ENUM( SAMPLER_1D_ARRAY_SHADOW                             , 0x8DC3 )                                     \
GL_ENUM( SAMPLER_2D_ARRAY                                    , 0x8DC1 )                                     \
GL_ENUM( SAMPLER_2D_ARRAY_SHADOW                             , 0x8DC4 )                                     \
GL_ENUM( SAMPLER_CUBE_SHADOW                                 , 0x8DC5 )                                     \
GL_ENUM( SEPARATE_ATTRIBS                                    , 0x8C8D )                                     \
GL_ENUM( STENCIL_ATTACHMENT                                  , 0x8D20 )                                     \
GL_ENUM( STENCIL_INDEX1                                      , 0x8D46 )                                     \
GL_ENUM( STENCIL_INDEX16                                     , 0x8D49 )                                     \
GL_ENUM( STENCIL_INDEX4                                      , 0x8D47 )                                     \
GL_ENUM( STENCIL_INDEX8                                      , 0x8D48 )                                     \
GL_ENUM( TEXTURE_1D_ARRAY                                    , 0x8C18 )                                     \
GL_ENUM( TEXTURE_2D_ARRAY                                    , 0x8C1A )                                     \
GL_ENUM( TEXTURE_ALPHA_TYPE                                  , 0x8C13 )                                     \
GL_ENUM( TEXTURE_BINDING_1D_ARRAY                            , 0x8C1C )                                     \
GL_ENUM( TEXTURE_BINDING_2D_ARRAY                            , 0x8C1D )                                     \
GL_ENUM( TEXTURE_BLUE_TYPE                                   , 0x8C12 )                                     \
GL_ENUM( TEXTURE_DEPTH_TYPE                                  , 0x8C16 )                                     \
GL_ENUM( TEXTURE_GREEN_TYPE                                  , 0x8C11 )                                     \
GL_ENUM( TEXTURE_RED_TYPE                                    , 0x8C10 )                                     \
GL_ENUM( TEXTURE_SHARED_SIZE                                 , 0x8C3F )                                     \
GL_ENUM( TEXTURE_STENCIL_SIZE                                , 0x88F1 )                                     \
GL_ENUM( TRANSFORM_FEEDBACK_BUFFER                           , 0x8C8E )                                     \
GL_ENUM( TRANSFORM_FEEDBACK_BUFFER_BINDING                   , 0x8C8F )                                     \
GL_ENUM( TRANSFORM_FEEDBACK_BUFFER_MODE                      , 0x8C7F )                                     \
GL_ENUM( TRANSFORM_FEEDBACK_BUFFER_SIZE                      , 0x8C85 )                                     \
GL_ENUM( TRANSFORM_FEEDBACK_BUFFER_START                     , 0x8C84 )                                     \
GL_ENUM( TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN               , 0x8C88 )                                     \
GL_ENUM( TRANSFORM_FEEDBACK_VARYINGS                         , 0x8C83 )                                     \
GL_ENUM( TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH               , 0x8C76 )                                     \
GL_ENUM( UNSIGNED_INT_10F_11F_11F_REV                        , 0x8C3B )                                     \
GL_ENUM( UNSIGNED_INT_24_8                                   , 0x84FA )                                     \
GL_ENUM( UNSIGNED_INT_5_9_9_9_REV                            , 0x8C3E )                                     \
GL_ENUM( UNSIGNED_INT_SAMPLER_1D                             , 0x8DD1 )                                     \
GL_ENUM( UNSIGNED_INT_SAMPLER_1D_ARRAY                       , 0x8DD6 )                                     \
GL_ENUM( UNSIGNED_INT_SAMPLER_2D                             , 0x8DD2 )                                     \
GL_ENUM( UNSIGNED_INT_SAMPLER_2D_ARRAY                       , 0x8DD7 )                                     \
GL_ENUM( UNSIGNED_INT_SAMPLER_3D                             , 0x8DD3 )                                     \
GL_ENUM( UNSIGNED_INT_SAMPLER_CUBE                           , 0x8DD4 )                                     \
GL_ENUM( UNSIGNED_INT_VEC2                                   , 0x8DC6 )                                     \
GL_ENUM( UNSIGNED_INT_VEC3                                   , 0x8DC7 )                                     \
GL_ENUM( UNSIGNED_INT_VEC4                                   , 0x8DC8 )                                     \
GL_ENUM( UNSIGNED_NORMALIZED                                 , 0x8C17 )                                     \
GL_ENUM( VERTEX_ARRAY_BINDING                                , 0x85B5 )                                     \
GL_ENUM( VERTEX_ATTRIB_ARRAY_INTEGER                         , 0x88FD )                                     \
GL_ENUM( ACTIVE_UNIFORM_BLOCKS                               , 0x8A36 )                                     \
GL_ENUM( ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH                , 0x8A35 )                                     \
GL_ENUM( COPY_READ_BUFFER                                    , 0x8F36 )                                     \
GL_ENUM( COPY_WRITE_BUFFER                                   , 0x8F37 )                                     \
GL_ENUM( INT_SAMPLER_2D_RECT                                 , 0x8DCD )                                     \
GL_ENUM( INT_SAMPLER_BUFFER                                  , 0x8DD0 )                                     \
GL_ENUM( INVALID_INDEX                                       , 0xFFFFFFFF )                                 \
GL_ENUM( MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS            , 0x8A33 )                                     \
GL_ENUM( MAX_COMBINED_UNIFORM_BLOCKS                         , 0x8A2E )                                     \
GL_ENUM( MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS              , 0x8A31 )                                     \
GL_ENUM( MAX_FRAGMENT_UNIFORM_BLOCKS                         , 0x8A2D )                                     \
GL_ENUM( MAX_RECTANGLE_TEXTURE_SIZE                          , 0x84F8 )                                     \
GL_ENUM( MAX_TEXTURE_BUFFER_SIZE                             , 0x8C2B )                                     \
GL_ENUM( MAX_UNIFORM_BLOCK_SIZE                              , 0x8A30 )                                     \
GL_ENUM( MAX_UNIFORM_BUFFER_BINDINGS                         , 0x8A2F )                                     \
GL_ENUM( MAX_VERTEX_UNIFORM_BLOCKS                           , 0x8A2B )                                     \
GL_ENUM( PRIMITIVE_RESTART                                   , 0x8F9D )                                     \
GL_ENUM( PRIMITIVE_RESTART_INDEX                             , 0x8F9E )                                     \
GL_ENUM( PROXY_TEXTURE_RECTANGLE                             , 0x84F7 )                                     \
GL_ENUM( R16_SNORM                                           , 0x8F98 )                                     \
GL_ENUM( R8_SNORM                                            , 0x8F94 )                                     \
GL_ENUM( RG16_SNORM                                          , 0x8F99 )                                     \
GL_ENUM( RG8_SNORM                                           , 0x8F95 )                                     \
GL_ENUM( RGB16_SNORM                                         , 0x8F9A )                                     \
GL_ENUM( RGB8_SNORM                                          , 0x8F96 )                                     \
GL_ENUM( RGBA16_SNORM                                        , 0x8F9B )                                     \
GL_ENUM( RGBA8_SNORM                                         , 0x8F97 )                                     \
GL_ENUM( SAMPLER_2D_RECT                                     , 0x8B63 )                                     \
GL_ENUM( SAMPLER_2D_RECT_SHADOW                              , 0x8B64 )                                     \
GL_ENUM( SAMPLER_BUFFER                                      , 0x8DC2 )                                     \
GL_ENUM( SIGNED_NORMALIZED                                   , 0x8F9C )                                     \
GL_ENUM( TEXTURE_BINDING_BUFFER                              , 0x8C2C )                                     \
GL_ENUM( TEXTURE_BINDING_RECTANGLE                           , 0x84F6 )                                     \
GL_ENUM( TEXTURE_BUFFER                                      , 0x8C2A )                                     \
GL_ENUM( TEXTURE_BUFFER_DATA_STORE_BINDING                   , 0x8C2D )                                     \
GL_ENUM( TEXTURE_RECTANGLE                                   , 0x84F5 )                                     \
GL_ENUM( UNIFORM_ARRAY_STRIDE                                , 0x8A3C )                                     \
GL_ENUM( UNIFORM_BLOCK_ACTIVE_UNIFORMS                       , 0x8A42 )                                     \
GL_ENUM( UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES                , 0x8A43 )                                     \
GL_ENUM( UNIFORM_BLOCK_BINDING                               , 0x8A3F )                                     \
GL_ENUM( UNIFORM_BLOCK_DATA_SIZE                             , 0x8A40 )                                     \
GL_ENUM( UNIFORM_BLOCK_INDEX                                 , 0x8A3A )                                     \
GL_ENUM( UNIFORM_BLOCK_NAME_LENGTH                           , 0x8A41 )                                     \
GL_ENUM( UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER         , 0x8A46 )                                     \
GL_ENUM( UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER           , 0x8A44 )                                     \
GL_ENUM( UNIFORM_BUFFER                                      , 0x8A11 )                                     \
GL_ENUM( UNIFORM_BUFFER_BINDING                              , 0x8A28 )                                     \
GL_ENUM( UNIFORM_BUFFER_OFFSET_ALIGNMENT                     , 0x8A34 )                                     \
GL_ENUM( UNIFORM_BUFFER_SIZE                                 , 0x8A2A )                                     \
GL_ENUM( UNIFORM_BUFFER_START                                , 0x8A29 )                                     \
GL_ENUM( UNIFORM_IS_ROW_MAJOR                                , 0x8A3E )                                     \
GL_ENUM( UNIFORM_MATRIX_STRIDE                               , 0x8A3D )                                     \
GL_ENUM( UNIFORM_NAME_LENGTH                                 , 0x8A39 )                                     \
GL_ENUM( UNIFORM_OFFSET                                      , 0x8A3B )                                     \
GL_ENUM( UNIFORM_SIZE                                        , 0x8A38 )                                     \
GL_ENUM( UNIFORM_TYPE                                        , 0x8A37 )                                     \
GL_ENUM( UNSIGNED_INT_SAMPLER_2D_RECT                        , 0x8DD5 )                                     \
GL_ENUM( UNSIGNED_INT_SAMPLER_BUFFER                         , 0x8DD8 )                                     \
GL_ENUM( ALREADY_SIGNALED                                    , 0x911A )                                     \
GL_ENUM( CONDITION_SATISFIED                                 , 0x911C )                                     \
GL_ENUM( CONTEXT_COMPATIBILITY_PROFILE_BIT                   , 0x00000002)                                  \
GL_ENUM( CONTEXT_CORE_PROFILE_BIT                            , 0x00000001)                                  \
GL_ENUM( CONTEXT_PROFILE_MASK                                , 0x9126 )                                     \
GL_ENUM( DEPTH_CLAMP                                         , 0x864F )                                     \
GL_ENUM( FIRST_VERTEX_CONVENTION                             , 0x8E4D )                                     \
GL_ENUM( FRAMEBUFFER_ATTACHMENT_LAYERED                      , 0x8DA7 )                                     \
GL_ENUM( FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS                , 0x8DA8 )                                     \
GL_ENUM( GEOMETRY_INPUT_TYPE                                 , 0x8917 )                                     \
GL_ENUM( GEOMETRY_OUTPUT_TYPE                                , 0x8918 )                                     \
GL_ENUM( GEOMETRY_SHADER                                     , 0x8DD9 )                                     \
GL_ENUM( GEOMETRY_VERTICES_OUT                               , 0x8916 )                                     \
GL_ENUM( INT_SAMPLER_2D_MULTISAMPLE                          , 0x9109 )                                     \
GL_ENUM( INT_SAMPLER_2D_MULTISAMPLE_ARRAY                    , 0x910C )                                     \
GL_ENUM( LAST_VERTEX_CONVENTION                              , 0x8E4E )                                     \
GL_ENUM( LINES_ADJACENCY                                     , 0x000A )                                     \
GL_ENUM( LINE_STRIP_ADJACENCY                                , 0x000B )                                     \
GL_ENUM( MAX_COLOR_TEXTURE_SAMPLES                           , 0x910E )                                     \
GL_ENUM( MAX_DEPTH_TEXTURE_SAMPLES                           , 0x910F )                                     \
GL_ENUM( MAX_FRAGMENT_INPUT_COMPONENTS                       , 0x9125 )                                     \
GL_ENUM( MAX_GEOMETRY_INPUT_COMPONENTS                       , 0x9123 )                                     \
GL_ENUM( MAX_GEOMETRY_OUTPUT_COMPONENTS                      , 0x9124 )                                     \
GL_ENUM( MAX_GEOMETRY_OUTPUT_VERTICES                        , 0x8DE0 )                                     \
GL_ENUM( MAX_GEOMETRY_TEXTURE_IMAGE_UNITS                    , 0x8C29 )                                     \
GL_ENUM( MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS                , 0x8DE1 )                                     \
GL_ENUM( MAX_GEOMETRY_UNIFORM_COMPONENTS                     , 0x8DDF )                                     \
GL_ENUM( MAX_INTEGER_SAMPLES                                 , 0x9110 )                                     \
GL_ENUM( MAX_SAMPLE_MASK_WORDS                               , 0x8E59 )                                     \
GL_ENUM( MAX_SERVER_WAIT_TIMEOUT                             , 0x9111 )                                     \
GL_ENUM( MAX_VERTEX_OUTPUT_COMPONENTS                        , 0x9122 )                                     \
GL_ENUM( OBJECT_TYPE                                         , 0x9112 )                                     \
GL_ENUM( PROGRAM_POINT_SIZE                                  , 0x8642 )                                     \
GL_ENUM( PROVOKING_VERTEX                                    , 0x8E4F )                                     \
GL_ENUM( PROXY_TEXTURE_2D_MULTISAMPLE                        , 0x9101 )                                     \
GL_ENUM( PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY                  , 0x9103 )                                     \
GL_ENUM( QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION            , 0x8E4C )                                     \
GL_ENUM( SAMPLER_2D_MULTISAMPLE                              , 0x9108 )                                     \
GL_ENUM( SAMPLER_2D_MULTISAMPLE_ARRAY                        , 0x910B )                                     \
GL_ENUM( SAMPLE_MASK                                         , 0x8E51 )                                     \
GL_ENUM( SAMPLE_MASK_VALUE                                   , 0x8E52 )                                     \
GL_ENUM( SAMPLE_POSITION                                     , 0x8E50 )                                     \
GL_ENUM( SIGNALED                                            , 0x9119 )                                     \
GL_ENUM( SYNC_CONDITION                                      , 0x9113 )                                     \
GL_ENUM( SYNC_FENCE                                          , 0x9116 )                                     \
GL_ENUM( SYNC_FLAGS                                          , 0x9115 )                                     \
GL_ENUM( SYNC_FLUSH_COMMANDS_BIT                             , 0x00000001 )                                 \
GL_ENUM( SYNC_GPU_COMMANDS_COMPLETE                          , 0x9117 )                                     \
GL_ENUM( SYNC_STATUS                                         , 0x9114 )                                     \
GL_ENUM( TEXTURE_2D_MULTISAMPLE                              , 0x9100 )                                     \
GL_ENUM( TEXTURE_2D_MULTISAMPLE_ARRAY                        , 0x9102 )                                     \
GL_ENUM( TEXTURE_BINDING_2D_MULTISAMPLE                      , 0x9104 )                                     \
GL_ENUM( TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY                , 0x9105 )                                     \
GL_ENUM( TEXTURE_CUBE_MAP_SEAMLESS                           , 0x884F )                                     \
GL_ENUM( TEXTURE_FIXED_SAMPLE_LOCATIONS                      , 0x9107 )                                     \
GL_ENUM( TEXTURE_SAMPLES                                     , 0x9106 )                                     \
GL_ENUM( TIMEOUT_EXPIRED                                     , 0x911B )                                     \
GL_ENUM( TIMEOUT_IGNORED                                     , 0xFFFFFFFFFFFFFFFF )                         \
GL_ENUM( TRIANGLES_ADJACENCY                                 , 0x000C )                                     \
GL_ENUM( TRIANGLE_STRIP_ADJACENCY                            , 0x000D )                                     \
GL_ENUM( UNSIGNALED                                          , 0x9118 )                                     \
GL_ENUM( UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE                 , 0x910A )                                     \
GL_ENUM( UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY           , 0x910D )                                     \
GL_ENUM( WAIT_FAILED_                                        , 0x911D )                                     \
GL_ENUM( ANY_SAMPLES_PASSED                                  , 0x8C2F )                                     \
GL_ENUM( INT_2_10_10_10_REV                                  , 0x8D9F )                                     \
GL_ENUM( MAX_DUAL_SOURCE_DRAW_BUFFERS                        , 0x88FC )                                     \
GL_ENUM( ONE_MINUS_SRC1_ALPHA                                , 0x88FB )                                     \
GL_ENUM( ONE_MINUS_SRC1_COLOR                                , 0x88FA )                                     \
GL_ENUM( RGB10_A2UI                                          , 0x906F )                                     \
GL_ENUM( SAMPLER_BINDING                                     , 0x8919 )                                     \
GL_ENUM( SRC1_COLOR                                          , 0x88F9 )                                     \
GL_ENUM( TEXTURE_SWIZZLE_A                                   , 0x8E45 )                                     \
GL_ENUM( TEXTURE_SWIZZLE_B                                   , 0x8E44 )                                     \
GL_ENUM( TEXTURE_SWIZZLE_G                                   , 0x8E43 )                                     \
GL_ENUM( TEXTURE_SWIZZLE_R                                   , 0x8E42 )                                     \
GL_ENUM( TEXTURE_SWIZZLE_RGBA                                , 0x8E46 )                                     \
GL_ENUM( TIMESTAMP                                           , 0x8E28 )                                     \
GL_ENUM( TIME_ELAPSED                                        , 0x88BF )                                     \
GL_ENUM( VERTEX_ATTRIB_ARRAY_DIVISOR                         , 0x88FE )                                     \
GL_ENUM( ACTIVE_SUBROUTINES                                  , 0x8DE5 )                                     \
GL_ENUM( ACTIVE_SUBROUTINE_MAX_LENGTH                        , 0x8E48 )                                     \
GL_ENUM( ACTIVE_SUBROUTINE_UNIFORMS                          , 0x8DE6 )                                     \
GL_ENUM( ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS                 , 0x8E47 )                                     \
GL_ENUM( ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH                , 0x8E49 )                                     \
GL_ENUM( DOUBLE_MAT2                                         , 0x8F46 )                                     \
GL_ENUM( DOUBLE_MAT2x3                                       , 0x8F49 )                                     \
GL_ENUM( DOUBLE_MAT2x4                                       , 0x8F4A )                                     \
GL_ENUM( DOUBLE_MAT3                                         , 0x8F47 )                                     \
GL_ENUM( DOUBLE_MAT3x2                                       , 0x8F4B )                                     \
GL_ENUM( DOUBLE_MAT3x4                                       , 0x8F4C )                                     \
GL_ENUM( DOUBLE_MAT4                                         , 0x8F48 )                                     \
GL_ENUM( DOUBLE_MAT4x2                                       , 0x8F4D )                                     \
GL_ENUM( DOUBLE_MAT4x3                                       , 0x8F4E )                                     \
GL_ENUM( DOUBLE_VEC2                                         , 0x8FFC )                                     \
GL_ENUM( DOUBLE_VEC3                                         , 0x8FFD )                                     \
GL_ENUM( DOUBLE_VEC4                                         , 0x8FFE )                                     \
GL_ENUM( DRAW_INDIRECT_BUFFER                                , 0x8F3F )                                     \
GL_ENUM( DRAW_INDIRECT_BUFFER_BINDING                        , 0x8F43 )                                     \
GL_ENUM( FRACTIONAL_EVEN                                     , 0x8E7C )                                     \
GL_ENUM( FRACTIONAL_ODD                                      , 0x8E7B )                                     \
GL_ENUM( FRAGMENT_INTERPOLATION_OFFSET_BITS                  , 0x8E5D )                                     \
GL_ENUM( GEOMETRY_SHADER_INVOCATIONS                         , 0x887F )                                     \
GL_ENUM( INT_SAMPLER_CUBE_MAP_ARRAY                          , 0x900E )                                     \
GL_ENUM( ISOLINES                                            , 0x8E7A )                                     \
GL_ENUM( MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS        , 0x8E1E )                                     \
GL_ENUM( MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS     , 0x8E1F )                                     \
GL_ENUM( MAX_FRAGMENT_INTERPOLATION_OFFSET                   , 0x8E5C )                                     \
GL_ENUM( MAX_GEOMETRY_SHADER_INVOCATIONS                     , 0x8E5A )                                     \
GL_ENUM( MAX_PATCH_VERTICES                                  , 0x8E7D )                                     \
GL_ENUM( MAX_PROGRAM_TEXTURE_GATHER_OFFSET                   , 0x8E5F )                                     \
GL_ENUM( MAX_SUBROUTINES                                     , 0x8DE7 )                                     \
GL_ENUM( MAX_SUBROUTINE_UNIFORM_LOCATIONS                    , 0x8DE8 )                                     \
GL_ENUM( MAX_TESS_CONTROL_INPUT_COMPONENTS                   , 0x886C )                                     \
GL_ENUM( MAX_TESS_CONTROL_OUTPUT_COMPONENTS                  , 0x8E83 )                                     \
GL_ENUM( MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS                , 0x8E81 )                                     \
GL_ENUM( MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS            , 0x8E85 )                                     \
GL_ENUM( MAX_TESS_CONTROL_UNIFORM_BLOCKS                     , 0x8E89 )                                     \
GL_ENUM( MAX_TESS_CONTROL_UNIFORM_COMPONENTS                 , 0x8E7F )                                     \
GL_ENUM( MAX_TESS_EVALUATION_INPUT_COMPONENTS                , 0x886D )                                     \
GL_ENUM( MAX_TESS_EVALUATION_OUTPUT_COMPONENTS               , 0x8E86 )                                     \
GL_ENUM( MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS             , 0x8E82 )                                     \
GL_ENUM( MAX_TESS_EVALUATION_UNIFORM_BLOCKS                  , 0x8E8A )                                     \
GL_ENUM( MAX_TESS_EVALUATION_UNIFORM_COMPONENTS              , 0x8E80 )                                     \
GL_ENUM( MAX_TESS_GEN_LEVEL                                  , 0x8E7E )                                     \
GL_ENUM( MAX_TESS_PATCH_COMPONENTS                           , 0x8E84 )                                     \
GL_ENUM( MAX_TRANSFORM_FEEDBACK_BUFFERS                      , 0x8E70 )                                     \
GL_ENUM( MAX_VERTEX_STREAMS                                  , 0x8E71 )                                     \
GL_ENUM( MIN_FRAGMENT_INTERPOLATION_OFFSET                   , 0x8E5B )                                     \
GL_ENUM( MIN_PROGRAM_TEXTURE_GATHER_OFFSET                   , 0x8E5E )                                     \
GL_ENUM( MIN_SAMPLE_SHADING_VALUE                            , 0x8C37 )                                     \
GL_ENUM( PATCHES                                             , 0x000E )                                     \
GL_ENUM( PATCH_DEFAULT_INNER_LEVEL                           , 0x8E73 )                                     \
GL_ENUM( PATCH_DEFAULT_OUTER_LEVEL                           , 0x8E74 )                                     \
GL_ENUM( PATCH_VERTICES                                      , 0x8E72 )                                     \
GL_ENUM( PROXY_TEXTURE_CUBE_MAP_ARRAY                        , 0x900B )                                     \
GL_ENUM( SAMPLER_CUBE_MAP_ARRAY                              , 0x900C )                                     \
GL_ENUM( SAMPLER_CUBE_MAP_ARRAY_SHADOW                       , 0x900D )                                     \
GL_ENUM( SAMPLE_SHADING                                      , 0x8C36 )                                     \
GL_ENUM( TESS_CONTROL_OUTPUT_VERTICES                        , 0x8E75 )                                     \
GL_ENUM( TESS_CONTROL_SHADER                                 , 0x8E88 )                                     \
GL_ENUM( TESS_EVALUATION_SHADER                              , 0x8E87 )                                     \
GL_ENUM( TESS_GEN_MODE                                       , 0x8E76 )                                     \
GL_ENUM( TESS_GEN_POINT_MODE                                 , 0x8E79 )                                     \
GL_ENUM( TESS_GEN_SPACING                                    , 0x8E77 )                                     \
GL_ENUM( TESS_GEN_VERTEX_ORDER                               , 0x8E78 )                                     \
GL_ENUM( TEXTURE_BINDING_CUBE_MAP_ARRAY                      , 0x900A )                                     \
GL_ENUM( TEXTURE_CUBE_MAP_ARRAY                              , 0x9009 )                                     \
GL_ENUM( TRANSFORM_FEEDBACK                                  , 0x8E22 )                                     \
GL_ENUM( TRANSFORM_FEEDBACK_BINDING                          , 0x8E25 )                                     \
GL_ENUM( TRANSFORM_FEEDBACK_BUFFER_ACTIVE                    , 0x8E24 )                                     \
GL_ENUM( TRANSFORM_FEEDBACK_BUFFER_PAUSED                    , 0x8E23 )                                     \
GL_ENUM( UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER     , 0x84F0 )                                     \
GL_ENUM( UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER  , 0x84F1 )                                     \
GL_ENUM( UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY                 , 0x900F )                                     \
GL_ENUM( ACTIVE_PROGRAM                                      , 0x8259 )                                     \
GL_ENUM( ALL_SHADER_BITS                                     , 0xFFFFFFFF )                                 \
GL_ENUM( FIXED                                               , 0x140C )                                     \
GL_ENUM( FRAGMENT_SHADER_BIT                                 , 0x00000002 )                                 \
GL_ENUM( GEOMETRY_SHADER_BIT                                 , 0x00000004 )                                 \
GL_ENUM( HIGH_FLOAT                                          , 0x8DF2 )                                     \
GL_ENUM( HIGH_INT                                            , 0x8DF5 )                                     \
GL_ENUM( IMPLEMENTATION_COLOR_READ_FORMAT                    , 0x8B9B )                                     \
GL_ENUM( IMPLEMENTATION_COLOR_READ_TYPE                      , 0x8B9A )                                     \
GL_ENUM( LAYER_PROVOKING_VERTEX                              , 0x825E )                                     \
GL_ENUM( LOW_FLOAT                                           , 0x8DF0 )                                     \
GL_ENUM( LOW_INT                                             , 0x8DF3 )                                     \
GL_ENUM( MAX_FRAGMENT_UNIFORM_VECTORS                        , 0x8DFD )                                     \
GL_ENUM( MAX_VARYING_VECTORS                                 , 0x8DFC )                                     \
GL_ENUM( MAX_VERTEX_UNIFORM_VECTORS                          , 0x8DFB )                                     \
GL_ENUM( MAX_VIEWPORTS                                       , 0x825B )                                     \
GL_ENUM( MEDIUM_FLOAT                                        , 0x8DF1 )                                     \
GL_ENUM( MEDIUM_INT                                          , 0x8DF4 )                                     \
GL_ENUM( NUM_PROGRAM_BINARY_FORMATS                          , 0x87FE )                                     \
GL_ENUM( NUM_SHADER_BINARY_FORMATS                           , 0x8DF9 )                                     \
GL_ENUM( PROGRAM_BINARY_FORMATS                              , 0x87FF )                                     \
GL_ENUM( PROGRAM_BINARY_LENGTH                               , 0x8741 )                                     \
GL_ENUM( PROGRAM_BINARY_RETRIEVABLE_HINT                     , 0x8257 )                                     \
GL_ENUM( PROGRAM_PIPELINE_BINDING                            , 0x825A )                                     \
GL_ENUM( PROGRAM_SEPARABLE                                   , 0x8258 )                                     \
GL_ENUM( RGB565                                              , 0x8D62 )                                     \
GL_ENUM( SHADER_BINARY_FORMATS                               , 0x8DF8 )                                     \
GL_ENUM( SHADER_COMPILER                                     , 0x8DFA )                                     \
GL_ENUM( TESS_CONTROL_SHADER_BIT                             , 0x00000008 )                                 \
GL_ENUM( TESS_EVALUATION_SHADER_BIT                          , 0x00000010 )                                 \
GL_ENUM( UNDEFINED_VERTEX                                    , 0x8260 )                                     \
GL_ENUM( VERTEX_SHADER_BIT                                   , 0x00000001 )                                 \
GL_ENUM( VIEWPORT_BOUNDS_RANGE                               , 0x825D )                                     \
GL_ENUM( VIEWPORT_INDEX_PROVOKING_VERTEX                     , 0x825F )                                     \
GL_ENUM( VIEWPORT_SUBPIXEL_BITS                              , 0x825C )


	enum EGLEnum
	{
        GL_EXPAND_ENUM
	};
	
	namespace _detail
	{
		extern void (CODEGEN_FUNCPTR *CompressedTexImage1DARB)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid * data);
		extern void (CODEGEN_FUNCPTR *CompressedTexImage2DARB)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid * data);
		extern void (CODEGEN_FUNCPTR *CompressedTexImage3DARB)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid * data);
		extern void (CODEGEN_FUNCPTR *CompressedTexSubImage1DARB)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid * data);
		extern void (CODEGEN_FUNCPTR *CompressedTexSubImage2DARB)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid * data);
		extern void (CODEGEN_FUNCPTR *CompressedTexSubImage3DARB)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid * data);
		extern void (CODEGEN_FUNCPTR *GetCompressedTexImageARB)(GLenum target, GLint level, GLvoid * img);
		
		
		extern void (CODEGEN_FUNCPTR *GetProgramInterfaceiv)(GLuint program, GLenum programInterface, GLenum pname, GLint * params);
		extern GLuint (CODEGEN_FUNCPTR *GetProgramResourceIndex)(GLuint program, GLenum programInterface, const GLchar * name);
		extern GLint (CODEGEN_FUNCPTR *GetProgramResourceLocation)(GLuint program, GLenum programInterface, const GLchar * name);
		extern GLint (CODEGEN_FUNCPTR *GetProgramResourceLocationIndex)(GLuint program, GLenum programInterface, const GLchar * name);
		extern void (CODEGEN_FUNCPTR *GetProgramResourceName)(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name);
		extern void (CODEGEN_FUNCPTR *GetProgramResourceiv)(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum * props, GLsizei bufSize, GLsizei * length, GLint * params);
		
		extern void (CODEGEN_FUNCPTR *BlendFunc)(GLenum sfactor, GLenum dfactor);
		extern void (CODEGEN_FUNCPTR *Clear)(GLbitfield mask);
		extern void (CODEGEN_FUNCPTR *ClearColor)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
		extern void (CODEGEN_FUNCPTR *ClearDepth)(GLdouble depth);
		extern void (CODEGEN_FUNCPTR *ClearStencil)(GLint s);
		extern void (CODEGEN_FUNCPTR *ColorMask)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
		extern void (CODEGEN_FUNCPTR *CullFace)(GLenum mode);
		extern void (CODEGEN_FUNCPTR *DepthFunc)(GLenum func);
		extern void (CODEGEN_FUNCPTR *DepthMask)(GLboolean flag);
		extern void (CODEGEN_FUNCPTR *DepthRange)(GLdouble ren_near, GLdouble ren_far);
		extern void (CODEGEN_FUNCPTR *Disable)(GLenum cap);
		extern void (CODEGEN_FUNCPTR *DrawBuffer)(GLenum mode);
		extern void (CODEGEN_FUNCPTR *Enable)(GLenum cap);
		extern void (CODEGEN_FUNCPTR *Finish)();
		extern void (CODEGEN_FUNCPTR *Flush)();
		extern void (CODEGEN_FUNCPTR *FrontFace)(GLenum mode);
		extern void (CODEGEN_FUNCPTR *GetBooleanv)(GLenum pname, GLboolean * params);
		extern void (CODEGEN_FUNCPTR *GetDoublev)(GLenum pname, GLdouble * params);
		extern GLenum (CODEGEN_FUNCPTR *GetError)();
		extern void (CODEGEN_FUNCPTR *GetFloatv)(GLenum pname, GLfloat * params);
		extern void (CODEGEN_FUNCPTR *GetIntegerv)(GLenum pname, GLint * params);
OPENGL_API		extern const GLubyte * (CODEGEN_FUNCPTR *GetString)(GLenum name);
		extern void (CODEGEN_FUNCPTR *GetTexImage)(GLenum target, GLint level, GLenum format, GLenum type, GLvoid * pixels);
		extern void (CODEGEN_FUNCPTR *GetTexLevelParameterfv)(GLenum target, GLint level, GLenum pname, GLfloat * params);
		extern void (CODEGEN_FUNCPTR *GetTexLevelParameteriv)(GLenum target, GLint level, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetTexParameterfv)(GLenum target, GLenum pname, GLfloat * params);
		extern void (CODEGEN_FUNCPTR *GetTexParameteriv)(GLenum target, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *Hint)(GLenum target, GLenum mode);
		extern GLboolean (CODEGEN_FUNCPTR *IsEnabled)(GLenum cap);
		extern void (CODEGEN_FUNCPTR *LineWidth)(GLfloat width);
		extern void (CODEGEN_FUNCPTR *LogicOp)(GLenum opcode);
		extern void (CODEGEN_FUNCPTR *PixelStoref)(GLenum pname, GLfloat param);
		extern void (CODEGEN_FUNCPTR *PixelStorei)(GLenum pname, GLint param);
		extern void (CODEGEN_FUNCPTR *PointSize)(GLfloat size);
		extern void (CODEGEN_FUNCPTR *PolygonMode)(GLenum face, GLenum mode);
		extern void (CODEGEN_FUNCPTR *ReadBuffer)(GLenum mode);
		extern void (CODEGEN_FUNCPTR *ReadPixels)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid * pixels);
		extern void (CODEGEN_FUNCPTR *Scissor)(GLint x, GLint y, GLsizei width, GLsizei height);
		extern void (CODEGEN_FUNCPTR *StencilFunc)(GLenum func, GLint ref, GLuint mask);
		extern void (CODEGEN_FUNCPTR *StencilMask)(GLuint mask);
		extern void (CODEGEN_FUNCPTR *StencilOp)(GLenum fail, GLenum zfail, GLenum zpass);
		extern void (CODEGEN_FUNCPTR *TexImage1D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid * pixels);
		extern void (CODEGEN_FUNCPTR *TexImage2D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid * pixels);
		extern void (CODEGEN_FUNCPTR *TexParameterf)(GLenum target, GLenum pname, GLfloat param);
		extern void (CODEGEN_FUNCPTR *TexParameterfv)(GLenum target, GLenum pname, const GLfloat * params);
		extern void (CODEGEN_FUNCPTR *TexParameteri)(GLenum target, GLenum pname, GLint param);
		extern void (CODEGEN_FUNCPTR *TexParameteriv)(GLenum target, GLenum pname, const GLint * params);
		extern void (CODEGEN_FUNCPTR *Viewport)(GLint x, GLint y, GLsizei width, GLsizei height);
		
		extern void (CODEGEN_FUNCPTR *BindTexture)(GLenum target, GLuint texture);
		extern void (CODEGEN_FUNCPTR *CopyTexImage1D)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
		extern void (CODEGEN_FUNCPTR *CopyTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
		extern void (CODEGEN_FUNCPTR *CopyTexSubImage1D)(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
		extern void (CODEGEN_FUNCPTR *CopyTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
		extern void (CODEGEN_FUNCPTR *DeleteTextures)(GLsizei n, const GLuint * textures);
		extern void (CODEGEN_FUNCPTR *DrawArrays)(GLenum mode, GLint first, GLsizei count);
		extern void (CODEGEN_FUNCPTR *DrawElements)(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices);
		extern void (CODEGEN_FUNCPTR *GenTextures)(GLsizei n, GLuint * textures);
		extern GLboolean (CODEGEN_FUNCPTR *IsTexture)(GLuint texture);
		extern void (CODEGEN_FUNCPTR *PolygonOffset)(GLfloat factor, GLfloat units);
		extern void (CODEGEN_FUNCPTR *TexSubImage1D)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid * pixels);
		extern void (CODEGEN_FUNCPTR *TexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels);
		
		extern void (CODEGEN_FUNCPTR *BlendColor)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
		extern void (CODEGEN_FUNCPTR *BlendEquation)(GLenum mode);
		extern void (CODEGEN_FUNCPTR *CopyTexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
		extern void (CODEGEN_FUNCPTR *DrawRangeElements)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid * indices);
		extern void (CODEGEN_FUNCPTR *TexImage3D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid * pixels);
		extern void (CODEGEN_FUNCPTR *TexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid * pixels);
		
		extern void (CODEGEN_FUNCPTR *ActiveTexture)(GLenum texture);
		extern void (CODEGEN_FUNCPTR *CompressedTexImage1D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid * data);
		extern void (CODEGEN_FUNCPTR *CompressedTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid * data);
		extern void (CODEGEN_FUNCPTR *CompressedTexImage3D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid * data);
		extern void (CODEGEN_FUNCPTR *CompressedTexSubImage1D)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid * data);
		extern void (CODEGEN_FUNCPTR *CompressedTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid * data);
		extern void (CODEGEN_FUNCPTR *CompressedTexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid * data);
		extern void (CODEGEN_FUNCPTR *GetCompressedTexImage)(GLenum target, GLint level, GLvoid * img);
		extern void (CODEGEN_FUNCPTR *SampleCoverage)(GLfloat value, GLboolean invert);
		
		extern void (CODEGEN_FUNCPTR *BlendFuncSeparate)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
		extern void (CODEGEN_FUNCPTR *MultiDrawArrays)(GLenum mode, const GLint * first, const GLsizei * count, GLsizei drawcount);
		extern void (CODEGEN_FUNCPTR *MultiDrawElements)(GLenum mode, const GLsizei * count, GLenum type, const GLvoid *const* indices, GLsizei drawcount);
		extern void (CODEGEN_FUNCPTR *PointParameterf)(GLenum pname, GLfloat param);
		extern void (CODEGEN_FUNCPTR *PointParameterfv)(GLenum pname, const GLfloat * params);
		extern void (CODEGEN_FUNCPTR *PointParameteri)(GLenum pname, GLint param);
		extern void (CODEGEN_FUNCPTR *PointParameteriv)(GLenum pname, const GLint * params);
		
		extern void (CODEGEN_FUNCPTR *BeginQuery)(GLenum target, GLuint id);
		extern void (CODEGEN_FUNCPTR *BindBuffer)(GLenum target, GLuint buffer);
		extern void (CODEGEN_FUNCPTR *BufferData)(GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage);
		extern void (CODEGEN_FUNCPTR *BufferSubData)(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid * data);
		extern void (CODEGEN_FUNCPTR *DeleteBuffers)(GLsizei n, const GLuint * buffers);
		extern void (CODEGEN_FUNCPTR *DeleteQueries)(GLsizei n, const GLuint * ids);
		extern void (CODEGEN_FUNCPTR *EndQuery)(GLenum target);
		extern void (CODEGEN_FUNCPTR *GenBuffers)(GLsizei n, GLuint * buffers);
		extern void (CODEGEN_FUNCPTR *GenQueries)(GLsizei n, GLuint * ids);
		extern void (CODEGEN_FUNCPTR *GetBufferParameteriv)(GLenum target, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetBufferPointerv)(GLenum target, GLenum pname, GLvoid ** params);
		extern void (CODEGEN_FUNCPTR *GetBufferSubData)(GLenum target, GLintptr offset, GLsizeiptr size, GLvoid * data);
		extern void (CODEGEN_FUNCPTR *GetQueryObjectiv)(GLuint id, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetQueryObjectuiv)(GLuint id, GLenum pname, GLuint * params);
		extern void (CODEGEN_FUNCPTR *GetQueryiv)(GLenum target, GLenum pname, GLint * params);
		extern GLboolean (CODEGEN_FUNCPTR *IsBuffer)(GLuint buffer);
		extern GLboolean (CODEGEN_FUNCPTR *IsQuery)(GLuint id);
		extern void * (CODEGEN_FUNCPTR *MapBuffer)(GLenum target, GLenum access);
		extern GLboolean (CODEGEN_FUNCPTR *UnmapBuffer)(GLenum target);
		
		extern void (CODEGEN_FUNCPTR *AttachShader)(GLuint program, GLuint shader);
		extern void (CODEGEN_FUNCPTR *BindAttribLocation)(GLuint program, GLuint index, const GLchar * name);
		extern void (CODEGEN_FUNCPTR *BlendEquationSeparate)(GLenum modeRGB, GLenum modeAlpha);
		extern void (CODEGEN_FUNCPTR *CompileShader)(GLuint shader);
		extern GLuint (CODEGEN_FUNCPTR *CreateProgram)();
		extern GLuint (CODEGEN_FUNCPTR *CreateShader)(GLenum type);
		extern void (CODEGEN_FUNCPTR *DeleteProgram)(GLuint program);
		extern void (CODEGEN_FUNCPTR *DeleteShader)(GLuint shader);
		extern void (CODEGEN_FUNCPTR *DetachShader)(GLuint program, GLuint shader);
		extern void (CODEGEN_FUNCPTR *DisableVertexAttribArray)(GLuint index);
		extern void (CODEGEN_FUNCPTR *DrawBuffers)(GLsizei n, const GLenum * bufs);
		extern void (CODEGEN_FUNCPTR *EnableVertexAttribArray)(GLuint index);
		extern void (CODEGEN_FUNCPTR *GetActiveAttrib)(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
		extern void (CODEGEN_FUNCPTR *GetActiveUniform)(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
		extern void (CODEGEN_FUNCPTR *GetAttachedShaders)(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders);
		extern GLint (CODEGEN_FUNCPTR *GetAttribLocation)(GLuint program, const GLchar * name);
		extern void (CODEGEN_FUNCPTR *GetProgramInfoLog)(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
		extern void (CODEGEN_FUNCPTR *GetProgramiv)(GLuint program, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetShaderInfoLog)(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
		extern void (CODEGEN_FUNCPTR *GetShaderSource)(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source);
		extern void (CODEGEN_FUNCPTR *GetShaderiv)(GLuint shader, GLenum pname, GLint * params);
		extern GLint (CODEGEN_FUNCPTR *GetUniformLocation)(GLuint program, const GLchar * name);
		extern void (CODEGEN_FUNCPTR *GetUniformfv)(GLuint program, GLint location, GLfloat * params);
		extern void (CODEGEN_FUNCPTR *GetUniformiv)(GLuint program, GLint location, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetVertexAttribPointerv)(GLuint index, GLenum pname, GLvoid ** pointer);
		extern void (CODEGEN_FUNCPTR *GetVertexAttribdv)(GLuint index, GLenum pname, GLdouble * params);
		extern void (CODEGEN_FUNCPTR *GetVertexAttribfv)(GLuint index, GLenum pname, GLfloat * params);
		extern void (CODEGEN_FUNCPTR *GetVertexAttribiv)(GLuint index, GLenum pname, GLint * params);
		extern GLboolean (CODEGEN_FUNCPTR *IsProgram)(GLuint program);
		extern GLboolean (CODEGEN_FUNCPTR *IsShader)(GLuint shader);
		extern void (CODEGEN_FUNCPTR *LinkProgram)(GLuint program);
		extern void (CODEGEN_FUNCPTR *ShaderSource)(GLuint shader, GLsizei count, const GLchar *const* string, const GLint * length);
		extern void (CODEGEN_FUNCPTR *StencilFuncSeparate)(GLenum face, GLenum func, GLint ref, GLuint mask);
		extern void (CODEGEN_FUNCPTR *StencilMaskSeparate)(GLenum face, GLuint mask);
		extern void (CODEGEN_FUNCPTR *StencilOpSeparate)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
		extern void (CODEGEN_FUNCPTR *Uniform1f)(GLint location, GLfloat v0);
		extern void (CODEGEN_FUNCPTR *Uniform1fv)(GLint location, GLsizei count, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *Uniform1i)(GLint location, GLint v0);
		extern void (CODEGEN_FUNCPTR *Uniform1iv)(GLint location, GLsizei count, const GLint * value);
		extern void (CODEGEN_FUNCPTR *Uniform2f)(GLint location, GLfloat v0, GLfloat v1);
		extern void (CODEGEN_FUNCPTR *Uniform2fv)(GLint location, GLsizei count, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *Uniform2i)(GLint location, GLint v0, GLint v1);
		extern void (CODEGEN_FUNCPTR *Uniform2iv)(GLint location, GLsizei count, const GLint * value);
		extern void (CODEGEN_FUNCPTR *Uniform3f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
		extern void (CODEGEN_FUNCPTR *Uniform3fv)(GLint location, GLsizei count, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *Uniform3i)(GLint location, GLint v0, GLint v1, GLint v2);
		extern void (CODEGEN_FUNCPTR *Uniform3iv)(GLint location, GLsizei count, const GLint * value);
		extern void (CODEGEN_FUNCPTR *Uniform4f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
		extern void (CODEGEN_FUNCPTR *Uniform4fv)(GLint location, GLsizei count, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *Uniform4i)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
		extern void (CODEGEN_FUNCPTR *Uniform4iv)(GLint location, GLsizei count, const GLint * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *UseProgram)(GLuint program);
		extern void (CODEGEN_FUNCPTR *ValidateProgram)(GLuint program);
		extern void (CODEGEN_FUNCPTR *VertexAttrib1d)(GLuint index, GLdouble x);
		extern void (CODEGEN_FUNCPTR *VertexAttrib1dv)(GLuint index, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib1f)(GLuint index, GLfloat x);
		extern void (CODEGEN_FUNCPTR *VertexAttrib1fv)(GLuint index, const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib1s)(GLuint index, GLshort x);
		extern void (CODEGEN_FUNCPTR *VertexAttrib1sv)(GLuint index, const GLshort * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib2d)(GLuint index, GLdouble x, GLdouble y);
		extern void (CODEGEN_FUNCPTR *VertexAttrib2dv)(GLuint index, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib2f)(GLuint index, GLfloat x, GLfloat y);
		extern void (CODEGEN_FUNCPTR *VertexAttrib2fv)(GLuint index, const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib2s)(GLuint index, GLshort x, GLshort y);
		extern void (CODEGEN_FUNCPTR *VertexAttrib2sv)(GLuint index, const GLshort * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib3d)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
		extern void (CODEGEN_FUNCPTR *VertexAttrib3dv)(GLuint index, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib3f)(GLuint index, GLfloat x, GLfloat y, GLfloat z);
		extern void (CODEGEN_FUNCPTR *VertexAttrib3fv)(GLuint index, const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib3s)(GLuint index, GLshort x, GLshort y, GLshort z);
		extern void (CODEGEN_FUNCPTR *VertexAttrib3sv)(GLuint index, const GLshort * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4Nbv)(GLuint index, const GLbyte * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4Niv)(GLuint index, const GLint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4Nsv)(GLuint index, const GLshort * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4Nub)(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4Nubv)(GLuint index, const GLubyte * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4Nuiv)(GLuint index, const GLuint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4Nusv)(GLuint index, const GLushort * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4bv)(GLuint index, const GLbyte * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4d)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4dv)(GLuint index, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4f)(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4fv)(GLuint index, const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4iv)(GLuint index, const GLint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4s)(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4sv)(GLuint index, const GLshort * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4ubv)(GLuint index, const GLubyte * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4uiv)(GLuint index, const GLuint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4usv)(GLuint index, const GLushort * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribPointer)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer);
		
		extern void (CODEGEN_FUNCPTR *UniformMatrix2x3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix2x4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix3x2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix3x4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix4x2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix4x3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		
		extern void (CODEGEN_FUNCPTR *BeginConditionalRender)(GLuint id, GLenum mode);
		extern void (CODEGEN_FUNCPTR *BeginTransformFeedback)(GLenum primitiveMode);
		extern void (CODEGEN_FUNCPTR *BindBufferBase)(GLenum target, GLuint index, GLuint buffer);
		extern void (CODEGEN_FUNCPTR *BindBufferRange)(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
		extern void (CODEGEN_FUNCPTR *BindFragDataLocation)(GLuint program, GLuint color, const GLchar * name);
		extern void (CODEGEN_FUNCPTR *BindFramebuffer)(GLenum target, GLuint framebuffer);
		extern void (CODEGEN_FUNCPTR *BindRenderbuffer)(GLenum target, GLuint renderbuffer);
		extern void (CODEGEN_FUNCPTR *BindVertexArray)(GLuint ren_array);
		extern void (CODEGEN_FUNCPTR *BlitFramebuffer)(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
		extern GLenum (CODEGEN_FUNCPTR *CheckFramebufferStatus)(GLenum target);
		extern void (CODEGEN_FUNCPTR *ClampColor)(GLenum target, GLenum clamp);
		extern void (CODEGEN_FUNCPTR *ClearBufferfi)(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
		extern void (CODEGEN_FUNCPTR *ClearBufferfv)(GLenum buffer, GLint drawbuffer, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *ClearBufferiv)(GLenum buffer, GLint drawbuffer, const GLint * value);
		extern void (CODEGEN_FUNCPTR *ClearBufferuiv)(GLenum buffer, GLint drawbuffer, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *ColorMaski)(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
		extern void (CODEGEN_FUNCPTR *DeleteFramebuffers)(GLsizei n, const GLuint * framebuffers);
		extern void (CODEGEN_FUNCPTR *DeleteRenderbuffers)(GLsizei n, const GLuint * renderbuffers);
		extern void (CODEGEN_FUNCPTR *DeleteVertexArrays)(GLsizei n, const GLuint * arrays);
		extern void (CODEGEN_FUNCPTR *Disablei)(GLenum target, GLuint index);
		extern void (CODEGEN_FUNCPTR *Enablei)(GLenum target, GLuint index);
		extern void (CODEGEN_FUNCPTR *EndConditionalRender)();
		extern void (CODEGEN_FUNCPTR *EndTransformFeedback)();
		extern void (CODEGEN_FUNCPTR *FlushMappedBufferRange)(GLenum target, GLintptr offset, GLsizeiptr length);
		extern void (CODEGEN_FUNCPTR *FramebufferRenderbuffer)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
		extern void (CODEGEN_FUNCPTR *FramebufferTexture1D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
		extern void (CODEGEN_FUNCPTR *FramebufferTexture2D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
		extern void (CODEGEN_FUNCPTR *FramebufferTexture3D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
		extern void (CODEGEN_FUNCPTR *FramebufferTextureLayer)(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
		extern void (CODEGEN_FUNCPTR *GenFramebuffers)(GLsizei n, GLuint * framebuffers);
		extern void (CODEGEN_FUNCPTR *GenRenderbuffers)(GLsizei n, GLuint * renderbuffers);
		extern void (CODEGEN_FUNCPTR *GenVertexArrays)(GLsizei n, GLuint * arrays);
		extern void (CODEGEN_FUNCPTR *GenerateMipmap)(GLenum target);
		extern void (CODEGEN_FUNCPTR *GetBooleani_v)(GLenum target, GLuint index, GLboolean * data);
		extern GLint (CODEGEN_FUNCPTR *GetFragDataLocation)(GLuint program, const GLchar * name);
		extern void (CODEGEN_FUNCPTR *GetFramebufferAttachmentParameteriv)(GLenum target, GLenum attachment, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetIntegeri_v)(GLenum target, GLuint index, GLint * data);
		extern void (CODEGEN_FUNCPTR *GetRenderbufferParameteriv)(GLenum target, GLenum pname, GLint * params);
		extern const GLubyte * (CODEGEN_FUNCPTR *GetStringi)(GLenum name, GLuint index);
		extern void (CODEGEN_FUNCPTR *GetTexParameterIiv)(GLenum target, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetTexParameterIuiv)(GLenum target, GLenum pname, GLuint * params);
		extern void (CODEGEN_FUNCPTR *GetTransformFeedbackVarying)(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name);
		extern void (CODEGEN_FUNCPTR *GetUniformuiv)(GLuint program, GLint location, GLuint * params);
		extern void (CODEGEN_FUNCPTR *GetVertexAttribIiv)(GLuint index, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetVertexAttribIuiv)(GLuint index, GLenum pname, GLuint * params);
		extern GLboolean (CODEGEN_FUNCPTR *IsEnabledi)(GLenum target, GLuint index);
		extern GLboolean (CODEGEN_FUNCPTR *IsFramebuffer)(GLuint framebuffer);
		extern GLboolean (CODEGEN_FUNCPTR *IsRenderbuffer)(GLuint renderbuffer);
		extern GLboolean (CODEGEN_FUNCPTR *IsVertexArray)(GLuint ren_array);
		extern void * (CODEGEN_FUNCPTR *MapBufferRange)(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
		extern void (CODEGEN_FUNCPTR *RenderbufferStorage)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
		extern void (CODEGEN_FUNCPTR *RenderbufferStorageMultisample)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
		extern void (CODEGEN_FUNCPTR *TexParameterIiv)(GLenum target, GLenum pname, const GLint * params);
		extern void (CODEGEN_FUNCPTR *TexParameterIuiv)(GLenum target, GLenum pname, const GLuint * params);
		extern void (CODEGEN_FUNCPTR *TransformFeedbackVaryings)(GLuint program, GLsizei count, const GLchar *const* varyings, GLenum bufferMode);
		extern void (CODEGEN_FUNCPTR *Uniform1ui)(GLint location, GLuint v0);
		extern void (CODEGEN_FUNCPTR *Uniform1uiv)(GLint location, GLsizei count, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *Uniform2ui)(GLint location, GLuint v0, GLuint v1);
		extern void (CODEGEN_FUNCPTR *Uniform2uiv)(GLint location, GLsizei count, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *Uniform3ui)(GLint location, GLuint v0, GLuint v1, GLuint v2);
		extern void (CODEGEN_FUNCPTR *Uniform3uiv)(GLint location, GLsizei count, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *Uniform4ui)(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
		extern void (CODEGEN_FUNCPTR *Uniform4uiv)(GLint location, GLsizei count, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *VertexAttribI1i)(GLuint index, GLint x);
		extern void (CODEGEN_FUNCPTR *VertexAttribI1iv)(GLuint index, const GLint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI1ui)(GLuint index, GLuint x);
		extern void (CODEGEN_FUNCPTR *VertexAttribI1uiv)(GLuint index, const GLuint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI2i)(GLuint index, GLint x, GLint y);
		extern void (CODEGEN_FUNCPTR *VertexAttribI2iv)(GLuint index, const GLint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI2ui)(GLuint index, GLuint x, GLuint y);
		extern void (CODEGEN_FUNCPTR *VertexAttribI2uiv)(GLuint index, const GLuint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI3i)(GLuint index, GLint x, GLint y, GLint z);
		extern void (CODEGEN_FUNCPTR *VertexAttribI3iv)(GLuint index, const GLint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI3ui)(GLuint index, GLuint x, GLuint y, GLuint z);
		extern void (CODEGEN_FUNCPTR *VertexAttribI3uiv)(GLuint index, const GLuint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI4bv)(GLuint index, const GLbyte * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI4i)(GLuint index, GLint x, GLint y, GLint z, GLint w);
		extern void (CODEGEN_FUNCPTR *VertexAttribI4iv)(GLuint index, const GLint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI4sv)(GLuint index, const GLshort * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI4ubv)(GLuint index, const GLubyte * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI4ui)(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
		extern void (CODEGEN_FUNCPTR *VertexAttribI4uiv)(GLuint index, const GLuint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI4usv)(GLuint index, const GLushort * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribIPointer)(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer);
		
		extern void (CODEGEN_FUNCPTR *CopyBufferSubData)(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
		extern void (CODEGEN_FUNCPTR *DrawArraysInstanced)(GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
		extern void (CODEGEN_FUNCPTR *DrawElementsInstanced)(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices, GLsizei instancecount);
		extern void (CODEGEN_FUNCPTR *GetActiveUniformBlockName)(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName);
		extern void (CODEGEN_FUNCPTR *GetActiveUniformBlockiv)(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetActiveUniformName)(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformName);
		extern void (CODEGEN_FUNCPTR *GetActiveUniformsiv)(GLuint program, GLsizei uniformCount, const GLuint * uniformIndices, GLenum pname, GLint * params);
		extern GLuint (CODEGEN_FUNCPTR *GetUniformBlockIndex)(GLuint program, const GLchar * uniformBlockName);
		extern void (CODEGEN_FUNCPTR *GetUniformIndices)(GLuint program, GLsizei uniformCount, const GLchar *const* uniformNames, GLuint * uniformIndices);
		extern void (CODEGEN_FUNCPTR *PrimitiveRestartIndex)(GLuint index);
		extern void (CODEGEN_FUNCPTR *TexBuffer)(GLenum target, GLenum internalformat, GLuint buffer);
		extern void (CODEGEN_FUNCPTR *UniformBlockBinding)(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
		
		extern GLenum (CODEGEN_FUNCPTR *ClientWaitSync)(GLsync sync, GLbitfield flags, GLuint64 timeout);
		extern void (CODEGEN_FUNCPTR *DeleteSync)(GLsync sync);
		extern void (CODEGEN_FUNCPTR *DrawElementsBaseVertex)(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices, GLint basevertex);
		extern void (CODEGEN_FUNCPTR *DrawElementsInstancedBaseVertex)(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices, GLsizei instancecount, GLint basevertex);
		extern void (CODEGEN_FUNCPTR *DrawRangeElementsBaseVertex)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid * indices, GLint basevertex);
		extern GLsync (CODEGEN_FUNCPTR *FenceSync)(GLenum condition, GLbitfield flags);
		extern void (CODEGEN_FUNCPTR *FramebufferTexture)(GLenum target, GLenum attachment, GLuint texture, GLint level);
		extern void (CODEGEN_FUNCPTR *GetBufferParameteri64v)(GLenum target, GLenum pname, GLint64 * params);
		extern void (CODEGEN_FUNCPTR *GetInteger64i_v)(GLenum target, GLuint index, GLint64 * data);
		extern void (CODEGEN_FUNCPTR *GetInteger64v)(GLenum pname, GLint64 * params);
		extern void (CODEGEN_FUNCPTR *GetMultisamplefv)(GLenum pname, GLuint index, GLfloat * val);
		extern void (CODEGEN_FUNCPTR *GetSynciv)(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei * length, GLint * values);
		extern GLboolean (CODEGEN_FUNCPTR *IsSync)(GLsync sync);
		extern void (CODEGEN_FUNCPTR *MultiDrawElementsBaseVertex)(GLenum mode, const GLsizei * count, GLenum type, const GLvoid *const* indices, GLsizei drawcount, const GLint * basevertex);
		extern void (CODEGEN_FUNCPTR *ProvokingVertex)(GLenum mode);
		extern void (CODEGEN_FUNCPTR *SampleMaski)(GLuint index, GLbitfield mask);
		extern void (CODEGEN_FUNCPTR *TexImage2DMultisample)(GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
		extern void (CODEGEN_FUNCPTR *TexImage3DMultisample)(GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
		extern void (CODEGEN_FUNCPTR *WaitSync)(GLsync sync, GLbitfield flags, GLuint64 timeout);
		
		extern void (CODEGEN_FUNCPTR *BindFragDataLocationIndexed)(GLuint program, GLuint colorNumber, GLuint index, const GLchar * name);
		extern void (CODEGEN_FUNCPTR *BindSampler)(GLuint unit, GLuint sampler);
		extern void (CODEGEN_FUNCPTR *ColorP3ui)(GLenum type, GLuint color);
		extern void (CODEGEN_FUNCPTR *ColorP3uiv)(GLenum type, const GLuint * color);
		extern void (CODEGEN_FUNCPTR *ColorP4ui)(GLenum type, GLuint color);
		extern void (CODEGEN_FUNCPTR *ColorP4uiv)(GLenum type, const GLuint * color);
		extern void (CODEGEN_FUNCPTR *DeleteSamplers)(GLsizei count, const GLuint * samplers);
		extern void (CODEGEN_FUNCPTR *GenSamplers)(GLsizei count, GLuint * samplers);
		extern GLint (CODEGEN_FUNCPTR *GetFragDataIndex)(GLuint program, const GLchar * name);
		extern void (CODEGEN_FUNCPTR *GetQueryObjecti64v)(GLuint id, GLenum pname, GLint64 * params);
		extern void (CODEGEN_FUNCPTR *GetQueryObjectui64v)(GLuint id, GLenum pname, GLuint64 * params);
		extern void (CODEGEN_FUNCPTR *GetSamplerParameterIiv)(GLuint sampler, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetSamplerParameterIuiv)(GLuint sampler, GLenum pname, GLuint * params);
		extern void (CODEGEN_FUNCPTR *GetSamplerParameterfv)(GLuint sampler, GLenum pname, GLfloat * params);
		extern void (CODEGEN_FUNCPTR *GetSamplerParameteriv)(GLuint sampler, GLenum pname, GLint * params);
		extern GLboolean (CODEGEN_FUNCPTR *IsSampler)(GLuint sampler);
		extern void (CODEGEN_FUNCPTR *MultiTexCoordP1ui)(GLenum texture, GLenum type, GLuint coords);
		extern void (CODEGEN_FUNCPTR *MultiTexCoordP1uiv)(GLenum texture, GLenum type, const GLuint * coords);
		extern void (CODEGEN_FUNCPTR *MultiTexCoordP2ui)(GLenum texture, GLenum type, GLuint coords);
		extern void (CODEGEN_FUNCPTR *MultiTexCoordP2uiv)(GLenum texture, GLenum type, const GLuint * coords);
		extern void (CODEGEN_FUNCPTR *MultiTexCoordP3ui)(GLenum texture, GLenum type, GLuint coords);
		extern void (CODEGEN_FUNCPTR *MultiTexCoordP3uiv)(GLenum texture, GLenum type, const GLuint * coords);
		extern void (CODEGEN_FUNCPTR *MultiTexCoordP4ui)(GLenum texture, GLenum type, GLuint coords);
		extern void (CODEGEN_FUNCPTR *MultiTexCoordP4uiv)(GLenum texture, GLenum type, const GLuint * coords);
		extern void (CODEGEN_FUNCPTR *NormalP3ui)(GLenum type, GLuint coords);
		extern void (CODEGEN_FUNCPTR *NormalP3uiv)(GLenum type, const GLuint * coords);
		extern void (CODEGEN_FUNCPTR *QueryCounter)(GLuint id, GLenum target);
		extern void (CODEGEN_FUNCPTR *SamplerParameterIiv)(GLuint sampler, GLenum pname, const GLint * param);
		extern void (CODEGEN_FUNCPTR *SamplerParameterIuiv)(GLuint sampler, GLenum pname, const GLuint * param);
		extern void (CODEGEN_FUNCPTR *SamplerParameterf)(GLuint sampler, GLenum pname, GLfloat param);
		extern void (CODEGEN_FUNCPTR *SamplerParameterfv)(GLuint sampler, GLenum pname, const GLfloat * param);
		extern void (CODEGEN_FUNCPTR *SamplerParameteri)(GLuint sampler, GLenum pname, GLint param);
		extern void (CODEGEN_FUNCPTR *SamplerParameteriv)(GLuint sampler, GLenum pname, const GLint * param);
		extern void (CODEGEN_FUNCPTR *SecondaryColorP3ui)(GLenum type, GLuint color);
		extern void (CODEGEN_FUNCPTR *SecondaryColorP3uiv)(GLenum type, const GLuint * color);
		extern void (CODEGEN_FUNCPTR *TexCoordP1ui)(GLenum type, GLuint coords);
		extern void (CODEGEN_FUNCPTR *TexCoordP1uiv)(GLenum type, const GLuint * coords);
		extern void (CODEGEN_FUNCPTR *TexCoordP2ui)(GLenum type, GLuint coords);
		extern void (CODEGEN_FUNCPTR *TexCoordP2uiv)(GLenum type, const GLuint * coords);
		extern void (CODEGEN_FUNCPTR *TexCoordP3ui)(GLenum type, GLuint coords);
		extern void (CODEGEN_FUNCPTR *TexCoordP3uiv)(GLenum type, const GLuint * coords);
		extern void (CODEGEN_FUNCPTR *TexCoordP4ui)(GLenum type, GLuint coords);
		extern void (CODEGEN_FUNCPTR *TexCoordP4uiv)(GLenum type, const GLuint * coords);
		extern void (CODEGEN_FUNCPTR *VertexAttribDivisor)(GLuint index, GLuint divisor);
		extern void (CODEGEN_FUNCPTR *VertexAttribP1ui)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
		extern void (CODEGEN_FUNCPTR *VertexAttribP1uiv)(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *VertexAttribP2ui)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
		extern void (CODEGEN_FUNCPTR *VertexAttribP2uiv)(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *VertexAttribP3ui)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
		extern void (CODEGEN_FUNCPTR *VertexAttribP3uiv)(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *VertexAttribP4ui)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
		extern void (CODEGEN_FUNCPTR *VertexAttribP4uiv)(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *VertexP2ui)(GLenum type, GLuint value);
		extern void (CODEGEN_FUNCPTR *VertexP2uiv)(GLenum type, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *VertexP3ui)(GLenum type, GLuint value);
		extern void (CODEGEN_FUNCPTR *VertexP3uiv)(GLenum type, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *VertexP4ui)(GLenum type, GLuint value);
		extern void (CODEGEN_FUNCPTR *VertexP4uiv)(GLenum type, const GLuint * value);
		
		extern void (CODEGEN_FUNCPTR *BeginQueryIndexed)(GLenum target, GLuint index, GLuint id);
		extern void (CODEGEN_FUNCPTR *BindTransformFeedback)(GLenum target, GLuint id);
		extern void (CODEGEN_FUNCPTR *BlendEquationSeparatei)(GLuint buf, GLenum modeRGB, GLenum modeAlpha);
		extern void (CODEGEN_FUNCPTR *BlendEquationi)(GLuint buf, GLenum mode);
		extern void (CODEGEN_FUNCPTR *BlendFuncSeparatei)(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
		extern void (CODEGEN_FUNCPTR *BlendFunci)(GLuint buf, GLenum src, GLenum dst);
		extern void (CODEGEN_FUNCPTR *DeleteTransformFeedbacks)(GLsizei n, const GLuint * ids);
		extern void (CODEGEN_FUNCPTR *DrawArraysIndirect)(GLenum mode, const GLvoid * indirect);
		extern void (CODEGEN_FUNCPTR *DrawElementsIndirect)(GLenum mode, GLenum type, const GLvoid * indirect);
		extern void (CODEGEN_FUNCPTR *DrawTransformFeedback)(GLenum mode, GLuint id);
		extern void (CODEGEN_FUNCPTR *DrawTransformFeedbackStream)(GLenum mode, GLuint id, GLuint stream);
		extern void (CODEGEN_FUNCPTR *EndQueryIndexed)(GLenum target, GLuint index);
		extern void (CODEGEN_FUNCPTR *GenTransformFeedbacks)(GLsizei n, GLuint * ids);
		extern void (CODEGEN_FUNCPTR *GetActiveSubroutineName)(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name);
		extern void (CODEGEN_FUNCPTR *GetActiveSubroutineUniformName)(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name);
		extern void (CODEGEN_FUNCPTR *GetActiveSubroutineUniformiv)(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint * values);
		extern void (CODEGEN_FUNCPTR *GetProgramStageiv)(GLuint program, GLenum shadertype, GLenum pname, GLint * values);
		extern void (CODEGEN_FUNCPTR *GetQueryIndexediv)(GLenum target, GLuint index, GLenum pname, GLint * params);
		extern GLuint (CODEGEN_FUNCPTR *GetSubroutineIndex)(GLuint program, GLenum shadertype, const GLchar * name);
		extern GLint (CODEGEN_FUNCPTR *GetSubroutineUniformLocation)(GLuint program, GLenum shadertype, const GLchar * name);
		extern void (CODEGEN_FUNCPTR *GetUniformSubroutineuiv)(GLenum shadertype, GLint location, GLuint * params);
		extern void (CODEGEN_FUNCPTR *GetUniformdv)(GLuint program, GLint location, GLdouble * params);
		extern GLboolean (CODEGEN_FUNCPTR *IsTransformFeedback)(GLuint id);
		extern void (CODEGEN_FUNCPTR *MinSampleShading)(GLfloat value);
		extern void (CODEGEN_FUNCPTR *PatchParameterfv)(GLenum pname, const GLfloat * values);
		extern void (CODEGEN_FUNCPTR *PatchParameteri)(GLenum pname, GLint value);
		extern void (CODEGEN_FUNCPTR *PauseTransformFeedback)();
		extern void (CODEGEN_FUNCPTR *ResumeTransformFeedback)();
		extern void (CODEGEN_FUNCPTR *Uniform1d)(GLint location, GLdouble x);
		extern void (CODEGEN_FUNCPTR *Uniform1dv)(GLint location, GLsizei count, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *Uniform2d)(GLint location, GLdouble x, GLdouble y);
		extern void (CODEGEN_FUNCPTR *Uniform2dv)(GLint location, GLsizei count, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *Uniform3d)(GLint location, GLdouble x, GLdouble y, GLdouble z);
		extern void (CODEGEN_FUNCPTR *Uniform3dv)(GLint location, GLsizei count, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *Uniform4d)(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
		extern void (CODEGEN_FUNCPTR *Uniform4dv)(GLint location, GLsizei count, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix2dv)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix2x3dv)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix2x4dv)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix3dv)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix3x2dv)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix3x4dv)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix4dv)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix4x2dv)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix4x3dv)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *UniformSubroutinesuiv)(GLenum shadertype, GLsizei count, const GLuint * indices);
		
		extern void (CODEGEN_FUNCPTR *ActiveShaderProgram)(GLuint pipeline, GLuint program);
		extern void (CODEGEN_FUNCPTR *BindProgramPipeline)(GLuint pipeline);
		extern void (CODEGEN_FUNCPTR *ClearDepthf)(GLfloat d);
		extern GLuint (CODEGEN_FUNCPTR *CreateShaderProgramv)(GLenum type, GLsizei count, const GLchar *const* strings);
		extern void (CODEGEN_FUNCPTR *DeleteProgramPipelines)(GLsizei n, const GLuint * pipelines);
		extern void (CODEGEN_FUNCPTR *DepthRangeArrayv)(GLuint first, GLsizei count, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *DepthRangeIndexed)(GLuint index, GLdouble n, GLdouble f);
		extern void (CODEGEN_FUNCPTR *DepthRangef)(GLfloat n, GLfloat f);
		extern void (CODEGEN_FUNCPTR *GenProgramPipelines)(GLsizei n, GLuint * pipelines);
		extern void (CODEGEN_FUNCPTR *GetDoublei_v)(GLenum target, GLuint index, GLdouble * data);
		extern void (CODEGEN_FUNCPTR *GetFloati_v)(GLenum target, GLuint index, GLfloat * data);
		extern void (CODEGEN_FUNCPTR *GetProgramBinary)(GLuint program, GLsizei bufSize, GLsizei * length, GLenum * binaryFormat, GLvoid * binary);
		extern void (CODEGEN_FUNCPTR *GetProgramPipelineInfoLog)(GLuint pipeline, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
		extern void (CODEGEN_FUNCPTR *GetProgramPipelineiv)(GLuint pipeline, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetShaderPrecisionFormat)(GLenum shadertype, GLenum precisiontype, GLint * range, GLint * precision);
		extern void (CODEGEN_FUNCPTR *GetVertexAttribLdv)(GLuint index, GLenum pname, GLdouble * params);
		extern GLboolean (CODEGEN_FUNCPTR *IsProgramPipeline)(GLuint pipeline);
		extern void (CODEGEN_FUNCPTR *ProgramBinary)(GLuint program, GLenum binaryFormat, const GLvoid * binary, GLsizei length);
		extern void (CODEGEN_FUNCPTR *ProgramParameteri)(GLuint program, GLenum pname, GLint value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform1d)(GLuint program, GLint location, GLdouble v0);
		extern void (CODEGEN_FUNCPTR *ProgramUniform1dv)(GLuint program, GLint location, GLsizei count, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform1f)(GLuint program, GLint location, GLfloat v0);
		extern void (CODEGEN_FUNCPTR *ProgramUniform1fv)(GLuint program, GLint location, GLsizei count, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform1i)(GLuint program, GLint location, GLint v0);
		extern void (CODEGEN_FUNCPTR *ProgramUniform1iv)(GLuint program, GLint location, GLsizei count, const GLint * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform1ui)(GLuint program, GLint location, GLuint v0);
		extern void (CODEGEN_FUNCPTR *ProgramUniform1uiv)(GLuint program, GLint location, GLsizei count, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform2d)(GLuint program, GLint location, GLdouble v0, GLdouble v1);
		extern void (CODEGEN_FUNCPTR *ProgramUniform2dv)(GLuint program, GLint location, GLsizei count, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform2f)(GLuint program, GLint location, GLfloat v0, GLfloat v1);
		extern void (CODEGEN_FUNCPTR *ProgramUniform2fv)(GLuint program, GLint location, GLsizei count, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform2i)(GLuint program, GLint location, GLint v0, GLint v1);
		extern void (CODEGEN_FUNCPTR *ProgramUniform2iv)(GLuint program, GLint location, GLsizei count, const GLint * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform2ui)(GLuint program, GLint location, GLuint v0, GLuint v1);
		extern void (CODEGEN_FUNCPTR *ProgramUniform2uiv)(GLuint program, GLint location, GLsizei count, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform3d)(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2);
		extern void (CODEGEN_FUNCPTR *ProgramUniform3dv)(GLuint program, GLint location, GLsizei count, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform3f)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
		extern void (CODEGEN_FUNCPTR *ProgramUniform3fv)(GLuint program, GLint location, GLsizei count, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform3i)(GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
		extern void (CODEGEN_FUNCPTR *ProgramUniform3iv)(GLuint program, GLint location, GLsizei count, const GLint * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform3ui)(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
		extern void (CODEGEN_FUNCPTR *ProgramUniform3uiv)(GLuint program, GLint location, GLsizei count, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform4d)(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3);
		extern void (CODEGEN_FUNCPTR *ProgramUniform4dv)(GLuint program, GLint location, GLsizei count, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform4f)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
		extern void (CODEGEN_FUNCPTR *ProgramUniform4fv)(GLuint program, GLint location, GLsizei count, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform4i)(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
		extern void (CODEGEN_FUNCPTR *ProgramUniform4iv)(GLuint program, GLint location, GLsizei count, const GLint * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform4ui)(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
		extern void (CODEGEN_FUNCPTR *ProgramUniform4uiv)(GLuint program, GLint location, GLsizei count, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix2dv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix2fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix2x3dv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix2x3fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix2x4dv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix2x4fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix3dv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix3fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix3x2dv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix3x2fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix3x4dv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix3x4fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix4dv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix4fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix4x2dv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix4x2fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix4x3dv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix4x3fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *ReleaseShaderCompiler)();
		extern void (CODEGEN_FUNCPTR *ScissorArrayv)(GLuint first, GLsizei count, const GLint * v);
		extern void (CODEGEN_FUNCPTR *ScissorIndexed)(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height);
		extern void (CODEGEN_FUNCPTR *ScissorIndexedv)(GLuint index, const GLint * v);
		extern void (CODEGEN_FUNCPTR *ShaderBinary)(GLsizei count, const GLuint * shaders, GLenum binaryformat, const GLvoid * binary, GLsizei length);
		extern void (CODEGEN_FUNCPTR *UseProgramStages)(GLuint pipeline, GLbitfield stages, GLuint program);
		extern void (CODEGEN_FUNCPTR *ValidateProgramPipeline)(GLuint pipeline);
		extern void (CODEGEN_FUNCPTR *VertexAttribL1d)(GLuint index, GLdouble x);
		extern void (CODEGEN_FUNCPTR *VertexAttribL1dv)(GLuint index, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribL2d)(GLuint index, GLdouble x, GLdouble y);
		extern void (CODEGEN_FUNCPTR *VertexAttribL2dv)(GLuint index, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribL3d)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
		extern void (CODEGEN_FUNCPTR *VertexAttribL3dv)(GLuint index, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribL4d)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
		extern void (CODEGEN_FUNCPTR *VertexAttribL4dv)(GLuint index, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribLPointer)(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer);
		extern void (CODEGEN_FUNCPTR *ViewportArrayv)(GLuint first, GLsizei count, const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *ViewportIndexedf)(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
		extern void (CODEGEN_FUNCPTR *ViewportIndexedfv)(GLuint index, const GLfloat * v);
		
	} //namespace _detail
	
	inline void CompressedTexImage1DARB(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid * data){_detail::CompressedTexImage1DARB(target, level, internalformat, width, border, imageSize, data);}
	inline void CompressedTexImage2DARB(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid * data){_detail::CompressedTexImage2DARB(target, level, internalformat, width, height, border, imageSize, data);}
	inline void CompressedTexImage3DARB(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid * data){_detail::CompressedTexImage3DARB(target, level, internalformat, width, height, depth, border, imageSize, data);}
	inline void CompressedTexSubImage1DARB(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid * data){_detail::CompressedTexSubImage1DARB(target, level, xoffset, width, format, imageSize, data);}
	inline void CompressedTexSubImage2DARB(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid * data){_detail::CompressedTexSubImage2DARB(target, level, xoffset, yoffset, width, height, format, imageSize, data);}
	inline void CompressedTexSubImage3DARB(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid * data){_detail::CompressedTexSubImage3DARB(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);}
	inline void GetCompressedTexImageARB(GLenum target, GLint level, GLvoid * img){_detail::GetCompressedTexImageARB(target, level, img);}
	
	
	inline void GetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint * params){_detail::GetProgramInterfaceiv(program, programInterface, pname, params);}
	inline GLuint GetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar * name){return _detail::GetProgramResourceIndex(program, programInterface, name);}
	inline GLint GetProgramResourceLocation(GLuint program, GLenum programInterface, const GLchar * name){return _detail::GetProgramResourceLocation(program, programInterface, name);}
	inline GLint GetProgramResourceLocationIndex(GLuint program, GLenum programInterface, const GLchar * name){return _detail::GetProgramResourceLocationIndex(program, programInterface, name);}
	inline void GetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name){_detail::GetProgramResourceName(program, programInterface, index, bufSize, length, name);}
	inline void GetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum * props, GLsizei bufSize, GLsizei * length, GLint * params){_detail::GetProgramResourceiv(program, programInterface, index, propCount, props, bufSize, length, params);}
	
	inline void BlendFunc(GLenum sfactor, GLenum dfactor){_detail::BlendFunc(sfactor, dfactor);}
	inline void Clear(GLbitfield mask){_detail::Clear(mask);}
	inline void ClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha){_detail::ClearColor(red, green, blue, alpha);}
	inline void ClearDepth(GLdouble depth){_detail::ClearDepth(depth);}
	inline void ClearStencil(GLint s){_detail::ClearStencil(s);}
	inline void ColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha){_detail::ColorMask(red, green, blue, alpha);}
	inline void CullFace(GLenum mode){_detail::CullFace(mode);}
	inline void DepthFunc(GLenum func){_detail::DepthFunc(func);}
	inline void DepthMask(GLboolean flag){_detail::DepthMask(flag);}
	inline void DepthRange(GLdouble ren_near, GLdouble ren_far){_detail::DepthRange(ren_near, ren_far);}
	inline void Disable(GLenum cap){_detail::Disable(cap);}
	inline void DrawBuffer(GLenum mode){_detail::DrawBuffer(mode);}
	inline void Enable(GLenum cap){_detail::Enable(cap);}
	inline void Finish(){_detail::Finish();}
	inline void Flush(){_detail::Flush();}
	inline void FrontFace(GLenum mode){_detail::FrontFace(mode);}
	inline void GetBooleanv(GLenum pname, GLboolean * params){_detail::GetBooleanv(pname, params);}
	inline void GetDoublev(GLenum pname, GLdouble * params){_detail::GetDoublev(pname, params);}
	inline GLenum GetError(){return _detail::GetError();}
	inline void GetFloatv(GLenum pname, GLfloat * params){_detail::GetFloatv(pname, params);}
	inline void GetIntegerv(GLenum pname, GLint * params){_detail::GetIntegerv(pname, params);}
	inline const GLubyte * GetString(GLenum name){return _detail::GetString(name);}
	inline void GetTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLvoid * pixels){_detail::GetTexImage(target, level, format, type, pixels);}
	inline void GetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat * params){_detail::GetTexLevelParameterfv(target, level, pname, params);}
	inline void GetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint * params){_detail::GetTexLevelParameteriv(target, level, pname, params);}
	inline void GetTexParameterfv(GLenum target, GLenum pname, GLfloat * params){_detail::GetTexParameterfv(target, pname, params);}
	inline void GetTexParameteriv(GLenum target, GLenum pname, GLint * params){_detail::GetTexParameteriv(target, pname, params);}
	inline void Hint(GLenum target, GLenum mode){_detail::Hint(target, mode);}
	inline GLboolean IsEnabled(GLenum cap){return _detail::IsEnabled(cap);}
	inline void LineWidth(GLfloat width){_detail::LineWidth(width);}
	inline void LogicOp(GLenum opcode){_detail::LogicOp(opcode);}
	inline void PixelStoref(GLenum pname, GLfloat param){_detail::PixelStoref(pname, param);}
	inline void PixelStorei(GLenum pname, GLint param){_detail::PixelStorei(pname, param);}
	inline void PointSize(GLfloat size){_detail::PointSize(size);}
	inline void PolygonMode(GLenum face, GLenum mode){_detail::PolygonMode(face, mode);}
	inline void ReadBuffer(GLenum mode){_detail::ReadBuffer(mode);}
	inline void ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid * pixels){_detail::ReadPixels(x, y, width, height, format, type, pixels);}
	inline void Scissor(GLint x, GLint y, GLsizei width, GLsizei height){_detail::Scissor(x, y, width, height);}
	inline void StencilFunc(GLenum func, GLint ref, GLuint mask){_detail::StencilFunc(func, ref, mask);}
	inline void StencilMask(GLuint mask){_detail::StencilMask(mask);}
	inline void StencilOp(GLenum fail, GLenum zfail, GLenum zpass){_detail::StencilOp(fail, zfail, zpass);}
	inline void TexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid * pixels){_detail::TexImage1D(target, level, internalformat, width, border, format, type, pixels);}
	inline void TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid * pixels){_detail::TexImage2D(target, level, internalformat, width, height, border, format, type, pixels);}
	inline void TexParameterf(GLenum target, GLenum pname, GLfloat param){_detail::TexParameterf(target, pname, param);}
	inline void TexParameterfv(GLenum target, GLenum pname, const GLfloat * params){_detail::TexParameterfv(target, pname, params);}
	inline void TexParameteri(GLenum target, GLenum pname, GLint param){_detail::TexParameteri(target, pname, param);}
	inline void TexParameteriv(GLenum target, GLenum pname, const GLint * params){_detail::TexParameteriv(target, pname, params);}
	inline void Viewport(GLint x, GLint y, GLsizei width, GLsizei height){_detail::Viewport(x, y, width, height);}
	
	inline void BindTexture(GLenum target, GLuint texture){_detail::BindTexture(target, texture);}
	inline void CopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border){_detail::CopyTexImage1D(target, level, internalformat, x, y, width, border);}
	inline void CopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border){_detail::CopyTexImage2D(target, level, internalformat, x, y, width, height, border);}
	inline void CopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width){_detail::CopyTexSubImage1D(target, level, xoffset, x, y, width);}
	inline void CopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height){_detail::CopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);}
	inline void DeleteTextures(GLsizei n, const GLuint * textures){_detail::DeleteTextures(n, textures);}
	inline void DrawArrays(GLenum mode, GLint first, GLsizei count){_detail::DrawArrays(mode, first, count);}
	inline void DrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices){_detail::DrawElements(mode, count, type, indices);}
	inline void GenTextures(GLsizei n, GLuint * textures){_detail::GenTextures(n, textures);}
	inline GLboolean IsTexture(GLuint texture){return _detail::IsTexture(texture);}
	inline void PolygonOffset(GLfloat factor, GLfloat units){_detail::PolygonOffset(factor, units);}
	inline void TexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid * pixels){_detail::TexSubImage1D(target, level, xoffset, width, format, type, pixels);}
	inline void TexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels){_detail::TexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);}
	
	inline void BlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha){_detail::BlendColor(red, green, blue, alpha);}
	inline void BlendEquation(GLenum mode){_detail::BlendEquation(mode);}
	inline void CopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height){_detail::CopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);}
	inline void DrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid * indices){_detail::DrawRangeElements(mode, start, end, count, type, indices);}
	inline void TexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid * pixels){_detail::TexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);}
	inline void TexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid * pixels){_detail::TexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);}
	
	inline void ActiveTexture(GLenum texture){_detail::ActiveTexture(texture);}
	inline void CompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid * data){_detail::CompressedTexImage1D(target, level, internalformat, width, border, imageSize, data);}
	inline void CompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid * data){_detail::CompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);}
	inline void CompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid * data){_detail::CompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);}
	inline void CompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid * data){_detail::CompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data);}
	inline void CompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid * data){_detail::CompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);}
	inline void CompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid * data){_detail::CompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);}
	inline void GetCompressedTexImage(GLenum target, GLint level, GLvoid * img){_detail::GetCompressedTexImage(target, level, img);}
	inline void SampleCoverage(GLfloat value, GLboolean invert){_detail::SampleCoverage(value, invert);}
	
	inline void BlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha){_detail::BlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);}
	inline void MultiDrawArrays(GLenum mode, const GLint * first, const GLsizei * count, GLsizei drawcount){_detail::MultiDrawArrays(mode, first, count, drawcount);}
	inline void MultiDrawElements(GLenum mode, const GLsizei * count, GLenum type, const GLvoid *const* indices, GLsizei drawcount){_detail::MultiDrawElements(mode, count, type, indices, drawcount);}
	inline void PointParameterf(GLenum pname, GLfloat param){_detail::PointParameterf(pname, param);}
	inline void PointParameterfv(GLenum pname, const GLfloat * params){_detail::PointParameterfv(pname, params);}
	inline void PointParameteri(GLenum pname, GLint param){_detail::PointParameteri(pname, param);}
	inline void PointParameteriv(GLenum pname, const GLint * params){_detail::PointParameteriv(pname, params);}
	
	inline void BeginQuery(GLenum target, GLuint id){_detail::BeginQuery(target, id);}
	inline void BindBuffer(GLenum target, GLuint buffer){_detail::BindBuffer(target, buffer);}
	inline void BufferData(GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage){_detail::BufferData(target, size, data, usage);}
	inline void BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid * data){_detail::BufferSubData(target, offset, size, data);}
	inline void DeleteBuffers(GLsizei n, const GLuint * buffers){_detail::DeleteBuffers(n, buffers);}
	inline void DeleteQueries(GLsizei n, const GLuint * ids){_detail::DeleteQueries(n, ids);}
	inline void EndQuery(GLenum target){_detail::EndQuery(target);}
	inline void GenBuffers(GLsizei n, GLuint * buffers){_detail::GenBuffers(n, buffers);}
	inline void GenQueries(GLsizei n, GLuint * ids){_detail::GenQueries(n, ids);}
	inline void GetBufferParameteriv(GLenum target, GLenum pname, GLint * params){_detail::GetBufferParameteriv(target, pname, params);}
	inline void GetBufferPointerv(GLenum target, GLenum pname, GLvoid ** params){_detail::GetBufferPointerv(target, pname, params);}
	inline void GetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, GLvoid * data){_detail::GetBufferSubData(target, offset, size, data);}
	inline void GetQueryObjectiv(GLuint id, GLenum pname, GLint * params){_detail::GetQueryObjectiv(id, pname, params);}
	inline void GetQueryObjectuiv(GLuint id, GLenum pname, GLuint * params){_detail::GetQueryObjectuiv(id, pname, params);}
	inline void GetQueryiv(GLenum target, GLenum pname, GLint * params){_detail::GetQueryiv(target, pname, params);}
	inline GLboolean IsBuffer(GLuint buffer){return _detail::IsBuffer(buffer);}
	inline GLboolean IsQuery(GLuint id){return _detail::IsQuery(id);}
	inline void * MapBuffer(GLenum target, GLenum access){return _detail::MapBuffer(target, access);}
	inline GLboolean UnmapBuffer(GLenum target){return _detail::UnmapBuffer(target);}
	
	inline void AttachShader(GLuint program, GLuint shader){_detail::AttachShader(program, shader);}
	inline void BindAttribLocation(GLuint program, GLuint index, const GLchar * name){_detail::BindAttribLocation(program, index, name);}
	inline void BlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha){_detail::BlendEquationSeparate(modeRGB, modeAlpha);}
	inline void CompileShader(GLuint shader){_detail::CompileShader(shader);}
	inline GLuint CreateProgram(){return _detail::CreateProgram();}
	inline GLuint CreateShader(GLenum type){return _detail::CreateShader(type);}
	inline void DeleteProgram(GLuint program){_detail::DeleteProgram(program);}
	inline void DeleteShader(GLuint shader){_detail::DeleteShader(shader);}
	inline void DetachShader(GLuint program, GLuint shader){_detail::DetachShader(program, shader);}
	inline void DisableVertexAttribArray(GLuint index){_detail::DisableVertexAttribArray(index);}
	inline void DrawBuffers(GLsizei n, const GLenum * bufs){_detail::DrawBuffers(n, bufs);}
	inline void EnableVertexAttribArray(GLuint index){_detail::EnableVertexAttribArray(index);}
	inline void GetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name){_detail::GetActiveAttrib(program, index, bufSize, length, size, type, name);}
	inline void GetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name){_detail::GetActiveUniform(program, index, bufSize, length, size, type, name);}
	inline void GetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders){_detail::GetAttachedShaders(program, maxCount, count, shaders);}
	inline GLint GetAttribLocation(GLuint program, const GLchar * name){return _detail::GetAttribLocation(program, name);}
	inline void GetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog){_detail::GetProgramInfoLog(program, bufSize, length, infoLog);}
	inline void GetProgramiv(GLuint program, GLenum pname, GLint * params){_detail::GetProgramiv(program, pname, params);}
	inline void GetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog){_detail::GetShaderInfoLog(shader, bufSize, length, infoLog);}
	inline void GetShaderSource(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source){_detail::GetShaderSource(shader, bufSize, length, source);}
	inline void GetShaderiv(GLuint shader, GLenum pname, GLint * params){_detail::GetShaderiv(shader, pname, params);}
	inline GLint GetUniformLocation(GLuint program, const GLchar * name){return _detail::GetUniformLocation(program, name);}
	inline void GetUniformfv(GLuint program, GLint location, GLfloat * params){_detail::GetUniformfv(program, location, params);}
	inline void GetUniformiv(GLuint program, GLint location, GLint * params){_detail::GetUniformiv(program, location, params);}
	inline void GetVertexAttribPointerv(GLuint index, GLenum pname, GLvoid ** pointer){_detail::GetVertexAttribPointerv(index, pname, pointer);}
	inline void GetVertexAttribdv(GLuint index, GLenum pname, GLdouble * params){_detail::GetVertexAttribdv(index, pname, params);}
	inline void GetVertexAttribfv(GLuint index, GLenum pname, GLfloat * params){_detail::GetVertexAttribfv(index, pname, params);}
	inline void GetVertexAttribiv(GLuint index, GLenum pname, GLint * params){_detail::GetVertexAttribiv(index, pname, params);}
	inline GLboolean IsProgram(GLuint program){return _detail::IsProgram(program);}
	inline GLboolean IsShader(GLuint shader){return _detail::IsShader(shader);}
	inline void LinkProgram(GLuint program){_detail::LinkProgram(program);}
	inline void ShaderSource(GLuint shader, GLsizei count, const GLchar *const* string, const GLint * length){_detail::ShaderSource(shader, count, string, length);}
	inline void StencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask){_detail::StencilFuncSeparate(face, func, ref, mask);}
	inline void StencilMaskSeparate(GLenum face, GLuint mask){_detail::StencilMaskSeparate(face, mask);}
	inline void StencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass){_detail::StencilOpSeparate(face, sfail, dpfail, dppass);}
	inline void Uniform1f(GLint location, GLfloat v0){_detail::Uniform1f(location, v0);}
	inline void Uniform1fv(GLint location, GLsizei count, const GLfloat * value){_detail::Uniform1fv(location, count, value);}
	inline void Uniform1i(GLint location, GLint v0){_detail::Uniform1i(location, v0);}
	inline void Uniform1iv(GLint location, GLsizei count, const GLint * value){_detail::Uniform1iv(location, count, value);}
	inline void Uniform2f(GLint location, GLfloat v0, GLfloat v1){_detail::Uniform2f(location, v0, v1);}
	inline void Uniform2fv(GLint location, GLsizei count, const GLfloat * value){_detail::Uniform2fv(location, count, value);}
	inline void Uniform2i(GLint location, GLint v0, GLint v1){_detail::Uniform2i(location, v0, v1);}
	inline void Uniform2iv(GLint location, GLsizei count, const GLint * value){_detail::Uniform2iv(location, count, value);}
	inline void Uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2){_detail::Uniform3f(location, v0, v1, v2);}
	inline void Uniform3fv(GLint location, GLsizei count, const GLfloat * value){_detail::Uniform3fv(location, count, value);}
	inline void Uniform3i(GLint location, GLint v0, GLint v1, GLint v2){_detail::Uniform3i(location, v0, v1, v2);}
	inline void Uniform3iv(GLint location, GLsizei count, const GLint * value){_detail::Uniform3iv(location, count, value);}
	inline void Uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3){_detail::Uniform4f(location, v0, v1, v2, v3);}
	inline void Uniform4fv(GLint location, GLsizei count, const GLfloat * value){_detail::Uniform4fv(location, count, value);}
	inline void Uniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3){_detail::Uniform4i(location, v0, v1, v2, v3);}
	inline void Uniform4iv(GLint location, GLsizei count, const GLint * value){_detail::Uniform4iv(location, count, value);}
	inline void UniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::UniformMatrix2fv(location, count, transpose, value);}
	inline void UniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::UniformMatrix3fv(location, count, transpose, value);}
	inline void UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::UniformMatrix4fv(location, count, transpose, value);}
	inline void UseProgram(GLuint program){_detail::UseProgram(program);}
	inline void ValidateProgram(GLuint program){_detail::ValidateProgram(program);}
	inline void VertexAttrib1d(GLuint index, GLdouble x){_detail::VertexAttrib1d(index, x);}
	inline void VertexAttrib1dv(GLuint index, const GLdouble * v){_detail::VertexAttrib1dv(index, v);}
	inline void VertexAttrib1f(GLuint index, GLfloat x){_detail::VertexAttrib1f(index, x);}
	inline void VertexAttrib1fv(GLuint index, const GLfloat * v){_detail::VertexAttrib1fv(index, v);}
	inline void VertexAttrib1s(GLuint index, GLshort x){_detail::VertexAttrib1s(index, x);}
	inline void VertexAttrib1sv(GLuint index, const GLshort * v){_detail::VertexAttrib1sv(index, v);}
	inline void VertexAttrib2d(GLuint index, GLdouble x, GLdouble y){_detail::VertexAttrib2d(index, x, y);}
	inline void VertexAttrib2dv(GLuint index, const GLdouble * v){_detail::VertexAttrib2dv(index, v);}
	inline void VertexAttrib2f(GLuint index, GLfloat x, GLfloat y){_detail::VertexAttrib2f(index, x, y);}
	inline void VertexAttrib2fv(GLuint index, const GLfloat * v){_detail::VertexAttrib2fv(index, v);}
	inline void VertexAttrib2s(GLuint index, GLshort x, GLshort y){_detail::VertexAttrib2s(index, x, y);}
	inline void VertexAttrib2sv(GLuint index, const GLshort * v){_detail::VertexAttrib2sv(index, v);}
	inline void VertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z){_detail::VertexAttrib3d(index, x, y, z);}
	inline void VertexAttrib3dv(GLuint index, const GLdouble * v){_detail::VertexAttrib3dv(index, v);}
	inline void VertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z){_detail::VertexAttrib3f(index, x, y, z);}
	inline void VertexAttrib3fv(GLuint index, const GLfloat * v){_detail::VertexAttrib3fv(index, v);}
	inline void VertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z){_detail::VertexAttrib3s(index, x, y, z);}
	inline void VertexAttrib3sv(GLuint index, const GLshort * v){_detail::VertexAttrib3sv(index, v);}
	inline void VertexAttrib4Nbv(GLuint index, const GLbyte * v){_detail::VertexAttrib4Nbv(index, v);}
	inline void VertexAttrib4Niv(GLuint index, const GLint * v){_detail::VertexAttrib4Niv(index, v);}
	inline void VertexAttrib4Nsv(GLuint index, const GLshort * v){_detail::VertexAttrib4Nsv(index, v);}
	inline void VertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w){_detail::VertexAttrib4Nub(index, x, y, z, w);}
	inline void VertexAttrib4Nubv(GLuint index, const GLubyte * v){_detail::VertexAttrib4Nubv(index, v);}
	inline void VertexAttrib4Nuiv(GLuint index, const GLuint * v){_detail::VertexAttrib4Nuiv(index, v);}
	inline void VertexAttrib4Nusv(GLuint index, const GLushort * v){_detail::VertexAttrib4Nusv(index, v);}
	inline void VertexAttrib4bv(GLuint index, const GLbyte * v){_detail::VertexAttrib4bv(index, v);}
	inline void VertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w){_detail::VertexAttrib4d(index, x, y, z, w);}
	inline void VertexAttrib4dv(GLuint index, const GLdouble * v){_detail::VertexAttrib4dv(index, v);}
	inline void VertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w){_detail::VertexAttrib4f(index, x, y, z, w);}
	inline void VertexAttrib4fv(GLuint index, const GLfloat * v){_detail::VertexAttrib4fv(index, v);}
	inline void VertexAttrib4iv(GLuint index, const GLint * v){_detail::VertexAttrib4iv(index, v);}
	inline void VertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w){_detail::VertexAttrib4s(index, x, y, z, w);}
	inline void VertexAttrib4sv(GLuint index, const GLshort * v){_detail::VertexAttrib4sv(index, v);}
	inline void VertexAttrib4ubv(GLuint index, const GLubyte * v){_detail::VertexAttrib4ubv(index, v);}
	inline void VertexAttrib4uiv(GLuint index, const GLuint * v){_detail::VertexAttrib4uiv(index, v);}
	inline void VertexAttrib4usv(GLuint index, const GLushort * v){_detail::VertexAttrib4usv(index, v);}
	inline void VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer){_detail::VertexAttribPointer(index, size, type, normalized, stride, pointer);}
	
	inline void UniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::UniformMatrix2x3fv(location, count, transpose, value);}
	inline void UniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::UniformMatrix2x4fv(location, count, transpose, value);}
	inline void UniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::UniformMatrix3x2fv(location, count, transpose, value);}
	inline void UniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::UniformMatrix3x4fv(location, count, transpose, value);}
	inline void UniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::UniformMatrix4x2fv(location, count, transpose, value);}
	inline void UniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::UniformMatrix4x3fv(location, count, transpose, value);}
	
	inline void BeginConditionalRender(GLuint id, GLenum mode){_detail::BeginConditionalRender(id, mode);}
	inline void BeginTransformFeedback(GLenum primitiveMode){_detail::BeginTransformFeedback(primitiveMode);}
	inline void BindBufferBase(GLenum target, GLuint index, GLuint buffer){_detail::BindBufferBase(target, index, buffer);}
	inline void BindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size){_detail::BindBufferRange(target, index, buffer, offset, size);}
	inline void BindFragDataLocation(GLuint program, GLuint color, const GLchar * name){_detail::BindFragDataLocation(program, color, name);}
	inline void BindFramebuffer(GLenum target, GLuint framebuffer){_detail::BindFramebuffer(target, framebuffer);}
	inline void BindRenderbuffer(GLenum target, GLuint renderbuffer){_detail::BindRenderbuffer(target, renderbuffer);}
	inline void BindVertexArray(GLuint ren_array){_detail::BindVertexArray(ren_array);}
	inline void BlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter){_detail::BlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);}
	inline GLenum CheckFramebufferStatus(GLenum target){return _detail::CheckFramebufferStatus(target);}
	inline void ClampColor(GLenum target, GLenum clamp){_detail::ClampColor(target, clamp);}
	inline void ClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil){_detail::ClearBufferfi(buffer, drawbuffer, depth, stencil);}
	inline void ClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat * value){_detail::ClearBufferfv(buffer, drawbuffer, value);}
	inline void ClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint * value){_detail::ClearBufferiv(buffer, drawbuffer, value);}
	inline void ClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint * value){_detail::ClearBufferuiv(buffer, drawbuffer, value);}
	inline void ColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a){_detail::ColorMaski(index, r, g, b, a);}
	inline void DeleteFramebuffers(GLsizei n, const GLuint * framebuffers){_detail::DeleteFramebuffers(n, framebuffers);}
	inline void DeleteRenderbuffers(GLsizei n, const GLuint * renderbuffers){_detail::DeleteRenderbuffers(n, renderbuffers);}
	inline void DeleteVertexArrays(GLsizei n, const GLuint * arrays){_detail::DeleteVertexArrays(n, arrays);}
	inline void Disablei(GLenum target, GLuint index){_detail::Disablei(target, index);}
	inline void Enablei(GLenum target, GLuint index){_detail::Enablei(target, index);}
	inline void EndConditionalRender(){_detail::EndConditionalRender();}
	inline void EndTransformFeedback(){_detail::EndTransformFeedback();}
	inline void FlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length){_detail::FlushMappedBufferRange(target, offset, length);}
	inline void FramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer){_detail::FramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);}
	inline void FramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level){_detail::FramebufferTexture1D(target, attachment, textarget, texture, level);}
	inline void FramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level){_detail::FramebufferTexture2D(target, attachment, textarget, texture, level);}
	inline void FramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset){_detail::FramebufferTexture3D(target, attachment, textarget, texture, level, zoffset);}
	inline void FramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer){_detail::FramebufferTextureLayer(target, attachment, texture, level, layer);}
	inline void GenFramebuffers(GLsizei n, GLuint * framebuffers){_detail::GenFramebuffers(n, framebuffers);}
	inline void GenRenderbuffers(GLsizei n, GLuint * renderbuffers){_detail::GenRenderbuffers(n, renderbuffers);}
	inline void GenVertexArrays(GLsizei n, GLuint * arrays){_detail::GenVertexArrays(n, arrays);}
	inline void GenerateMipmap(GLenum target){_detail::GenerateMipmap(target);}
	inline void GetBooleani_v(GLenum target, GLuint index, GLboolean * data){_detail::GetBooleani_v(target, index, data);}
	inline GLint GetFragDataLocation(GLuint program, const GLchar * name){return _detail::GetFragDataLocation(program, name);}
	inline void GetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint * params){_detail::GetFramebufferAttachmentParameteriv(target, attachment, pname, params);}
	inline void GetIntegeri_v(GLenum target, GLuint index, GLint * data){_detail::GetIntegeri_v(target, index, data);}
	inline void GetRenderbufferParameteriv(GLenum target, GLenum pname, GLint * params){_detail::GetRenderbufferParameteriv(target, pname, params);}
	inline const GLubyte * GetStringi(GLenum name, GLuint index){return _detail::GetStringi(name, index);}
	inline void GetTexParameterIiv(GLenum target, GLenum pname, GLint * params){_detail::GetTexParameterIiv(target, pname, params);}
	inline void GetTexParameterIuiv(GLenum target, GLenum pname, GLuint * params){_detail::GetTexParameterIuiv(target, pname, params);}
	inline void GetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name){_detail::GetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);}
	inline void GetUniformuiv(GLuint program, GLint location, GLuint * params){_detail::GetUniformuiv(program, location, params);}
	inline void GetVertexAttribIiv(GLuint index, GLenum pname, GLint * params){_detail::GetVertexAttribIiv(index, pname, params);}
	inline void GetVertexAttribIuiv(GLuint index, GLenum pname, GLuint * params){_detail::GetVertexAttribIuiv(index, pname, params);}
	inline GLboolean IsEnabledi(GLenum target, GLuint index){return _detail::IsEnabledi(target, index);}
	inline GLboolean IsFramebuffer(GLuint framebuffer){return _detail::IsFramebuffer(framebuffer);}
	inline GLboolean IsRenderbuffer(GLuint renderbuffer){return _detail::IsRenderbuffer(renderbuffer);}
	inline GLboolean IsVertexArray(GLuint ren_array){return _detail::IsVertexArray(ren_array);}
	inline void * MapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access){return _detail::MapBufferRange(target, offset, length, access);}
	inline void RenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height){_detail::RenderbufferStorage(target, internalformat, width, height);}
	inline void RenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height){_detail::RenderbufferStorageMultisample(target, samples, internalformat, width, height);}
	inline void TexParameterIiv(GLenum target, GLenum pname, const GLint * params){_detail::TexParameterIiv(target, pname, params);}
	inline void TexParameterIuiv(GLenum target, GLenum pname, const GLuint * params){_detail::TexParameterIuiv(target, pname, params);}
	inline void TransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar *const* varyings, GLenum bufferMode){_detail::TransformFeedbackVaryings(program, count, varyings, bufferMode);}
	inline void Uniform1ui(GLint location, GLuint v0){_detail::Uniform1ui(location, v0);}
	inline void Uniform1uiv(GLint location, GLsizei count, const GLuint * value){_detail::Uniform1uiv(location, count, value);}
	inline void Uniform2ui(GLint location, GLuint v0, GLuint v1){_detail::Uniform2ui(location, v0, v1);}
	inline void Uniform2uiv(GLint location, GLsizei count, const GLuint * value){_detail::Uniform2uiv(location, count, value);}
	inline void Uniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2){_detail::Uniform3ui(location, v0, v1, v2);}
	inline void Uniform3uiv(GLint location, GLsizei count, const GLuint * value){_detail::Uniform3uiv(location, count, value);}
	inline void Uniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3){_detail::Uniform4ui(location, v0, v1, v2, v3);}
	inline void Uniform4uiv(GLint location, GLsizei count, const GLuint * value){_detail::Uniform4uiv(location, count, value);}
	inline void VertexAttribI1i(GLuint index, GLint x){_detail::VertexAttribI1i(index, x);}
	inline void VertexAttribI1iv(GLuint index, const GLint * v){_detail::VertexAttribI1iv(index, v);}
	inline void VertexAttribI1ui(GLuint index, GLuint x){_detail::VertexAttribI1ui(index, x);}
	inline void VertexAttribI1uiv(GLuint index, const GLuint * v){_detail::VertexAttribI1uiv(index, v);}
	inline void VertexAttribI2i(GLuint index, GLint x, GLint y){_detail::VertexAttribI2i(index, x, y);}
	inline void VertexAttribI2iv(GLuint index, const GLint * v){_detail::VertexAttribI2iv(index, v);}
	inline void VertexAttribI2ui(GLuint index, GLuint x, GLuint y){_detail::VertexAttribI2ui(index, x, y);}
	inline void VertexAttribI2uiv(GLuint index, const GLuint * v){_detail::VertexAttribI2uiv(index, v);}
	inline void VertexAttribI3i(GLuint index, GLint x, GLint y, GLint z){_detail::VertexAttribI3i(index, x, y, z);}
	inline void VertexAttribI3iv(GLuint index, const GLint * v){_detail::VertexAttribI3iv(index, v);}
	inline void VertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z){_detail::VertexAttribI3ui(index, x, y, z);}
	inline void VertexAttribI3uiv(GLuint index, const GLuint * v){_detail::VertexAttribI3uiv(index, v);}
	inline void VertexAttribI4bv(GLuint index, const GLbyte * v){_detail::VertexAttribI4bv(index, v);}
	inline void VertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w){_detail::VertexAttribI4i(index, x, y, z, w);}
	inline void VertexAttribI4iv(GLuint index, const GLint * v){_detail::VertexAttribI4iv(index, v);}
	inline void VertexAttribI4sv(GLuint index, const GLshort * v){_detail::VertexAttribI4sv(index, v);}
	inline void VertexAttribI4ubv(GLuint index, const GLubyte * v){_detail::VertexAttribI4ubv(index, v);}
	inline void VertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w){_detail::VertexAttribI4ui(index, x, y, z, w);}
	inline void VertexAttribI4uiv(GLuint index, const GLuint * v){_detail::VertexAttribI4uiv(index, v);}
	inline void VertexAttribI4usv(GLuint index, const GLushort * v){_detail::VertexAttribI4usv(index, v);}
	inline void VertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer){_detail::VertexAttribIPointer(index, size, type, stride, pointer);}
	
	inline void CopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size){_detail::CopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);}
	inline void DrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount){_detail::DrawArraysInstanced(mode, first, count, instancecount);}
	inline void DrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices, GLsizei instancecount){_detail::DrawElementsInstanced(mode, count, type, indices, instancecount);}
	inline void GetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName){_detail::GetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName);}
	inline void GetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint * params){_detail::GetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);}
	inline void GetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformName){_detail::GetActiveUniformName(program, uniformIndex, bufSize, length, uniformName);}
	inline void GetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint * uniformIndices, GLenum pname, GLint * params){_detail::GetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params);}
	inline GLuint GetUniformBlockIndex(GLuint program, const GLchar * uniformBlockName){return _detail::GetUniformBlockIndex(program, uniformBlockName);}
	inline void GetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar *const* uniformNames, GLuint * uniformIndices){_detail::GetUniformIndices(program, uniformCount, uniformNames, uniformIndices);}
	inline void PrimitiveRestartIndex(GLuint index){_detail::PrimitiveRestartIndex(index);}
	inline void TexBuffer(GLenum target, GLenum internalformat, GLuint buffer){_detail::TexBuffer(target, internalformat, buffer);}
	inline void UniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding){_detail::UniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);}
	
	inline GLenum ClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout){return _detail::ClientWaitSync(sync, flags, timeout);}
	inline void DeleteSync(GLsync sync){_detail::DeleteSync(sync);}
	inline void DrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices, GLint basevertex){_detail::DrawElementsBaseVertex(mode, count, type, indices, basevertex);}
	inline void DrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices, GLsizei instancecount, GLint basevertex){_detail::DrawElementsInstancedBaseVertex(mode, count, type, indices, instancecount, basevertex);}
	inline void DrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid * indices, GLint basevertex){_detail::DrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);}
	inline GLsync FenceSync(GLenum condition, GLbitfield flags){return _detail::FenceSync(condition, flags);}
	inline void FramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level){_detail::FramebufferTexture(target, attachment, texture, level);}
	inline void GetBufferParameteri64v(GLenum target, GLenum pname, GLint64 * params){_detail::GetBufferParameteri64v(target, pname, params);}
	inline void GetInteger64i_v(GLenum target, GLuint index, GLint64 * data){_detail::GetInteger64i_v(target, index, data);}
	inline void GetInteger64v(GLenum pname, GLint64 * params){_detail::GetInteger64v(pname, params);}
	inline void GetMultisamplefv(GLenum pname, GLuint index, GLfloat * val){_detail::GetMultisamplefv(pname, index, val);}
	inline void GetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei * length, GLint * values){_detail::GetSynciv(sync, pname, bufSize, length, values);}
	inline GLboolean IsSync(GLsync sync){return _detail::IsSync(sync);}
	inline void MultiDrawElementsBaseVertex(GLenum mode, const GLsizei * count, GLenum type, const GLvoid *const* indices, GLsizei drawcount, const GLint * basevertex){_detail::MultiDrawElementsBaseVertex(mode, count, type, indices, drawcount, basevertex);}
	inline void ProvokingVertex(GLenum mode){_detail::ProvokingVertex(mode);}
	inline void SampleMaski(GLuint index, GLbitfield mask){_detail::SampleMaski(index, mask);}
	inline void TexImage2DMultisample(GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations){_detail::TexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);}
	inline void TexImage3DMultisample(GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations){_detail::TexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);}
	inline void WaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout){_detail::WaitSync(sync, flags, timeout);}
	
	inline void BindFragDataLocationIndexed(GLuint program, GLuint colorNumber, GLuint index, const GLchar * name){_detail::BindFragDataLocationIndexed(program, colorNumber, index, name);}
	inline void BindSampler(GLuint unit, GLuint sampler){_detail::BindSampler(unit, sampler);}
	inline void ColorP3ui(GLenum type, GLuint color){_detail::ColorP3ui(type, color);}
	inline void ColorP3uiv(GLenum type, const GLuint * color){_detail::ColorP3uiv(type, color);}
	inline void ColorP4ui(GLenum type, GLuint color){_detail::ColorP4ui(type, color);}
	inline void ColorP4uiv(GLenum type, const GLuint * color){_detail::ColorP4uiv(type, color);}
	inline void DeleteSamplers(GLsizei count, const GLuint * samplers){_detail::DeleteSamplers(count, samplers);}
	inline void GenSamplers(GLsizei count, GLuint * samplers){_detail::GenSamplers(count, samplers);}
	inline GLint GetFragDataIndex(GLuint program, const GLchar * name){return _detail::GetFragDataIndex(program, name);}
	inline void GetQueryObjecti64v(GLuint id, GLenum pname, GLint64 * params){_detail::GetQueryObjecti64v(id, pname, params);}
	inline void GetQueryObjectui64v(GLuint id, GLenum pname, GLuint64 * params){_detail::GetQueryObjectui64v(id, pname, params);}
	inline void GetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint * params){_detail::GetSamplerParameterIiv(sampler, pname, params);}
	inline void GetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint * params){_detail::GetSamplerParameterIuiv(sampler, pname, params);}
	inline void GetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat * params){_detail::GetSamplerParameterfv(sampler, pname, params);}
	inline void GetSamplerParameteriv(GLuint sampler, GLenum pname, GLint * params){_detail::GetSamplerParameteriv(sampler, pname, params);}
	inline GLboolean IsSampler(GLuint sampler){return _detail::IsSampler(sampler);}
	inline void MultiTexCoordP1ui(GLenum texture, GLenum type, GLuint coords){_detail::MultiTexCoordP1ui(texture, type, coords);}
	inline void MultiTexCoordP1uiv(GLenum texture, GLenum type, const GLuint * coords){_detail::MultiTexCoordP1uiv(texture, type, coords);}
	inline void MultiTexCoordP2ui(GLenum texture, GLenum type, GLuint coords){_detail::MultiTexCoordP2ui(texture, type, coords);}
	inline void MultiTexCoordP2uiv(GLenum texture, GLenum type, const GLuint * coords){_detail::MultiTexCoordP2uiv(texture, type, coords);}
	inline void MultiTexCoordP3ui(GLenum texture, GLenum type, GLuint coords){_detail::MultiTexCoordP3ui(texture, type, coords);}
	inline void MultiTexCoordP3uiv(GLenum texture, GLenum type, const GLuint * coords){_detail::MultiTexCoordP3uiv(texture, type, coords);}
	inline void MultiTexCoordP4ui(GLenum texture, GLenum type, GLuint coords){_detail::MultiTexCoordP4ui(texture, type, coords);}
	inline void MultiTexCoordP4uiv(GLenum texture, GLenum type, const GLuint * coords){_detail::MultiTexCoordP4uiv(texture, type, coords);}
	inline void NormalP3ui(GLenum type, GLuint coords){_detail::NormalP3ui(type, coords);}
	inline void NormalP3uiv(GLenum type, const GLuint * coords){_detail::NormalP3uiv(type, coords);}
	inline void QueryCounter(GLuint id, GLenum target){_detail::QueryCounter(id, target);}
	inline void SamplerParameterIiv(GLuint sampler, GLenum pname, const GLint * param){_detail::SamplerParameterIiv(sampler, pname, param);}
	inline void SamplerParameterIuiv(GLuint sampler, GLenum pname, const GLuint * param){_detail::SamplerParameterIuiv(sampler, pname, param);}
	inline void SamplerParameterf(GLuint sampler, GLenum pname, GLfloat param){_detail::SamplerParameterf(sampler, pname, param);}
	inline void SamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat * param){_detail::SamplerParameterfv(sampler, pname, param);}
	inline void SamplerParameteri(GLuint sampler, GLenum pname, GLint param){_detail::SamplerParameteri(sampler, pname, param);}
	inline void SamplerParameteriv(GLuint sampler, GLenum pname, const GLint * param){_detail::SamplerParameteriv(sampler, pname, param);}
	inline void SecondaryColorP3ui(GLenum type, GLuint color){_detail::SecondaryColorP3ui(type, color);}
	inline void SecondaryColorP3uiv(GLenum type, const GLuint * color){_detail::SecondaryColorP3uiv(type, color);}
	inline void TexCoordP1ui(GLenum type, GLuint coords){_detail::TexCoordP1ui(type, coords);}
	inline void TexCoordP1uiv(GLenum type, const GLuint * coords){_detail::TexCoordP1uiv(type, coords);}
	inline void TexCoordP2ui(GLenum type, GLuint coords){_detail::TexCoordP2ui(type, coords);}
	inline void TexCoordP2uiv(GLenum type, const GLuint * coords){_detail::TexCoordP2uiv(type, coords);}
	inline void TexCoordP3ui(GLenum type, GLuint coords){_detail::TexCoordP3ui(type, coords);}
	inline void TexCoordP3uiv(GLenum type, const GLuint * coords){_detail::TexCoordP3uiv(type, coords);}
	inline void TexCoordP4ui(GLenum type, GLuint coords){_detail::TexCoordP4ui(type, coords);}
	inline void TexCoordP4uiv(GLenum type, const GLuint * coords){_detail::TexCoordP4uiv(type, coords);}
	inline void VertexAttribDivisor(GLuint index, GLuint divisor){_detail::VertexAttribDivisor(index, divisor);}
	inline void VertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value){_detail::VertexAttribP1ui(index, type, normalized, value);}
	inline void VertexAttribP1uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value){_detail::VertexAttribP1uiv(index, type, normalized, value);}
	inline void VertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value){_detail::VertexAttribP2ui(index, type, normalized, value);}
	inline void VertexAttribP2uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value){_detail::VertexAttribP2uiv(index, type, normalized, value);}
	inline void VertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value){_detail::VertexAttribP3ui(index, type, normalized, value);}
	inline void VertexAttribP3uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value){_detail::VertexAttribP3uiv(index, type, normalized, value);}
	inline void VertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value){_detail::VertexAttribP4ui(index, type, normalized, value);}
	inline void VertexAttribP4uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value){_detail::VertexAttribP4uiv(index, type, normalized, value);}
	inline void VertexP2ui(GLenum type, GLuint value){_detail::VertexP2ui(type, value);}
	inline void VertexP2uiv(GLenum type, const GLuint * value){_detail::VertexP2uiv(type, value);}
	inline void VertexP3ui(GLenum type, GLuint value){_detail::VertexP3ui(type, value);}
	inline void VertexP3uiv(GLenum type, const GLuint * value){_detail::VertexP3uiv(type, value);}
	inline void VertexP4ui(GLenum type, GLuint value){_detail::VertexP4ui(type, value);}
	inline void VertexP4uiv(GLenum type, const GLuint * value){_detail::VertexP4uiv(type, value);}
	
	inline void BeginQueryIndexed(GLenum target, GLuint index, GLuint id){_detail::BeginQueryIndexed(target, index, id);}
	inline void BindTransformFeedback(GLenum target, GLuint id){_detail::BindTransformFeedback(target, id);}
	inline void BlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha){_detail::BlendEquationSeparatei(buf, modeRGB, modeAlpha);}
	inline void BlendEquationi(GLuint buf, GLenum mode){_detail::BlendEquationi(buf, mode);}
	inline void BlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha){_detail::BlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);}
	inline void BlendFunci(GLuint buf, GLenum src, GLenum dst){_detail::BlendFunci(buf, src, dst);}
	inline void DeleteTransformFeedbacks(GLsizei n, const GLuint * ids){_detail::DeleteTransformFeedbacks(n, ids);}
	inline void DrawArraysIndirect(GLenum mode, const GLvoid * indirect){_detail::DrawArraysIndirect(mode, indirect);}
	inline void DrawElementsIndirect(GLenum mode, GLenum type, const GLvoid * indirect){_detail::DrawElementsIndirect(mode, type, indirect);}
	inline void DrawTransformFeedback(GLenum mode, GLuint id){_detail::DrawTransformFeedback(mode, id);}
	inline void DrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream){_detail::DrawTransformFeedbackStream(mode, id, stream);}
	inline void EndQueryIndexed(GLenum target, GLuint index){_detail::EndQueryIndexed(target, index);}
	inline void GenTransformFeedbacks(GLsizei n, GLuint * ids){_detail::GenTransformFeedbacks(n, ids);}
	inline void GetActiveSubroutineName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name){_detail::GetActiveSubroutineName(program, shadertype, index, bufsize, length, name);}
	inline void GetActiveSubroutineUniformName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name){_detail::GetActiveSubroutineUniformName(program, shadertype, index, bufsize, length, name);}
	inline void GetActiveSubroutineUniformiv(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint * values){_detail::GetActiveSubroutineUniformiv(program, shadertype, index, pname, values);}
	inline void GetProgramStageiv(GLuint program, GLenum shadertype, GLenum pname, GLint * values){_detail::GetProgramStageiv(program, shadertype, pname, values);}
	inline void GetQueryIndexediv(GLenum target, GLuint index, GLenum pname, GLint * params){_detail::GetQueryIndexediv(target, index, pname, params);}
	inline GLuint GetSubroutineIndex(GLuint program, GLenum shadertype, const GLchar * name){return _detail::GetSubroutineIndex(program, shadertype, name);}
	inline GLint GetSubroutineUniformLocation(GLuint program, GLenum shadertype, const GLchar * name){return _detail::GetSubroutineUniformLocation(program, shadertype, name);}
	inline void GetUniformSubroutineuiv(GLenum shadertype, GLint location, GLuint * params){_detail::GetUniformSubroutineuiv(shadertype, location, params);}
	inline void GetUniformdv(GLuint program, GLint location, GLdouble * params){_detail::GetUniformdv(program, location, params);}
	inline GLboolean IsTransformFeedback(GLuint id){return _detail::IsTransformFeedback(id);}
	inline void MinSampleShading(GLfloat value){_detail::MinSampleShading(value);}
	inline void PatchParameterfv(GLenum pname, const GLfloat * values){_detail::PatchParameterfv(pname, values);}
	inline void PatchParameteri(GLenum pname, GLint value){_detail::PatchParameteri(pname, value);}
	inline void PauseTransformFeedback(){_detail::PauseTransformFeedback();}
	inline void ResumeTransformFeedback(){_detail::ResumeTransformFeedback();}
	inline void Uniform1d(GLint location, GLdouble x){_detail::Uniform1d(location, x);}
	inline void Uniform1dv(GLint location, GLsizei count, const GLdouble * value){_detail::Uniform1dv(location, count, value);}
	inline void Uniform2d(GLint location, GLdouble x, GLdouble y){_detail::Uniform2d(location, x, y);}
	inline void Uniform2dv(GLint location, GLsizei count, const GLdouble * value){_detail::Uniform2dv(location, count, value);}
	inline void Uniform3d(GLint location, GLdouble x, GLdouble y, GLdouble z){_detail::Uniform3d(location, x, y, z);}
	inline void Uniform3dv(GLint location, GLsizei count, const GLdouble * value){_detail::Uniform3dv(location, count, value);}
	inline void Uniform4d(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w){_detail::Uniform4d(location, x, y, z, w);}
	inline void Uniform4dv(GLint location, GLsizei count, const GLdouble * value){_detail::Uniform4dv(location, count, value);}
	inline void UniformMatrix2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::UniformMatrix2dv(location, count, transpose, value);}
	inline void UniformMatrix2x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::UniformMatrix2x3dv(location, count, transpose, value);}
	inline void UniformMatrix2x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::UniformMatrix2x4dv(location, count, transpose, value);}
	inline void UniformMatrix3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::UniformMatrix3dv(location, count, transpose, value);}
	inline void UniformMatrix3x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::UniformMatrix3x2dv(location, count, transpose, value);}
	inline void UniformMatrix3x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::UniformMatrix3x4dv(location, count, transpose, value);}
	inline void UniformMatrix4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::UniformMatrix4dv(location, count, transpose, value);}
	inline void UniformMatrix4x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::UniformMatrix4x2dv(location, count, transpose, value);}
	inline void UniformMatrix4x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::UniformMatrix4x3dv(location, count, transpose, value);}
	inline void UniformSubroutinesuiv(GLenum shadertype, GLsizei count, const GLuint * indices){_detail::UniformSubroutinesuiv(shadertype, count, indices);}
	
	inline void ActiveShaderProgram(GLuint pipeline, GLuint program){_detail::ActiveShaderProgram(pipeline, program);}
	inline void BindProgramPipeline(GLuint pipeline){_detail::BindProgramPipeline(pipeline);}
	inline void ClearDepthf(GLfloat d){_detail::ClearDepthf(d);}
	inline GLuint CreateShaderProgramv(GLenum type, GLsizei count, const GLchar *const* strings){return _detail::CreateShaderProgramv(type, count, strings);}
	inline void DeleteProgramPipelines(GLsizei n, const GLuint * pipelines){_detail::DeleteProgramPipelines(n, pipelines);}
	inline void DepthRangeArrayv(GLuint first, GLsizei count, const GLdouble * v){_detail::DepthRangeArrayv(first, count, v);}
	inline void DepthRangeIndexed(GLuint index, GLdouble n, GLdouble f){_detail::DepthRangeIndexed(index, n, f);}
	inline void DepthRangef(GLfloat n, GLfloat f){_detail::DepthRangef(n, f);}
	inline void GenProgramPipelines(GLsizei n, GLuint * pipelines){_detail::GenProgramPipelines(n, pipelines);}
	inline void GetDoublei_v(GLenum target, GLuint index, GLdouble * data){_detail::GetDoublei_v(target, index, data);}
	inline void GetFloati_v(GLenum target, GLuint index, GLfloat * data){_detail::GetFloati_v(target, index, data);}
	inline void GetProgramBinary(GLuint program, GLsizei bufSize, GLsizei * length, GLenum * binaryFormat, GLvoid * binary){_detail::GetProgramBinary(program, bufSize, length, binaryFormat, binary);}
	inline void GetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei * length, GLchar * infoLog){_detail::GetProgramPipelineInfoLog(pipeline, bufSize, length, infoLog);}
	inline void GetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint * params){_detail::GetProgramPipelineiv(pipeline, pname, params);}
	inline void GetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint * range, GLint * precision){_detail::GetShaderPrecisionFormat(shadertype, precisiontype, range, precision);}
	inline void GetVertexAttribLdv(GLuint index, GLenum pname, GLdouble * params){_detail::GetVertexAttribLdv(index, pname, params);}
	inline GLboolean IsProgramPipeline(GLuint pipeline){return _detail::IsProgramPipeline(pipeline);}
	inline void ProgramBinary(GLuint program, GLenum binaryFormat, const GLvoid * binary, GLsizei length){_detail::ProgramBinary(program, binaryFormat, binary, length);}
	inline void ProgramParameteri(GLuint program, GLenum pname, GLint value){_detail::ProgramParameteri(program, pname, value);}
	inline void ProgramUniform1d(GLuint program, GLint location, GLdouble v0){_detail::ProgramUniform1d(program, location, v0);}
	inline void ProgramUniform1dv(GLuint program, GLint location, GLsizei count, const GLdouble * value){_detail::ProgramUniform1dv(program, location, count, value);}
	inline void ProgramUniform1f(GLuint program, GLint location, GLfloat v0){_detail::ProgramUniform1f(program, location, v0);}
	inline void ProgramUniform1fv(GLuint program, GLint location, GLsizei count, const GLfloat * value){_detail::ProgramUniform1fv(program, location, count, value);}
	inline void ProgramUniform1i(GLuint program, GLint location, GLint v0){_detail::ProgramUniform1i(program, location, v0);}
	inline void ProgramUniform1iv(GLuint program, GLint location, GLsizei count, const GLint * value){_detail::ProgramUniform1iv(program, location, count, value);}
	inline void ProgramUniform1ui(GLuint program, GLint location, GLuint v0){_detail::ProgramUniform1ui(program, location, v0);}
	inline void ProgramUniform1uiv(GLuint program, GLint location, GLsizei count, const GLuint * value){_detail::ProgramUniform1uiv(program, location, count, value);}
	inline void ProgramUniform2d(GLuint program, GLint location, GLdouble v0, GLdouble v1){_detail::ProgramUniform2d(program, location, v0, v1);}
	inline void ProgramUniform2dv(GLuint program, GLint location, GLsizei count, const GLdouble * value){_detail::ProgramUniform2dv(program, location, count, value);}
	inline void ProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1){_detail::ProgramUniform2f(program, location, v0, v1);}
	inline void ProgramUniform2fv(GLuint program, GLint location, GLsizei count, const GLfloat * value){_detail::ProgramUniform2fv(program, location, count, value);}
	inline void ProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1){_detail::ProgramUniform2i(program, location, v0, v1);}
	inline void ProgramUniform2iv(GLuint program, GLint location, GLsizei count, const GLint * value){_detail::ProgramUniform2iv(program, location, count, value);}
	inline void ProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1){_detail::ProgramUniform2ui(program, location, v0, v1);}
	inline void ProgramUniform2uiv(GLuint program, GLint location, GLsizei count, const GLuint * value){_detail::ProgramUniform2uiv(program, location, count, value);}
	inline void ProgramUniform3d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2){_detail::ProgramUniform3d(program, location, v0, v1, v2);}
	inline void ProgramUniform3dv(GLuint program, GLint location, GLsizei count, const GLdouble * value){_detail::ProgramUniform3dv(program, location, count, value);}
	inline void ProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2){_detail::ProgramUniform3f(program, location, v0, v1, v2);}
	inline void ProgramUniform3fv(GLuint program, GLint location, GLsizei count, const GLfloat * value){_detail::ProgramUniform3fv(program, location, count, value);}
	inline void ProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2){_detail::ProgramUniform3i(program, location, v0, v1, v2);}
	inline void ProgramUniform3iv(GLuint program, GLint location, GLsizei count, const GLint * value){_detail::ProgramUniform3iv(program, location, count, value);}
	inline void ProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2){_detail::ProgramUniform3ui(program, location, v0, v1, v2);}
	inline void ProgramUniform3uiv(GLuint program, GLint location, GLsizei count, const GLuint * value){_detail::ProgramUniform3uiv(program, location, count, value);}
	inline void ProgramUniform4d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3){_detail::ProgramUniform4d(program, location, v0, v1, v2, v3);}
	inline void ProgramUniform4dv(GLuint program, GLint location, GLsizei count, const GLdouble * value){_detail::ProgramUniform4dv(program, location, count, value);}
	inline void ProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3){_detail::ProgramUniform4f(program, location, v0, v1, v2, v3);}
	inline void ProgramUniform4fv(GLuint program, GLint location, GLsizei count, const GLfloat * value){_detail::ProgramUniform4fv(program, location, count, value);}
	inline void ProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3){_detail::ProgramUniform4i(program, location, v0, v1, v2, v3);}
	inline void ProgramUniform4iv(GLuint program, GLint location, GLsizei count, const GLint * value){_detail::ProgramUniform4iv(program, location, count, value);}
	inline void ProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3){_detail::ProgramUniform4ui(program, location, v0, v1, v2, v3);}
	inline void ProgramUniform4uiv(GLuint program, GLint location, GLsizei count, const GLuint * value){_detail::ProgramUniform4uiv(program, location, count, value);}
	inline void ProgramUniformMatrix2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::ProgramUniformMatrix2dv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::ProgramUniformMatrix2fv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix2x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::ProgramUniformMatrix2x3dv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::ProgramUniformMatrix2x3fv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix2x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::ProgramUniformMatrix2x4dv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::ProgramUniformMatrix2x4fv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::ProgramUniformMatrix3dv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::ProgramUniformMatrix3fv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix3x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::ProgramUniformMatrix3x2dv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::ProgramUniformMatrix3x2fv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix3x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::ProgramUniformMatrix3x4dv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::ProgramUniformMatrix3x4fv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::ProgramUniformMatrix4dv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::ProgramUniformMatrix4fv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix4x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::ProgramUniformMatrix4x2dv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::ProgramUniformMatrix4x2fv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix4x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::ProgramUniformMatrix4x3dv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::ProgramUniformMatrix4x3fv(program, location, count, transpose, value);}
	inline void ReleaseShaderCompiler(){_detail::ReleaseShaderCompiler();}
	inline void ScissorArrayv(GLuint first, GLsizei count, const GLint * v){_detail::ScissorArrayv(first, count, v);}
	inline void ScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height){_detail::ScissorIndexed(index, left, bottom, width, height);}
	inline void ScissorIndexedv(GLuint index, const GLint * v){_detail::ScissorIndexedv(index, v);}
	inline void ShaderBinary(GLsizei count, const GLuint * shaders, GLenum binaryformat, const GLvoid * binary, GLsizei length){_detail::ShaderBinary(count, shaders, binaryformat, binary, length);}
	inline void UseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program){_detail::UseProgramStages(pipeline, stages, program);}
	inline void ValidateProgramPipeline(GLuint pipeline){_detail::ValidateProgramPipeline(pipeline);}
	inline void VertexAttribL1d(GLuint index, GLdouble x){_detail::VertexAttribL1d(index, x);}
	inline void VertexAttribL1dv(GLuint index, const GLdouble * v){_detail::VertexAttribL1dv(index, v);}
	inline void VertexAttribL2d(GLuint index, GLdouble x, GLdouble y){_detail::VertexAttribL2d(index, x, y);}
	inline void VertexAttribL2dv(GLuint index, const GLdouble * v){_detail::VertexAttribL2dv(index, v);}
	inline void VertexAttribL3d(GLuint index, GLdouble x, GLdouble y, GLdouble z){_detail::VertexAttribL3d(index, x, y, z);}
	inline void VertexAttribL3dv(GLuint index, const GLdouble * v){_detail::VertexAttribL3dv(index, v);}
	inline void VertexAttribL4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w){_detail::VertexAttribL4d(index, x, y, z, w);}
	inline void VertexAttribL4dv(GLuint index, const GLdouble * v){_detail::VertexAttribL4dv(index, v);}
	inline void VertexAttribLPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer){_detail::VertexAttribLPointer(index, size, type, stride, pointer);}
	inline void ViewportArrayv(GLuint first, GLsizei count, const GLfloat * v){_detail::ViewportArrayv(first, count, v);}
	inline void ViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h){_detail::ViewportIndexedf(index, x, y, w, h);}
	inline void ViewportIndexedfv(GLuint index, const GLfloat * v){_detail::ViewportIndexedfv(index, v);}
	
	
	namespace sys
	{
		
		exts::LoadTest LoadFunctions();
		
		int GetMinorVersion();
		int GetMajorVersion();
		bool IsVersionGEQ(int majorVersion, int minorVersion);
		
	} //namespace sys
} //namespace gl



#endif //FUNCTION_CPP_GENERATED_HEADEROPENGL_HPP
