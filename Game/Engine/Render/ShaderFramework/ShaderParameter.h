#pragma once
#ifndef __RENDER_SHADER_PARAMETER_H__
#define __RENDER_SHADER_PARAMETER_H__

#include "Render/GLWrapper/OpenGL.h"
#include "Kernel/DataStructures/CString.h"

#include "Render/ShaderFramework/ShaderParameterTypes.h"
#include "Render/ShaderFramework/ShaderParameterTraits.h"

#if defined THOT_ENABLE_DEBUG_TOOLS
#   define THOT_ENABLE_SHADER_PARAM_STORE_DEBUG_NAME
#endif

class CShaderUniform;

class RENDER_API IShaderParameter
{
public:
    IShaderParameter()
    {
    }

    virtual             ~IShaderParameter(){}
    
    virtual void        SetParameterShaderData  ( u32 uniformLocation )  = 0;

};

template< typename TYPE, u32 SIZE >
class RENDER_API CShaderParameterTemplateBase: public IShaderParameter
{
public:
    TYPE& operator[] ( u32 index );
    const TYPE& operator[] ( u32 index )const;

    THOT_FORCE_INLINE u64         GetSize(){ return SIZE;}

    static const u32      ms_parameterType = CShaderParameterTraits<TYPE>::ms_parameterType;

protected:
    TYPE  m_data[SIZE];
};


template< typename TYPE >
class RENDER_API CShaderParameterTemplateBase< TYPE, 1>: public IShaderParameter
{
public:

    operator const TYPE& ()const;
    operator TYPE& ();

    static const u32      ms_parameterType = CShaderParameterTraits<TYPE>::ms_parameterType;

protected:
    TYPE  m_data;
};


template<typename TYPE, u32 SIZE=1>
class CShaderParameter
{
public:
    CShaderParameter()
    {
        THOT_COMPILE_ASSERT2(false, "CShaderParameter must be specialized. Cannot use default implementation");
    }
    ~CShaderParameter()
    {
        THOT_COMPILE_ASSERT2(false, "CShaderParameter must be specialized. Cannot use default implementation");
    }
};




#if defined(RENDER_EXPORTS) // to avoid "definition of dllimport function not allowed" error
#   include "ShaderParameter.inl"
#endif

#endif