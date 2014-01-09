#if !defined __RENDER_SHADER_PARAMETER_PROVIDER_TYPES_H__
#define __RENDER_SHADER_PARAMETER_PROVIDER_TYPES_H__

// when create a new shader provider class you must increment this value; sorry for that,
// but it helps to save some memory if we know the count at compile-time rather then at run-time.
// if you forgot to increment a run-time assert will be triggered before entering main function;
const u16       SHADER_PARAMETER_PROVIDER_COUNT = 4;

class IShaderParameterProvider;
class CShaderParameterProviderDescriptor;
typedef void (*TCreateParameterMapFunction)();
typedef u16     ParameterProviderType;


                                                        
                                                        





#endif