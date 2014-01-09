#if !defined(__RENDER_SHADER_DATA_H__)
#define __RENDER_SHADER_DATA_H__

#include "Kernel/DataStructures/Array/Array.h"
#include "Render/ShaderFramework/ShaderLayout/ShaderUniform.h"
#include "Render/ShaderFramework/ShaderLayout/ShaderLayout.h"
#include "Render/ShaderFramework/ShaderTypes.h"
#include "Render/ShaderFramework/ShaderParameterProviderTypes.h"

// native shader data container
// all members and functions are private; CShaderData is used only by CShader;
class  CShaderData
{
private:
    friend class CShader;

    // shader parameter info internal data;
    struct SParameterInfo
    {
        SParameterInfo(){}
        SParameterInfo( u32 dataOffset, u32 uniformLocationID )
            : m_dataOffset      ( dataOffset )
            , m_locationID      ( uniformLocationID)
        {}

        u32         m_dataOffset;   // provider data offset;
        u32         m_locationID;   // uniform location
    };

    typedef CStaticArray< CStaticArray< thVector<SParameterInfo>, EShaderParameterType::Count >, SHADER_PARAMETER_PROVIDER_COUNT >       TParameterInfos;

//*******************************************************
//                  CONTR/DESTR                
//*******************************************************
private:
     CShaderData();
    ~CShaderData();

//*******************************************************
//                  FUNCTIONS                
//*******************************************************

private:
    Bool                BuildInternalData       ( );
    void                BuildParameterInfosData ( );


//*******************************************************
//                  MEMBERS                
//*******************************************************
private:
    CShaderLayout       m_layout;
    ShaderID            m_shaderID;                     // opengl program handle [TODO] make engine own shaderID
    u32                 m_nativeVertexShaderHandle;     // opengl handle to vertex shader
    u32                 m_nativePixelShaderHandle;      // opengl handle to pixel shader

    TParameterInfos     m_parameterInfos;

#if defined(THOT_ENABLE_DEBUG)
    CShader const*      m_debugParentShader;
#endif

};

#endif //__RENDER_SHADER_DATA_H__