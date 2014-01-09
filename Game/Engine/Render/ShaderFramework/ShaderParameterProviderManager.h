#if !defined __RENDER_SHADER_PARAMETER_PROVIDER_MANAGER_H__
#define __RENDER_SHADER_PARAMETER_PROVIDER_MANAGER_H__

#include "Kernel/Singleton.h"
#include "Kernel/DataStructures/Array/Vector.h"
#include "Render/ShaderFramework/ShaderParameterProviderTypes.h"


// Shader Provider Manager; container of all providers descriptors; 
// It will be used by shaders to setup shader internal data at loading time;
class CShaderParameterProviderManager
{
    THOT_DECLARE_SINGLETON(CShaderParameterProviderManager);
private:
     CShaderParameterProviderManager();

public:
    ~CShaderParameterProviderManager();

    u32                                         GetDescriptorsCount ();
    const CShaderParameterProviderDescriptor&   GetDescriptor       ( ParameterProviderType providerType ) const;
    Bool                                        RegisterDescriptor  ( CShaderParameterProviderDescriptor& providerDescriptor ); 

private:
#if defined(THOT_ENABLE_DEBUG)
    Bool                                        DebugVerifyRegisterDescriptor( CShaderParameterProviderDescriptor& providerDescriptor );
#endif

private:
    thVector<CShaderParameterProviderDescriptor*>            m_providerDescriptors;
};



#endif //__RENDER_SHADER_PARAMETER_PROVIDER_MANAGER_H__