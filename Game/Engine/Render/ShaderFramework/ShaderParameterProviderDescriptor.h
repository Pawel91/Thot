#if !defined(__RENDER_SHADER_PARAMETER_PROVIDER_DESCRIPTOR_H__)
#define __RENDER_SHADER_PARAMETER_PROVIDER_DESCRIPTOR_H__

#include "Kernel/DataStructures/Array/Vector.h"
#include "Render/ShaderFramework/ShaderParameter.h"
#include "Render/ShaderFramework/ShaderParameterProviderTypes.h"
#include "Render/ShaderFramework/ShaderLayout/ShaderUniform.h"


struct  SProviderDescriptorPrivateData;
class   CShaderUniform;
class   IShaderParameter;

struct SShaderParameterInfo
{
    SShaderParameterInfo(){}
    
    SShaderParameterInfo( u16 dataOffset, EShaderParameterType parameterType )
        : m_dataOffset      ( dataOffset )
        , m_parameterType   ( parameterType )
    {}

    u16                 m_dataOffset;       // offset in ShaderParameterProvider
    u16                 m_parameterType;    // EShaderParameterType
};

// every parameter provider class has a static descriptor
// holds layout for each parameter provider
class RENDER_API CShaderParameterProviderDescriptor
{
    friend class IShaderParameterProvider;
    friend class CShaderParameterProviderManager;
    template<class T> friend class CShaderParameterProviderBase;

public:
    CShaderParameterProviderDescriptor  ( TCreateParameterMapFunction createMapFunction );
    ~CShaderParameterProviderDescriptor ( );

    Bool                                        GetParameterInfo    ( const CString& parameterName, SShaderParameterInfo& outInfo )const;
    THOT_FORCE_INLINE ParameterProviderType     GetProviderType     ( )const;
    const CString&                              GetProviderName     ( )const;
    u32                                         GetParameterCount   ( )const; //nb of parameter in parameterProvider;
    void                                        AddParameter        ( const IShaderParameter& parameter, EShaderParameterType parameterType, const CString parameterName );

#if defined (THOT_ENABLE_DEBUG)
    void                                        DebugGetParameterNameArray( thVector<CString>& outNames )const;
#endif 

public:
    static const u32   ms_privateDataSize = 64;


private:
    void            SetProviderName     ( const CString& name );


private:
    u8                                  m_rawPrivateData[ms_privateDataSize];
    SProviderDescriptorPrivateData*     m_privateData;

    ParameterProviderType               m_type;
    CString                             m_providerName;
};


THOT_FORCE_INLINE ParameterProviderType CShaderParameterProviderDescriptor::GetProviderType( )const
{
    return m_type;
}

#endif //__RENDER_SHADER_PARAMETER_PROVIDER_DESCRIPTOR_H__