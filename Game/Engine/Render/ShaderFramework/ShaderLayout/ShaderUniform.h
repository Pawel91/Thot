#if !defined(__RENDER_SHADER_PRIVATE_DATA_H__)
#define __RENDER_SHADER_PRIVATE_DATA_H__

#include "Kernel/DataStructures/CString.h"
#include "Render/ShaderFramework/ShaderParameterTypes.h"

class CShaderUniform
{
public:
    friend class CShaderLayout;
    friend class CShaderData;
    CShaderUniform();
    CShaderUniform( const CShaderUniform& other);
    const CShaderUniform& operator = ( const CShaderUniform& other);
    ~CShaderUniform();

public:
    void                        SetName             ( const CString& name );
    void                        SetLocation         ( u32 uniformLocation );

    const CString&              GetName             ( ) const;
    u32                         GetLocation         ( ) const;
    EShaderParameterType        GetType             ( ) const;
    Bool                        GetIsActive         ( ) const;
    u32                         GetElementCount     ( ) const;

#if defined(THOT_ENABLE_DEBUG_TOOLS)
    void                        SetNativeParameterTypeID( u32 nativeTypeID );
    u32                         GetNativeParameterTypeID()const;
    void                        SetNativeTypeStringID ( const CString& nativeTypeString );
    const CString&              GetNativeTypeStringID ( )const;
#endif


public:
    static const u32            ms_invalidUniformLocation = -1;

protected:
    void                        CopyFromOther   ( const CShaderUniform& other );

protected:
    CString                     m_name;
    u32                         m_location;
    u32                         m_elementCount;     // number of elements in this uniform
    EShaderParameterType   m_parameterType;    // parameter type;

#if defined(THOT_ENABLE_DEBUG_TOOLS)
    u32                         m_nativeParameterTypeID;
    CString                     m_nativeTypeString;
#endif

};



#endif //__RENDER_SHADER_PRIVATE_DATA_H__