#include "Render_PCH.h"
#include "ShaderLayout.h"
#include "Render/GLWrapper/OpenGL.h"
#include "Kernel/DataStructures/Array/Array.h"

#if defined(THOT_ENABLE_DEBUG)
#include "Kernel/Utils/StringUtils.h"
#endif

#include <vector>

//---------------------------------------------------------------------------------------

CShaderLayout:: CShaderLayout()
    : m_isValid         (false)
    , m_uniformCount    ( 0 )
{

}

//---------------------------------------------------------------------------------------

CShaderLayout::~CShaderLayout()
{

}

//---------------------------------------------------------------------------------------

u32 CShaderLayout::GetUniformCount( )const
{
    return m_uniformCount;
}

//---------------------------------------------------------------------------------------

const CShaderUniform& CShaderLayout::GetUniform    ( u32 index )const
{
    THOT_ASSERT( index < m_uniformCount);
    return m_uniforms[index];
}

//---------------------------------------------------------------------------------------

Bool CShaderLayout::BuildInternalData( ShaderID shaderID )
{
    if( m_isValid )
    {
        THOT_ASSERT( false, "CShaderLayout allready constructed" );
        return false;
    }
    m_uniforms.Reserve(128);
#if defined(THOT_ENABLE_DEBUG)
    m_shaderID = shaderID;
#endif //THOT_ENABLE_DEBUG

    //parse all shader uniforms
    gl::GetProgramiv( shaderID, gl::ACTIVE_UNIFORMS, (GLint*)&m_uniformCount );
    
    CStaticArray<GLchar, 256> nameData;
    thVector<CString> activeUniformsNames;
    for( u32 unif = 0; unif < m_uniformCount; ++unif )
    {
        CShaderUniform uniform;

        GLenum nativeTypeID = 0;  
        GLsizei actualLength = 0;
        gl::GetActiveUniform(   shaderID,
                                (GLuint)unif,
                                (GLsizei)nameData.GetSize(),
                                &actualLength,
                                (GLint*)&uniform.m_elementCount, // setting uniform element count here
                                &nativeTypeID,
                                &nameData[0]);

        CString name( &nameData[0] );
        THOT_ASSERT( name.GetLenght() == actualLength );
        activeUniformsNames.PushBack( name );
        u32 uniformLocation  = gl::GetUniformLocation( shaderID, name.c_str() );
        CString nativeTypeStringID = glDebug::GetNameFromEnum(nativeTypeID);

        uniform.SetName( name.c_str() );
        uniform.SetLocation( uniformLocation );
#if defined(THOT_ENABLE_DEBUG_TOOLS)
        uniform.SetNativeParameterTypeID(nativeTypeID);
        uniform.SetNativeTypeStringID(nativeTypeStringID);
#endif //defined(THOT_ENABLE_DEBUG_TOOLS)

        m_uniforms.PushBack( uniform );
    }

    m_isValid = true;
    
#if defined(THOT_ENABLE_DEBUG)
    CString shaderDataDebugString = DebugDump();
    THOT_TRACE_LINE( "%s", shaderDataDebugString.GetBuffer() );
#endif

    return true;
}

//---------------------------------------------------------------------------------------

#if defined(THOT_ENABLE_DEBUG)
CString CShaderLayout::DebugDump()
{
    CString rezult;
    rezult += StringUtils::FormatString( "SHADER WITH ID[%d]\n", m_shaderID );
    for( u64 i=0; i < m_uniforms.Size(); i++ )
    {
        rezult += StringUtils::FormatString("====== BEGIN UNIFORM\n");

        const CShaderUniform& uniform = m_uniforms[i];

        rezult += StringUtils::FormatString("   UNIFORM NAME                [%s]\n",        uniform.m_name.GetBuffer() );
        rezult += StringUtils::FormatString("   UNIFORM LOCATION            [%d]\n",        uniform.m_location );
        rezult += StringUtils::FormatString("   UNIFORM ELEMENT COUNT       [%d]\n",        uniform.m_elementCount );
        
#if defined(THOT_ENABLE_DEBUG_TOOLS)
        rezult += StringUtils::FormatString("   UNIFORM NATIVE TYPEID       [%d]\n",        uniform.m_nativeParameterTypeID );
        rezult += StringUtils::FormatString("   UNIFORM NATIVE TYPE STRING  [%s]\n",        uniform.m_nativeTypeString.GetBuffer() );
#endif

        rezult += StringUtils::FormatString("======END UNIFORM\n\n");
    }

    rezult +="\n";

    return rezult;
}

#endif //THOT_ENABLE_DEBUG