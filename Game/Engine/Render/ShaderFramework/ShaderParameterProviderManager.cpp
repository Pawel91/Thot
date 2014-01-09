#include "Render_PCH.h"
#include "ShaderParameterProviderManager.h"
#include "Render/ShaderFramework/ShaderParameterProvider.h"
#include "Render/ShaderFramework/ShaderParameterProviderDescriptor.h"

THOT_IMPLEMENT_SINGLETON(CShaderParameterProviderManager);


CShaderParameterProviderManager:: CShaderParameterProviderManager()
{
}

CShaderParameterProviderManager::~CShaderParameterProviderManager()
{
}

const CShaderParameterProviderDescriptor& CShaderParameterProviderManager::GetDescriptor( ParameterProviderType providerType ) const
{
    THOT_ASSERT( providerType < m_providerDescriptors.Size(), "SHADER PARAMETER PROVIDER TYPE[%d] IS NOT REGISTERED", providerType );
    // I don`t know where to put this assert so I will put it here:D
    THOT_ASSERT( m_providerDescriptors.Size() == SHADER_PARAMETER_PROVIDER_COUNT,
                "CShaderParameterProviderDescriptor has [%d] descriptor but SHADER_PARAMETER_PROVIDER_COUNT is [%d]", m_providerDescriptors.Size(), SHADER_PARAMETER_PROVIDER_COUNT );

    return *m_providerDescriptors[providerType];
}

#if defined(THOT_ENABLE_DEBUG)
Bool CShaderParameterProviderManager::DebugVerifyRegisterDescriptor( CShaderParameterProviderDescriptor& providerDescriptor )
{
    // verify that this parameter was not allready registered
    for( u64 i=0; i < m_providerDescriptors.Size(); i++ )
    {
        const CShaderParameterProviderDescriptor& descriptor = *m_providerDescriptors[i];
        if( descriptor.GetProviderName() == providerDescriptor.GetProviderName() )
        {
            THOT_ASSERT(false, "PROVIDER[%s] WAS ALLREADY REGISTRED IN SHADER PROVIDER MANAGER", providerDescriptor.GetProviderName().GetBuffer() );
            return false;
        }
    }

    // parse all other registered descriptors and verify for parameter name conflicts
    for( u64 i=0; i<m_providerDescriptors.Size(); i++ )
    {
        const CShaderParameterProviderDescriptor& descriptor = *m_providerDescriptors[i];
        thVector<CString> names; descriptor.DebugGetParameterNameArray(names);
        thVector<CString> toAddNames; providerDescriptor.DebugGetParameterNameArray(toAddNames);

        for( u64 i=0; i<names.Size(); i++ )
        {
            const CString& name = names[i];
            for( u64 j=0; j< toAddNames.Size(); j++ )
            {
                const CString& toAddName = toAddNames[j];
                if( name == toAddName )
                {
                    THOT_ASSERT("SHADER PARAMETER NAME CONFLICT DETECTED!! PROVIDER[%s] and PROVIDER[%d] share same parameter name [%s]", 
                                descriptor.GetProviderName().c_str(), 
                                providerDescriptor.GetProviderName().c_str() );
                    return false;
                }
            }
        }
    }

    return true;
}
#endif //THOT_ENABLE_DEBUG

Bool CShaderParameterProviderManager::RegisterDescriptor( CShaderParameterProviderDescriptor& providerDescriptor )
{
#if defined(THOT_ENABLE_DEBUG)
    //verify descriptor before actual register
    if ( !DebugVerifyRegisterDescriptor( providerDescriptor ))
    {
        return false;
    }

#endif //THOT_ENABLE_DEBUG
    // add the pointer to provider descriptor;
    // the index of the new element will be the provider type;
    providerDescriptor.m_type = ThNumericCast<ParameterProviderType>( m_providerDescriptors.PushBack( &providerDescriptor ) );

    return true;
}

u32 CShaderParameterProviderManager::GetDescriptorsCount ()
{
    return ThNumericCast<u32>( m_providerDescriptors.Size() );
}