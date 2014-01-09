#include "Render_PCH.h"
#include "ShaderUniform.h"
#include "../ShaderTypes.h"

CShaderUniform:: CShaderUniform()
    : m_parameterType       ( EShaderParameterType::None )
    , m_location            ( ms_invalidUniformLocation )
    , m_elementCount        ( 0 )
#if defined(THOT_ENABLE_DEBUG_TOOLS)
    , m_nativeParameterTypeID (-1)
#endif
{

}

CShaderUniform::CShaderUniform( const CShaderUniform& other)
{
    CopyFromOther( other );
}

CShaderUniform::~CShaderUniform(){}

void CShaderUniform::SetName( const CString& name )
{
    m_name = name;
}

void CShaderUniform::SetLocation  ( u32 uniformLocation )
{
    m_location = uniformLocation;
}

const CString& CShaderUniform::GetName( )const
{
    return m_name;
}

u32 CShaderUniform::GetLocation  ( )const
{
    return m_location;
}

Bool CShaderUniform::GetIsActive() const
{
    return m_location == ms_invalidUniformLocation;
}

u32 CShaderUniform::GetElementCount ( ) const
{ 
    return m_elementCount;
}

EShaderParameterType CShaderUniform::GetType( )const
{
    return m_parameterType;
}

const CShaderUniform& CShaderUniform::operator = ( const CShaderUniform& other)
{
    CopyFromOther(other);
    return *this;
}

void CShaderUniform::CopyFromOther( const CShaderUniform& other )
{
    m_name              = other.m_name;
    m_location          = other.m_location;
    m_elementCount      = other.m_elementCount;
    m_parameterType     = other.m_parameterType;

#if defined(THOT_ENABLE_DEBUG_TOOLS)
    m_nativeParameterTypeID = other.m_nativeParameterTypeID;
    m_nativeTypeString      = other.m_nativeTypeString;
#endif
}

#if defined(THOT_ENABLE_DEBUG_TOOLS)
void CShaderUniform::SetNativeTypeStringID ( const CString& nativeTypeString )
{
    m_nativeTypeString = nativeTypeString;
}

const CString& CShaderUniform::GetNativeTypeStringID ( )const
{
    return m_nativeTypeString;
}

void   CShaderUniform::SetNativeParameterTypeID( u32 nativeTypeID )
{
    m_nativeParameterTypeID = nativeTypeID;
}

u32 CShaderUniform::GetNativeParameterTypeID()const
{
    return m_nativeParameterTypeID;
}


#endif //defined(THOT_ENABLE_DEBUG_TOOLS)
