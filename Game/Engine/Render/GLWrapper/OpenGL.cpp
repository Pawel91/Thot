#include "Render_PCH.h"
#include "OpenGL.h"

#include "Kernel/DataStructures/CString.h"
#include <map>


typedef std::map<GLenum, CString> TGLMap;
TGLMap g_glEnumToStringMap;

namespace glDebug
{
    Bool            Init                ( )
    {
#undef GL_ENUM
#define GL_ENUM(__name, __val) g_glEnumToStringMap[ (GLenum)__val ] = CString( #__name );
        GL_EXPAND_ENUM
    
        return true;
    }

    const char*     GetNameFromEnum     ( GLenum val )
    {
        TGLMap::const_iterator it =  g_glEnumToStringMap.find(val);
        if( it == g_glEnumToStringMap.end() )
        {
            return NULL;
        }

        return it->second;
    }
};
