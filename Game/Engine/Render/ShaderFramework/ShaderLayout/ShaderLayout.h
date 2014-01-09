#if !defined(__RENDER_SHADER_LAYOUT_H__)
#define __RENDER_SHADER_LAYOUT_H__

#include "Kernel/DataStructures/Array/Vector.h"
#include "Render/ShaderFramework/ShaderLayout/ShaderUniform.h"
#include "Render/ShaderFramework/ShaderTypes.h"

// native shader layout
// holds information about shader data
class CShaderLayout
{
public:
    typedef thVector<CShaderUniform>     TUniformArray;

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
     CShaderLayout();
    ~CShaderLayout();


//*********************************************
//            INTERFACE
//*********************************************
public:

    u32                     GetUniformCount     ( )const;
    const CShaderUniform&   GetUniform          ( u32 index )const;
    Bool                    BuildInternalData   ( ShaderID shaderID );


#if defined(THOT_ENABLE_DEBUG)
    CString                 DebugDump();
#endif //THOT_ENABLE_DEBUG

//*********************************************
//            HELPERS
//*********************************************
private:


//*********************************************
//            MEMBERS
//*********************************************
private:
    TUniformArray           m_uniforms;
    u32                     m_uniformCount;
    Bool                    m_isValid;


#if defined(THOT_ENABLE_DEBUG)
    ShaderID        m_shaderID; // shader id from which it was built
#endif //THOT_ENABLE_DEBUG
};



#endif //__RENDER_SHADER_LAYOUT_H__