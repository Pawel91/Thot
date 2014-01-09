#include "Render_PCH.h"
#include "ShaderParameterProviderDescriptor.h"

#include "Kernel/MemoryManagement/Allocator.h"
#include "Render/ShaderFramework/ShaderParameter.h"
#include "Render/ShaderFramework/ShaderParameterProviderManager.h"

#include <map>

//--------------------------------------------------------------------------------
struct SProviderDescriptorPrivateData
{
    SProviderDescriptorPrivateData()
        : m_parameterMap()
    {
    }


    typedef std::pair<CString, SShaderParameterInfo>                                        TParameterMapPair;
    typedef CStlAllocator< TParameterMapPair>                                               TParameterMapAllocator;
    typedef std::map<CString, SShaderParameterInfo, StdStringLess, TParameterMapAllocator>  TParameterMap;
    
    typedef TParameterMap::const_iterator                                                   TParameterMapConstIterator;
    typedef TParameterMap::iterator                                                         TParameterMapIterator;

    TParameterMap     m_parameterMap;
};

THOT_COMPILE_ASSERT( sizeof(SProviderDescriptorPrivateData) < CShaderParameterProviderDescriptor::ms_privateDataSize  );

//--------------------------------------------------------------------------------
CShaderParameterProviderDescriptor::CShaderParameterProviderDescriptor( TCreateParameterMapFunction createMapFunction )
    :m_privateData ( new(m_rawPrivateData) SProviderDescriptorPrivateData ) // to avoid a actual memory allocation
{
    createMapFunction();
    
    if( !CShaderParameterProviderManager::GetInstance())
    {
        CShaderParameterProviderManager::CreateInstance();
    }

    if( !CShaderParameterProviderManager::GetInstance()->RegisterDescriptor( *this ) )
    {
        THOT_ASSERT("FAILED TO REGISTER SHADER PARAMETER DESCRIPTOR[%s]", this->GetProviderName().c_str() );
    }
}

//--------------------------------------------------------------------------------
CShaderParameterProviderDescriptor::~CShaderParameterProviderDescriptor()
{
    m_privateData->~SProviderDescriptorPrivateData();
}

//--------------------------------------------------------------------------------
u32 CShaderParameterProviderDescriptor::GetParameterCount( )const
{
    return ThNumericCast<u32>( m_privateData->m_parameterMap.size() );
}

//--------------------------------------------------------------------------------
const CString& CShaderParameterProviderDescriptor::GetProviderName( )const
{
    return m_providerName;

}

//--------------------------------------------------------------------------------
void CShaderParameterProviderDescriptor::SetProviderName( const CString& name )
{
    m_providerName = name;
}

//--------------------------------------------------------------------------------
void CShaderParameterProviderDescriptor::AddParameter( const IShaderParameter& parameter, EShaderParameterType parameterType, const CString parameterName )
{
    THOT_ASSERT(    m_privateData->m_parameterMap.find( parameterName ) == m_privateData->m_parameterMap.end(),
                    "SHADER PARAMETER[%s] allready added to this descriptor", parameterName.c_str()
                );

    u16 parameterDataOffset = ThNumericCast<u16>(&parameter); // parameter is not an actual object; it is a member from a null parameter provider;
    SShaderParameterInfo parameterInfo ( parameterDataOffset, parameterType );
    m_privateData->m_parameterMap.insert( SProviderDescriptorPrivateData::TParameterMapPair( parameterName, parameterInfo)  );
}

//--------------------------------------------------------------------------------
Bool CShaderParameterProviderDescriptor::GetParameterInfo( const CString& parameterName, SShaderParameterInfo& outInfo )const
{
    SProviderDescriptorPrivateData::TParameterMapConstIterator it;
    if(  ( it = m_privateData->m_parameterMap.find(parameterName) ) == m_privateData->m_parameterMap.end() )
    {
        return false;
    }

    outInfo = it->second;
    return true;
}

//--------------------------------------------------------------------------------
#if defined(THOT_ENABLE_DEBUG)
void CShaderParameterProviderDescriptor::DebugGetParameterNameArray( thVector<CString>& outNames ) const
{
    outNames.Clear();
    for( SProviderDescriptorPrivateData::TParameterMapConstIterator it = m_privateData->m_parameterMap.begin(); it != m_privateData->m_parameterMap.end(); ++it )
    {
        outNames.PushBack( it->first );
    }
}
#endif
//--------------------------------------------------------------------------------