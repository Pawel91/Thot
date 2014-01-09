#if !defined(__KERNEL_TYPE_TRAITS_H__)
#define __KERNEL_TYPE_TRAITS_H__

#include "Kernel/DataTypes.h"
#include "TypeTraits_intrinsics.h"

namespace MetaTemplates
{
    //TEMP HACK [TODO] to remove
    namespace __detail
    {
        template<class T>
        struct isFundamental
        {
           static void f()
            {
                int a =0 ; a++;
            }

            enum 
            {
                value = false
            };
        };

        //pointers are fundamental types;
        template<class T>
        struct isFundamental<T*>
        {
           static void f()
            {
                int a =0 ; a++;
            }
            enum 
            {
                value = true
            };
        };

#define __DECLARE_FUNDAMENTAL_TYPE(__type)\
        template<>              \
        struct isFundamental<__type>           \
        {                       \
            enum                \
            {                   \
                value = true    \
            };                  \
        };

        __DECLARE_FUNDAMENTAL_TYPE(bool);
        __DECLARE_FUNDAMENTAL_TYPE(char);
        __DECLARE_FUNDAMENTAL_TYPE( unsigned char);
        __DECLARE_FUNDAMENTAL_TYPE(int);
        __DECLARE_FUNDAMENTAL_TYPE(unsigned int);
        __DECLARE_FUNDAMENTAL_TYPE(short int);
        __DECLARE_FUNDAMENTAL_TYPE(unsigned short int);
        __DECLARE_FUNDAMENTAL_TYPE(long);
        __DECLARE_FUNDAMENTAL_TYPE( unsigned long);
        __DECLARE_FUNDAMENTAL_TYPE( float);
        __DECLARE_FUNDAMENTAL_TYPE( double);
        __DECLARE_FUNDAMENTAL_TYPE( long double);
        //__DECLARE_FUNDAMENTAL_TYPE(u8);
        //__DECLARE_FUNDAMENTAL_TYPE(s8);
        //__DECLARE_FUNDAMENTAL_TYPE(u16);
        //__DECLARE_FUNDAMENTAL_TYPE(s16);
        //__DECLARE_FUNDAMENTAL_TYPE(u32);
        //__DECLARE_FUNDAMENTAL_TYPE(s32);
        __DECLARE_FUNDAMENTAL_TYPE(u64);
        __DECLARE_FUNDAMENTAL_TYPE(s64);
    }
    

    template<class T>
    class CTypeTraits
    {
    public:

        struct Properties
        {
            enum
            {
                isAbstract              = MetaTemplates::Intrinsics::CTypeTraits<T>::Properties::isAbstract,
                isEmpty                 = MetaTemplates::Intrinsics::CTypeTraits<T>::Properties::isEmpty,
                isEnum                  = MetaTemplates::Intrinsics::CTypeTraits<T>::Properties::isEnum,
                isPOD                   = MetaTemplates::Intrinsics::CTypeTraits<T>::Properties::isPOD,
                isPolymorphic           = MetaTemplates::Intrinsics::CTypeTraits<T>::Properties::isPolymorphic,
                isUnion                 = MetaTemplates::Intrinsics::CTypeTraits<T>::Properties::isUnion,
                isFundamental           = __detail::isFundamental<T>::value,
                //alignment               = isAbstract?0:__alignof(T),
                size                    = sizeof(T) 
            };

            template<class DERIVED> class isBaseOf { enum    { value = __is_base_of(T, DERIVED)    };  };
        };

        struct Trivial
        {
            enum
            {
                hasConstructor          =  MetaTemplates::Intrinsics::CTypeTraits<T>::Trivial::hasConstructor,
                hasDestructor           =  MetaTemplates::Intrinsics::CTypeTraits<T>::Trivial::hasDestructor,
                hasAssign               =  MetaTemplates::Intrinsics::CTypeTraits<T>::Trivial::hasAssign,
                hasCopy                 =  MetaTemplates::Intrinsics::CTypeTraits<T>::Trivial::hasCopy
            };
        };

        struct UserDefined
        {
            enum
            {
                hasConstructor          = !Trivial::hasConstructor && !Properties::isEnum && !Properties::isFundamental && !Properties::isPOD,
                hasDestructor           = MetaTemplates::Intrinsics::CTypeTraits<T>::UserDefined::hasDestructor,
                hasAssign               = MetaTemplates::Intrinsics::CTypeTraits<T>::UserDefined::hasAssign,
                hasCopy                 = MetaTemplates::Intrinsics::CTypeTraits<T>::UserDefined::hasCopy,
                hasVirtualDestructor    = MetaTemplates::Intrinsics::CTypeTraits<T>::UserDefined::hasVirtualDestructor
            };

        };

        struct CanIgnore
        {
            enum
            {
                Constructor             = Trivial::hasConstructor || Properties::isEnum || Properties::isFundamental || Properties::isPOD,
                Destructor              = Trivial::hasDestructor || Properties::isEnum || Properties::isFundamental || Properties::isPOD,
                CopyConstructor         = Trivial::hasCopy || Properties::isEnum || Properties::isFundamental || Properties::isPOD
            };
        };
    };

}//namespace MetaTemplates


#endif //__KERNEL_TYPE_TRAITS_H__