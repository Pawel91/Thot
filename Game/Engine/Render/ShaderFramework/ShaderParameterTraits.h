#if !defined (__RENDER_SHADER_PARAMETER_TRAITS_H__)
#define __RENDER_SHADER_PARAMETER_TRAITS_H__

#include "Render/ShaderFramework/ShaderParameterTypes.h"

#include "Render/Textures/Texture.h"
#include "Render/Color.h"

template<class TYPE_PARAMETER>
class CShaderParameterTraits;

//--------------------------------------------------------------------------------
template<>
class CShaderParameterTraits<m4x4>
{
public:

    static const u32        ms_parameterType = EShaderParameterType::Mat4;
};

//--------------------------------------------------------------------------------
template<>
class CShaderParameterTraits<m3x3>
{
public:

    static const u32        ms_parameterType = EShaderParameterType::Mat3;
};

//--------------------------------------------------------------------------------
template<>
class CShaderParameterTraits<float>
{
public:

    static const u32        ms_parameterType = EShaderParameterType::Float;
};

//--------------------------------------------------------------------------------
template<>
class CShaderParameterTraits<tVect3>
{
public:

    static const u32        ms_parameterType = EShaderParameterType::Vec3;
};

//--------------------------------------------------------------------------------
template<>
class CShaderParameterTraits<u32>
{
public:

    static const u32        ms_parameterType = EShaderParameterType::UnsignedInt32;
};

//--------------------------------------------------------------------------------
template<>
class CShaderParameterTraits<s32>
{
public:

    static const u32        ms_parameterType = EShaderParameterType::SignedInt32;
};

//--------------------------------------------------------------------------------
template<>
class CShaderParameterTraits<CColor>
{
public:
    static const u32        ms_parameterType = EShaderParameterType::Vec4;
};

//--------------------------------------------------------------------------------
template<>
class CShaderParameterTraits<CTexture>
{
public:
    static const u32        ms_parameterType = EShaderParameterType::Texture;
};

//--------------------------------------------------------------------------------

#endif //__RENDER_SHADER_PARAMETER_TRAITS_H__