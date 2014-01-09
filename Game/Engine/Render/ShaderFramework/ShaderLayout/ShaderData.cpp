#include "Render_PCH.h"
#include "ShaderData.h"

#include "Kernel/Utils/StringUtils.h"

#include "Render/ShaderFramework/ShaderParameter.h"
#include "Render/ShaderFramework/ShaderParameterProviderDescriptor.h"
#include "Render/ShaderFramework/ShaderParameterProviderManager.h"
#include "Render/GLWrapper/OpenGL.h"
#include <vector>
#include <string>

//-----------------------------------------------------------------------------------

CShaderData::CShaderData()
    : m_shaderID                    ( -1 )
    , m_nativeVertexShaderHandle    ( -1 )
    , m_nativePixelShaderHandle     ( -1 )
#if defined(THOT_ENABLE_DEBUG)
    , m_debugParentShader           ( NULL )
#endif
{

}

//-----------------------------------------------------------------------------------

CShaderData::~CShaderData()
{

}

//-----------------------------------------------------------------------------------

Bool CShaderData::BuildInternalData   ( )
{
    if( !m_layout.BuildInternalData( m_shaderID ) )
    {
        THOT_ASSERT( false, "FAILED TO BUID SHADER LAYOUT FOR SHADERID[%d]", m_shaderID );
        return false;
    }

    BuildParameterInfosData();


#if defined(THOT_ENABLE_DEBUG)
    // print shader layout to output
    CString strLayout =  m_layout.DebugDump();
    THOT_TRACE_LINE( "%s", strLayout.c_str() );
#endif //THOT_ENABLE_DEBUG

    return true;
}

//-----------------------------------------------------------------------------------


void CShaderData::BuildParameterInfosData ( )
{
    CShaderParameterProviderManager* providerManager = CShaderParameterProviderManager::GetInstance( );
    THOT_TRAP(providerManager);

    u32 uniformCount = m_layout.GetUniformCount( );
    for( u64 i=0; i < uniformCount; i++ )
    {
        const CShaderUniform& shaderUniform = m_layout.GetUniform( ThNumericCast<u32>(i) );
        const CString uniformName = shaderUniform.GetName();

        Bool found = false;

        // search uniform name in all providers;
        // [TODO]: optimize this search because is part of shader loading;
        u32 descriptorCount = providerManager->GetDescriptorsCount();
        for( u32 i=0; i<descriptorCount; i++ )
        {
            SShaderParameterInfo paramInfo;
            const CShaderParameterProviderDescriptor& descriptor = providerManager->GetDescriptor( i );

            if( descriptor.GetParameterInfo( uniformName, paramInfo ) )
            {
                found = true;
                m_parameterInfos[ descriptor.GetProviderType() ][ paramInfo.m_parameterType ].PushBack( CShaderData::SParameterInfo( paramInfo.m_dataOffset, shaderUniform.m_location ) );
            }
        }

        if(!found)
        {
            //[TODO] replace with assert after moving all framework
            THOT_TRACE_LINE( "ERRROR!!! SHADER PARAMETER[%s] is not provided in shader with ID[%d]", uniformName.c_str(), m_shaderID );
        }
    }
}

