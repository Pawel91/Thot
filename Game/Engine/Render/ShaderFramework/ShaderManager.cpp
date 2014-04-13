#include "Render_PCH.h"
#include "ShaderManager.h"

#include "Kernel/DataStructures/CString.h"
#include "Kernel/FileSystem/Path.h"
#include "Kernel/Profiler/Profiler.h"
#include "Kernel/Utils/Command.h"

#include "Render/ShaderFramework/Shader.h"
#include "Render/GLWrapper/OpenGL.h"

#include <map>

typedef std::map<CString, CShader*, StdStringLess>      TShadersStringMap;
typedef std::map<ShaderID, CShader*>                    TShadersIDMap;

//--------------------------------------------------------------------------------
struct CShaderManagerPrivateData
{
    TShadersStringMap       m_shadersStringMap;
    TShadersIDMap           m_shadersIDMap;
};

//--------------------------------------------------------------------------------
CShaderManager:: CShaderManager()
    : m_privateData             ( NULL )
    , m_currentActiveShaderID   ( INVALID_SHADERID )
{
    m_privateData = THOT_NEW CShaderManagerPrivateData ;

}

//--------------------------------------------------------------------------------
Bool CShaderManager::Init()
{
    return true;
}

//--------------------------------------------------------------------------------
CShaderManager::~CShaderManager()
{
    if( !m_privateData )
    {
        return;
    }

    for( TShadersStringMap::const_iterator it = m_privateData->m_shadersStringMap.begin(); it != m_privateData->m_shadersStringMap.end(); ++it )
    {
        if( it->second)
        {
            THOT_DELETE(it->second);
        }
    }

    THOT_DELETE(m_privateData);
}

//--------------------------------------------------------------------------------
ShaderID CShaderManager::GetShaderID( const CString& shaderName )
{
    THOT_ASSERT(m_privateData, "SHADER MANAGER PRIVATE DATA IS NULL");

    // try to find if the the shader was compiled
    TShadersStringMap::const_iterator it = m_privateData->m_shadersStringMap.find(shaderName);
    if( it == m_privateData->m_shadersStringMap.end() )
    {
        return CompileShader( shaderName);    
    }

    return it->second->GetID();
}

//-------------------------------------------------------------------------------------------------
ShaderID CShaderManager::CompileShader( const CString& shaderName )
{
    RENDER_GUARD_BLOCK
    CShader* shader = THOT_NEW CShader;
    SShaderCompileContext compileContext;
    CString shadersPath = "Data\\Shaders";
    
    compileContext.m_shaderName = shaderName;
    compileContext.m_vertexShaderPath = shadersPath +"\\" + shaderName +"_v.glsl";
    compileContext.m_fragmentShaderPath = shadersPath + "\\"+ shaderName + "_f.glsl";

    if( ! (CPath::FileExists(compileContext.m_vertexShaderPath) && CPath::FileExists(compileContext.m_fragmentShaderPath) ) )
    {
        CString vertexShaderAbsolutePath;
        CString pixelShaderAbsolutePath;
        CPath::GetAbsolutePath(compileContext.m_vertexShaderPath, vertexShaderAbsolutePath );
        CPath::GetAbsolutePath(compileContext.m_fragmentShaderPath, pixelShaderAbsolutePath );

        THOT_ASSERT( false, "INVALID SOURCE FILES FOR SHADERS: [%s], [%s]", vertexShaderAbsolutePath.c_str(), pixelShaderAbsolutePath.c_str() );
        THOT_DELETE(shader);
        return INVALID_SHADERID;
    }

    if( !shader->Compile( compileContext ) )
    {
        THOT_TRACE_LINE( "FAILED TO INIT SHADER[%s]", shaderName );
        THOT_DELETE(shader);
        return INVALID_SHADERID;
    }

    m_privateData->m_shadersStringMap.insert( std::pair<CString, CShader*>(shaderName, shader) );

#if defined(THOT_ENABLE_DEBUG)
    TShadersStringMap::iterator it = m_privateData->m_shadersStringMap.begin();
    const CString& string = it->first;
    THOT_ASSERT( CFrameAllocator::GetInstance()->IsValidPointer( string.c_str() ) == false, "" );
#endif

    m_privateData->m_shadersIDMap[shader->GetID()] = shader;
    return shader->GetID();
}

//--------------------------------------------------------------------------------
const CShader* CShaderManager::GetShaderFromID( ShaderID shaderID )const
{
    // call the non-cost function
    return const_cast<CShaderManager*>(this)->GetShaderFromID( shaderID );
}

//--------------------------------------------------------------------------------
CShader* CShaderManager::GetShaderFromID( ShaderID shaderID)
{
    THOT_ASSERT(m_privateData, "SHADER MANAGER PRIVATE DATA IS NULL");

    THOT_DECLARE_PROFILE("CShaderManager::GetShaderFromID");

    TShadersIDMap::const_iterator it = m_privateData->m_shadersIDMap.find( shaderID );
    if( it == m_privateData->m_shadersIDMap.end() )
    {
        return NULL;
    }

    return it->second;
}

//--------------------------------------------------------------------------------
void CShaderManager::BindShader( ShaderID shaderID )
{
    THOT_ASSERT(shaderID != INVALID_SHADERID);

    THOT_DECLARE_PROFILE("CShaderManager::BindShader");

#if defined(THOT_ENABLE_DEBUG)
    THOT_ASSERT( m_currentActiveShaderID != shaderID, "BINDING SAME SHADER MULTIPLE TIMES");
#endif

    gl::UseProgram( shaderID );

#if defined(THOT_ENABLE_DEBUG)
    m_currentActiveShaderID = shaderID;
#endif
}

//--------------------------------------------------------------------------------