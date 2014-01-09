#if !defined(__KERNEL_OBJECT_CONSTRUCT_POLICY_H__)
#define __KERNEL_OBJECT_CONSTRUCT_POLICY_H__

#include "Kernel/Basics.h"
#include "Kernel/MetaTemplates/MetaTemplates.h"
#include "Kernel/Memory/Memory.h"

//--------------------------------------------------------------------------------
namespace __detail
{
    //--------------------------------------------------------------------------------
    // forward declare templates
    template<class T, bool hasCopyConstructor >
    class CopyConstrHelpers;

    template<class T, bool hasDestructor  >
    class DestructorHelpers;
    
    template<class T, bool hasConstructor >
    class ConstructorHelpers;

    //--------------------------------------------------------------------------------
    template<class T>
    class ConstructorHelpers<T, true>
    {
    public:
        static THOT_FORCE_INLINE void DefaultConstruct(T* elements, size_t size)
        {
            // call array placement new
            for( size_t i=0; i<size;i++ )
            {
                new( & elements[i] ) T();
            }
        }

        static THOT_FORCE_INLINE void DefaultConstructSingle( T* element)
        {
            new(element) T();
        }
    };

    //--------------------------------------------------------------------------------
    template<class T>
    class ConstructorHelpers<T, false>
    {
    public:
        static THOT_FORCE_INLINE void DefaultConstruct(T* elements, size_t size)
        {
            
#if defined(THOT_ENABLE_DEBUG)
            // memset to 0;
            Memory::Set( elements, size * sizeof(T), 0);
#endif
        }

        static THOT_FORCE_INLINE void DefaultConstructSingle( T* element )
        {
#if defined(THOT_ENABLE_DEBUG)
            Memory::Set( element, sizeof(T), 0 );
#endif
        }
    };

    //--------------------------------------------------------------------------------
    template<class T>
    class CopyConstrHelpers<T, true>
    {
    public:

        static THOT_FORCE_INLINE void ConstructFromOther( const T* source, T* destination, size_t size )
        {
            // we have raw memory in destination; we don`t call destructor
            for( size_t i=0; i<size; i++)
            {
                //call copy constructor
                new( destination + i) T(source[i]);
            }
        }

        static THOT_FORCE_INLINE void ConstructFromOtherSingle( T& element, const T& source)
        {
            // we have raw memory in element; we don`t call destructor
            new(&element) T(source);
        }

        static THOT_FORCE_INLINE void CopyElements( const T* source, T* destination, size_t size )
        {
            // destroy old before copy;
            DestructorHelpers<T>::DestroyElements( destination, 0, size );
            ConstructFromOther( source, destination, size );
        }

        static THOT_FORCE_INLINE void CopySingle( T& element, const T& source )
        {
            // destroy element and then copy the new value
            DestructorHelpers<T>::DestroyElements( &element, 0, 1 );
            ConstructFromOtherSingle( element, source );
        }
    };
    
    //--------------------------------------------------------------------------------
    template<class T>
    class CopyConstrHelpers<T, false>
    {
    public:
    
        static THOT_FORCE_INLINE void ConstructFromOther( const T* source, T* destination, size_t size )
        {
            Memory::Copy( destination, source, size * sizeof(T) );
        }

        static THOT_FORCE_INLINE void ConstructFromOtherSingle( T& element, const T& source)
        {
            Memory::Copy( &element, &source, sizeof(T) );
        }

        static THOT_FORCE_INLINE void CopyElements( const T* source, T* destination, size_t size )
        {
            //memcpy because we don`t have copy constructor
            Memory::Copy( destination, source, size * sizeof(T) );
        }

        static THOT_FORCE_INLINE void CopySingle( T& element, const T& source )
        {
            Memory::Copy( &element, &source, sizeof(T) );
        }
    };

    //--------------------------------------------------------------------------------
    template<class T >
    class DestructorHelpers< T, false >
    {
    public:

        static THOT_FORCE_INLINE void DestroyElement( T& element)
        {
            // nothing
        }

        static THOT_FORCE_INLINE void DestroyElements( T* array, size_t begin, size_t range )
        {
            //does nothing
        }
    };

    //--------------------------------------------------------------------------------
    template<class T >
    class DestructorHelpers< T, true >
    {
    public:
        static THOT_FORCE_INLINE void DestroyElement( T& element)
        {
            // call the destructor
            (&element)->~T();
        }

        static THOT_FORCE_INLINE void DestroyElements( T* array, size_t begin, size_t size )
        {
            for( size_t i=begin; i<size; i++ )
            {
                //call destructor
                (array +i)->~T();
            }
        }
    };

} //namespace __detail 


//--------------------------------------------------------------------------------

template<class T>
class ObjectConstructionPolicy:
     public __detail::CopyConstrHelpers<T, !MetaTemplates::CTypeTraits<T>::CanIgnore::CopyConstructor >
    ,public __detail::DestructorHelpers<T, !MetaTemplates::CTypeTraits<T>::CanIgnore::Destructor >
    ,public __detail::ConstructorHelpers<T, !MetaTemplates::CTypeTraits<T>::CanIgnore::Constructor>
{
public:
};
//--------------------------------------------------------------------------------




#endif //__KERNEL_OBJECT_CONSTRUCT_POLICY_H__