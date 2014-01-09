#if !defined(__KERNEL_META_INTRINSICS_H__)
#define __KERNEL_META_INTRINSICS_H__

#include "Kernel/Basics.h"

#if defined(THOT_COMPILER_MICROSOFT) && (THOT_COMPILER_MICROSOFT >= THOT_MICROSOFT_VISUAL_STUDIO2010)

namespace MetaTemplates
{
    //forward declare CTypeTraits so we can declare it as friend class;
    template<class T>
    class CTypeTraits;

    namespace Intrinsics
    {
        template<class T>
        class CTypeTraits
        {
        template<class T> friend class MetaTemplates::CTypeTraits;

        // DO NOT USE DIRECTLY
        private:
            struct Properties
            {
                enum
                {
                    isAbstract              = __is_abstract(T),
                    isEmpty                 = __is_empty(T),
                    isEnum                  = __is_enum(T),
                    isPOD                   = __is_pod(T),
                    isPolymorphic           = __is_polymorphic(T),
                    isUnion                 = __is_union(T)
                };
            };

            struct Trivial
            {
                enum
                {
                    hasConstructor          = __has_trivial_constructor(T),
                    hasDestructor           = __has_trivial_destructor(T),
                    hasAssign               = __has_trivial_assign(T),
                    hasCopy                 = __has_trivial_copy(T)
                };
            };

            struct UserDefined
            {
                enum
                {

                    hasDestructor           = __has_user_destructor(T),
                    hasAssign               = __has_assign(T),
                    hasCopy                 = __has_copy(T),
                    hasVirtualDestructor    = __has_virtual_destructor(T)
                };
            };
        };
    
    } // namespace Intrinsics

} // namespace MetaTemplates




#else
#   error UNKNOWN COMPILER
#endif




#endif //__KERNEL_META_INTRINSICS_H__