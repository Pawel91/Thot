#ifndef __RENDER_OPENGL_H__
#define __RENDER_OPENGL_H__

#if !defined(OPENGL_VERSION_4_1)
#   define OPENGL_VERSION_4_1
#endif


#if defined(OPENGL_VERSION_3_3)
    const unsigned int g_OpenGlVersion = 33;
#   include "gl_core_3_3.hpp"

#   elif defined(OPENGL_VERSION_4_1)
    const unsigned int g_OpenGlVersion = 41;
#   include "gl_core_4_1.hpp"

#   else
#   error UNKNOWNM OPENGL VERSION
#endif 

namespace gl
{
    Bool        Init    ();

}

namespace glDebug
{
    Bool            Init                ( );
    const char*     GetNameFromEnum     ( GLenum val );
};


namespace gl
{

    inline Bool     Init()
    {
        int numMissingLoadedFunction = gl::sys::LoadFunctions().GetNumMissing();

        if( numMissingLoadedFunction != 0 )
        {
            THOT_ASSERT( false, "OPENGL FAILED TO INIT!! Cannot load [%d] functions", numMissingLoadedFunction);
            return false;
        }
       
        // verify current version of opengl
        GLint majorVersion;
        GLint minorVersion;
        gl::GetIntegerv( gl::MAJOR_VERSION, &majorVersion );
        gl::GetIntegerv( gl::MINOR_VERSION, &minorVersion );
        unsigned int currentOpenGlVersion = majorVersion *10 + minorVersion;

        if( currentOpenGlVersion < g_OpenGlVersion )
        {
            THOT_ASSERT( false, "CURRENT VERSION OF OPENGL[%d] IS NOT SUPPORT! YOU ARE TRYING TO USE OPENGL[%d]", currentOpenGlVersion, g_OpenGlVersion );
            return false;
        }


        const GLubyte* szVersionGL  = gl::GetString( gl::VERSION );
        const GLubyte* glVendor     = gl::GetString( gl::VENDOR );
        const GLubyte* glRenderer   = gl::GetString( gl::RENDERER );

        THOT_TRACE_LINE( "INIT RENDER ON OPENGL VERSION: [%s], VENDOR: [%s], RENDERER[%s]", szVersionGL, glVendor, glRenderer );

        if( !glDebug::Init() )
        {
            THOT_TRACE_LINE("FAILED TO INIT DEBUG GL");
            // DO NOT RETURN FALSE HERE; we can go on without glDebug
        }

        return true;
    }

}







#endif //__RENDER_OPENGL_H__