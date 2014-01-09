#include "Render_PCH.h"
#include "Shader.h"   

#include "Kernel/Profiler/Profiler.h"
#include "Kernel/FileSystem/FileSystem.h"
#include "Kernel/Utils/StringUtils.h"
#include "Render/RenderGL.h"
#include "Render/Buffers/Vertex.h"
#include "Render/Materials/Material.h"
#include "Render/ShaderFramework/ShaderManager.h"
#include "Render/ShaderFramework/ShaderParameterProvider.h"
#include "Render/ShaderFramework/ShaderParameterProviderDescriptor.h"
#include "Render/ShaderFramework/ShaderParameterProviderManager.h"

#ifdef CreateFile
#undef CreateFile
#endif /*CreateFile*/

#ifdef _DEBUG
#   ifndef TRACE_SHADER
#       define TRACE_SHADER(_format, ...) THOT_TRACE_LINE(_format, __VA_ARGS__);
#   else
#       error TRACE_SHADER allready defined; change macro name to resolve conflict;
#   endif /*TRACE_SHADER*/
#else
#   define TRACE_SHADER(_format, ...)
#endif /*_DEBUG*/

CShader::CShader()
    : m_isValid (false)
{
}


//---------------------------------------------------------------------------------------
CShader::~CShader()
{
    gl::DetachShader( m_shaderData.m_shaderID, m_shaderData.m_nativePixelShaderHandle);
    gl::DetachShader( m_shaderData.m_shaderID, m_shaderData.m_nativeVertexShaderHandle );
     
    gl::DeleteShader( m_shaderData.m_nativeVertexShaderHandle );
    gl::DeleteShader( m_shaderData.m_nativePixelShaderHandle );
    gl::DeleteProgram( m_shaderData.m_shaderID );
}
#undef DECLARE_DEFAULT_CONSTRUCTOR_LIST

//---------------------------------------------------------------------------------------
ShaderID CShader::GetID ( )
{
    return m_shaderData.m_shaderID;
}

//---------------------------------------------------------------------------------------
Bool CShader::ReadShaderSource( const CString& vertexShaderPath, const CString& fragmentShaderPath, CString& outVertexSource, CString& outFragSource )
{
    Bool rezult = false;
    rezult |= ReadShaderSource( vertexShaderPath, outVertexSource );
    rezult |= ReadShaderSource( fragmentShaderPath, outFragSource );
    return rezult;
}

//---------------------------------------------------------------------------------------
Bool CShader::ReadShaderSource( const CString& path, CString& outSource )
{
    FileSystem::FileHandle pFile = FileSystem::CreateFile( EFileType::E_FILE_TYPE_NORMAL );
    if( !pFile->Open( path, EAccesMode::E_ACCES_MODE_READ ) )
    {
        return false;
    }

    u64 nSize = pFile->GetSize();
    outSource.Resize( nSize );
    if ( !pFile->Read( outSource.GetBuffer(), nSize, 1 ) )
    {
        TRACE_SHADER( "Could not read shader source[%s]", path.GetBuffer() );
        return false;
    }

    return true;
}

//---------------------------------------------------------------------------------------
Bool CShader::Compile  ( const SShaderCompileContext& compileContext )
{
RENDER_GUARD_BLOCK

#if defined(THOT_ENABLE_DEBUG)
    m_debugCompileContext = compileContext;
    m_shaderData.m_debugParentShader = this;
#endif

    m_shaderData.m_nativeVertexShaderHandle = gl::CreateShader( gl::VERTEX_SHADER );
    m_shaderData.m_nativePixelShaderHandle  = gl::CreateShader( gl::FRAGMENT_SHADER );

    CString vertexSource;
    CString fragSource;
    if( !ReadShaderSource( compileContext.m_vertexShaderPath, compileContext.m_fragmentShaderPath, vertexSource, fragSource ) )
    {
        TRACE_SHADER( "ERROR! CANNOT READ SOURCE OF VERTEX[%s] or FRAGMENT[%s] SHADER", compileContext.m_vertexShaderPath.c_str(), compileContext.m_fragmentShaderPath.c_str() );
        return false;
    }
    
    {
        RENDER_GUARD_BLOCK
        const char* vs = vertexSource.GetBuffer();
        gl::ShaderSource( m_shaderData.m_nativeVertexShaderHandle, 1, &vs, NULL );

        const char* fs = fragSource.GetBuffer();
        gl::ShaderSource( m_shaderData.m_nativePixelShaderHandle, 1, &fs, NULL );

        gl::CompileShader( m_shaderData.m_nativeVertexShaderHandle );
        gl::CompileShader( m_shaderData.m_nativePixelShaderHandle );
    }

    // verify if compile succeeded
    if( !ValidateShader( m_shaderData.m_nativeVertexShaderHandle, compileContext.m_vertexShaderPath ) || 
        !ValidateShader( m_shaderData.m_nativePixelShaderHandle, compileContext.m_fragmentShaderPath) 
        )
    {
        THOT_ASSERT(false, "SHADER VALIDATION FAILED");
        return false;
    }

    // create native opengl shader programm and attach shaders to it;
    {
        RENDER_GUARD_BLOCK

        m_shaderData.m_shaderID = gl::CreateProgram( );
        gl::AttachShader( m_shaderData.m_shaderID, m_shaderData.m_nativeVertexShaderHandle );
        gl::AttachShader( m_shaderData.m_shaderID, m_shaderData.m_nativePixelShaderHandle );
        gl::LinkProgram( m_shaderData.m_shaderID);
    }

    // verify if link succeeded
    if( !ValidateProgram(m_shaderData.m_shaderID) )
    {
        THOT_ASSERT(0);
        return false;
    }

    if( !OnPostCompile() )
    {
        THOT_ASSERT( false, "POST COMPILE SHADER PROCESS FAILED FOR SHADER[%s]", compileContext.m_shaderName.c_str() );
        return false;
    }

    m_isValid = true;

    return true;
}

