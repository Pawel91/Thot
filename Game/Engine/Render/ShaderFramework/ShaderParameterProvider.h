#if !defined(__RENDER_PARAMETER_PROVIDER_H__)
#define __RENDER_PARAMETER_PROVIDER_H__

#include "Render/ShaderFramework/ShaderParameterImpl.h"
#include "Render/ShaderFramework/ShaderParameterProviderTypes.h"
#include "Render/ShaderFramework/ShaderParameterProviderDescriptor.h"

class IShaderParameter;

// ShaderParameter provider base class; no virtuals here
class RENDER_API IShaderParameterProvider
{
public:
    friend class CShaderParameterProviderManager;
    friend class CShader;

public:

             IShaderParameterProvider ();
            ~IShaderParameterProvider ();

    THOT_FORCE_INLINE ParameterProviderType GetType( ) const ;

protected:
    
    // type of this provider
    // actually is the index in array of descriptor in CShaderParameterProviderManager
    ParameterProviderType          m_type; 
};

THOT_FORCE_INLINE ParameterProviderType IShaderParameterProvider::GetType() const
{
    return m_type;
}

template< typename TYPE_DerivedParameterProvider >
class CShaderParameterProviderBase: public IShaderParameterProvider
{
public:
      CShaderParameterProviderBase();
     ~CShaderParameterProviderBase(){}

protected:

    static  void            SetProviderName ( const CString& providerName );

    template<class TYPE_PARAMETER, u32 SIZE>
    static  void            AddParameter    ( const CShaderParameterTemplateBase<TYPE_PARAMETER, SIZE>& shaderParameter, const CString& parameterName );

    static  CShaderParameterProviderDescriptor      ms_descriptor;

};

// Send the TYPE_DerivedParameterProvider::CreateParameterMap functions to the descriptor
template<typename TYPE_DerivedParameterProvider>
CShaderParameterProviderDescriptor CShaderParameterProviderBase<TYPE_DerivedParameterProvider>::ms_descriptor( &TYPE_DerivedParameterProvider::CreateParameterMap );

template<typename TYPE_DerivedParameterProvider>
void CShaderParameterProviderBase<TYPE_DerivedParameterProvider>::SetProviderName ( const CString& providerName )
{
    //forward the name to the descriptor
    ms_descriptor.SetProviderName( providerName );
}

template<typename TYPE_DerivedParameterProvider>
template<class TYPE_PARAMETER, u32 SIZE>
void CShaderParameterProviderBase<TYPE_DerivedParameterProvider>::AddParameter ( const CShaderParameterTemplateBase<TYPE_PARAMETER, SIZE>& shaderParameter, const CString& parameterName )
{
    // forward the parameter to descriptor
    ms_descriptor.AddParameter( shaderParameter,
                                ThNumericCast<EShaderParameterType>( CShaderParameterTemplateBase<TYPE_PARAMETER, SIZE>::ms_parameterType ),
                                parameterName );
}


template<typename TYPE_DerivedParameterProvider>
CShaderParameterProviderBase<TYPE_DerivedParameterProvider>::CShaderParameterProviderBase()
{
    // the descriptor holds the information about parameter type; 
    // it just passes the type to every instance of parameter provider via this constructor
    m_type = ms_descriptor.GetProviderType();
}

#endif //__RENDER_PARAMETER_PROVIDER_H__