#if !defined(__RENDER_SHADER_PARAMETER_TYPES_H__)
#define __RENDER_SHADER_PARAMETER_TYPES_H__

enum  EShaderParameterType
{
    None = -1,
    Float,
    Double,
    UnsignedInt32,
    SignedInt32,
    Mat4,
    Mat3,
    Vec3,
    Vec4,
    Texture,

    Count
};

#endif //__RENDER_SHADER_PARAMETER_TYPES_H__