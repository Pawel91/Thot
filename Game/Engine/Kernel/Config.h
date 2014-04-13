#if !defined(__KERNEL_CONFIG_H__)
#define __KERNEL_CONFIG_H__


#define THOT_ENABLE_DEBUG

#if defined(THOT_ENABLE_DEBUG)

#   define THOT_ENABLE_DEBUG_TOOLS
#   define THOT_ENABLE_TRACING
#   define THOT_ENABLE_ASSERT 
#   define THOT_MEM_ENABLE_DEBUG
#   define THOT_PROFILER_ENABLE

#endif //THOT_ENABLE_DEBUG






#endif //__KERNEL_CONFIG_H__