#ifndef __KERNEL_DEFINES_H__
#define __KERNEL_DEFINES_H__

#include "Kernel/Basics.h"


#define FORCE_DWORD                 0x7FFFFFFF 
#define THOT_ARRAY_SIZE(array)      (sizeof(array)/( sizeof((array)[0]) ))
#define THOT_STRINGIFY(arg)         (#arg)
#define KB(__kilos)                 (__kilos * 1024)
#define MB(__megas)                 (__megas * 1024 * 1024)


#define STRINGIZE_HELPER(x) #x
#define STRINGIZE(x) STRINGIZE_HELPER(x)
#define __MESSAGE(text) __pragma( message(__FILE__ "(" STRINGIZE(__LINE__) ")" text) ) 
#define THOT_WARNING(text) __MESSAGE( " : Warning: " #text )
#define THOT_ERROR(text) __MESSAGE( " : Error: " #text )
#define THOT_TODO(text) __MESSAGE( " : Warning: [TODO]: (" __FUNCTION__ ") " #text )

#define THOT_MEMBER_OFFSET(_class,_member)   ( (unsigned int) ( &(((_class*)0)->_member) ) ) 

#define IS_UPPER(l)                     (  ( (l)>='A' && (l)<='Z' )? true:false )
#define IS_LOWER(l)                     (  ( (l)>='a' && (l)<='z' )? true:false )
#define IS_LETTER(l)                    ( ( IS_LOWER(l) || IS_UPPER(l) )? true:false )
#define TO_UPPER(l)                     ( (l) - 'a' + 'A' ) // use only when you really know that is a lower letter
#define TO_LOWER(l)                     ( (l) - 'A' + 'a' ) // use only when you really know that is a upper letter
#define S_TO_UPPER(l)                   (  (IS_LOWER(l))?TO_UPPER(l):(l) ) // safe way to make toUpper
#define S_TO_LOWER(l)                   (  (IS_UPPER(l))?TO_LOWER(l):(l) ) // safe way to make toLowees

#define THOT_INLINE             inline

#ifdef THOT_ENABLE_EXTERN_TEMPLATE
#   define THOT_EXTERN_TEMPLATE extern template
#else
#   define THOT_EXTERN_TEMPLATE template
#endif 

#define THOT_DECLARE_TEMPLATE_API( __API_TEMPLATE_SPEC, ... ) __API_TEMPLATE_SPEC __VA_ARGS__;
#define THOT_DECLARE_NOCOPY_CLASS(__className)       \
    private:                                    \
    __className(const __className& other){THOT_ASSERT(false, "THOT_DECLARE_NOCOPY_CLASS");}    \
    const __className& operator = (const __className& other) {THOT_ASSERT(false, "THOT_DECLARE_NOCOPY_CLASS");return *this;}


template<typename CLASS, size_t SIZE> 
class  PrintSizeAsWarningHelperClass;//{ public: operator char() { return SIZE + 256; } }; 


#define THOT_COMPILE_PRINT_CLASS_SIZE_AS_ERROR(__class) \
template<>                                                  \
class  PrintSizeAsWarningHelperClass<__class, sizeof(__class)> \
{                                                                                       \
    public: operator char()                                                             \
    {                                                                                   \
        return PrintSizeAsWarningHelperClass<__class, sizeof(__class)>::__forceError;   \
    }                                                                                   \
};
//#endif



#endif /*__KERNEL_DEFINES_H__*/