//---------------------------------------------------------------------------------------
Bool CShader::ValidateShader ( ShaderID shaderID, const CString& fileName )
{
    RENDER_GUARD_BLOCK
    if( !HasCompileErrors(shaderID) )
    {
         return true;
    }
     
    int infologLength = 0;
    int charsWritten  = 0;
    gl::GetShaderiv( shaderID, gl::INFO_LOG_LENGTH, &infologLength);

    if (infologLength > 0)
    {
        CString infoLog;
        infoLog.Resize( (u64)infologLength);
        gl::GetShaderInfoLog( shaderID, infologLength, &charsWritten, infoLog );
        TRACE_SHADER( "Shader[%d] from file[%s] has compile errors:\n%s", shaderID, fileName.GetBuffer(), infoLog.GetBuffer() );
    }

    return false;
}

//---------------------------------------------------------------------------------------
Bool CShader::HasCompileErrors( ShaderID shaderID )
{
    int rezult = 0;
    gl::GetShaderiv( shaderID, gl::COMPILE_STATUS, &rezult );
    return (rezult== gl::TRUE)? false:true;
}

//---------------------------------------------------------------------------------------
Bool CShader::HasLinkErrors( ShaderID shaderID )
{
    int rezult = 0;
    gl::GetProgramiv( shaderID, gl::LINK_STATUS, &rezult );
    return (rezult== gl::TRUE)? false:true;
}

//---------------------------------------------------------------------------------------
Bool CShader::ValidateProgram ( ShaderID shaderID )
{
    RENDER_GUARD_BLOCK;
    if( !HasLinkErrors(shaderID) )
    {
        return true;
    }

    int infologLength = 0;
    int charsWritten  = 0;

    gl::GetProgramiv( shaderID, gl::INFO_LOG_LENGTH, &infologLength);

    if (infologLength > 0)
    {
        CString infoLog;
        infoLog.Resize( (u64)infologLength );

        gl::GetProgramInfoLog( shaderID, infologLength, &charsWritten, infoLog);
        TRACE_SHADER( "Program[%d] has link errors:\n%s", shaderID, infoLog.GetBuffer() );
    }

    return false;
}

//---------------------------------------------------------------------------------------
Bool CShader::IsValid( )
{
    return m_isValid;
}

//---------------------------------------------------------------------------------------
Bool CShader::OnPostCompile()
{
    if( !m_shaderData.BuildInternalData() )
    {
        return false;
    }

    return true;
}

//---------------------------------------------------------------------------------------
CRenderer* CShader::GetRenderer( )
{
    THOT_TODO("REMOVE THIS FUNCTION");
    return NULL;

}

//---------------------------------------------------------------------------------------
void CShader::SetupProviders( const IShaderParameterProvider* providers, u32 count )const
{
    for( u32 i=0; i<count; i++ )
    {
        SetupParameterProvider( providers[i] );
    }
}

//---------------------------------------------------------------------------------------
void CShader::SetupParameterProvider ( const IShaderParameterProvider& parameterProvider )const
{
    DECLARE_PROFILE_SCOPED( "CShader::SetupParameterProvider" );

    ParameterProviderType providerType = parameterProvider.GetType();

    for( u32 i=0; i< EShaderParameterType::Count; i++ )
    {
        const thVector< CShaderData::SParameterInfo>& parameterInfo = m_shaderData.m_parameterInfos[ providerType ][i];

        u64 size = parameterInfo.Size();
        for( u64 j=0; j< size; j++ )
        {
            // here we know what kind of IShaderParameter is;so we can remove the virtual functions from IShaderParameter and save some memory in providers;
            // [TODO] remove virtual functions form IShaderParameter and make template functions for each shader parameter type;
            IShaderParameter& shaderParameter = *(IShaderParameter*) ( (byte*) &parameterProvider + parameterInfo[j].m_dataOffset );
            
            {
                DECLARE_PROFILE_SCOPED("shaderParameter.SetParameterShaderData");
                RENDER_VERIFY;
                shaderParameter.SetParameterShaderData( parameterInfo[j].m_locationID );
                RENDER_VERIFY;
            }
        }
    }
}

//---------------------------------------------------------------------------------------

