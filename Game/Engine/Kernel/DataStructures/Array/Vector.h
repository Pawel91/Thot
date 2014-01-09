#if !defined(__KERNEL_VECTOR_H__)
#define __KERNEL_VECTOR_H__

#include "Kernel/Basics.h"
#include "Kernel/DataStructures/ContainerBase.h"
#include "Kernel/MetaTemplates/ObjectConstructionPolicy.h"
#include "Kernel/DataStructures/Array/VectorHelpers.h"
#include "Kernel/MemoryManagement/Allocator.h"
#include "Kernel/KernelUtils.h"


//#define THOT_ENABLE_VECTOR_DEBUG

#if defined(THOT_ENABLE_VECTOR_DEBUG)
#   include "Kernel/Time/Timer.h"
#   include "Kernel/Profiler/Profiler.h"
#endif

#define VECTOR_TEMPLATE_ARGS class T, class Allocator, class ResizePolicy
#define VECTOR_TEMPLATE_ARGS_NO_TYPE  T, Allocator, ResizePolicy


struct KERNEL_API SVectorProperties // export vector properties so we can make export a template class
{
    SVectorProperties();

    void Reset();

    u64 m_size;
    u64 m_capacity;
};


template<class T>
class thVectorBase: public CContainer<T>
{
protected:
    SVectorProperties     m_properties;
};


template<class T, class Allocator = CSmartAllocator, class ResizePolicy = VectorResizePolicy<T>>
class thVector: public thVectorBase<T>
{
public:

    typedef thVector<T, Allocator, ResizePolicy>    TSelf;
    typedef T                                       TElement;
    typedef T*                                      TPtrElement;
    typedef const T*                                TConstPtrElement;
    typedef T&                                      TRefElement;
    typedef const T&                                TConstRefElement;
    typedef TPtrElement                             Iterator;
    typedef TConstPtrElement                        ConstIterator;
    typedef u64                                     TSize;
    typedef MetaTemplates::CTypeTraits<T>           TypeTraits;
    typedef ObjectConstructionPolicy<T>             Helpers;

private:
    //copy not allowed
    thVector( const TSelf& other)
        : m_allocator   ( this )
    {
        THOT_ASSERT(false);
    }

    const TSelf& operator == ( const TSelf& other ){ THOT_ASSERT(false); return *this;}
public:
     thVector();
    ~thVector();

    TSize                   Size                ( )const    { return m_properties.m_size;}
    TSize                   Capacity            ( )const    { return m_properties.m_capacity;}
    Bool                    IsEmpty             ( )const    { return m_properties.m_size == 0;}
    TPtrElement             GetData             ( )         { return m_array;}
    TConstPtrElement        GetData             ( )const    { return m_array;}

    Iterator                End                 ( );
    Iterator                Begin               ( );
    ConstIterator           End                 ( )const;
    ConstIterator           Begin               ( )const;

    void                    StoleData           ( TSelf& other );
    void                    Resize              ( TSize newSize );
    void                    Clear               ( );
    void                    Erase               ( Iterator first, Iterator last );
    void                    Erase               ( Iterator element );
    void                    PopBack             ( );
    TSize                   PushBack            ( TConstRefElement element );
    void                    PushBackArray       ( T* array, TSize size);
    void                    Reserve             ( TSize size );
    void                    ShrinkToFit         ( );

    TRefElement             operator []         ( TSize index );
    TConstRefElement        operator []         ( TSize index )const;


//*****************************************************************************
//                  HELPER STRUCTS
//*****************************************************************************
private:



//*****************************************************************************
//                  HELPER FUNCTIONS
//*****************************************************************************
private:
    
    void        ResizeTo    ( TSize newSize, TSize newCapacity );   // internal function called only by resize; [TODO] make a base vector and make this function private and Resize protected ;)

private:
    T*              m_array;
    Allocator       m_allocator;

};

//--------------------------------------------------------------------------------
template<VECTOR_TEMPLATE_ARGS>
thVector<VECTOR_TEMPLATE_ARGS_NO_TYPE>::thVector()
    : m_array       ( NULL )
    , m_allocator   ( this )
{
}

//--------------------------------------------------------------------------------
template<VECTOR_TEMPLATE_ARGS>
thVector<VECTOR_TEMPLATE_ARGS_NO_TYPE>::~thVector()
{
    if(m_array)
    {
        Helpers::DestroyElements( m_array, 0, m_properties.m_size );
        m_allocator.FreeAlign(m_array);
        m_array = NULL;
    }
}

//--------------------------------------------------------------------------------
template<VECTOR_TEMPLATE_ARGS>
typename thVector<VECTOR_TEMPLATE_ARGS_NO_TYPE>::TRefElement thVector<VECTOR_TEMPLATE_ARGS_NO_TYPE>::operator[]( typename thVector<VECTOR_TEMPLATE_ARGS_NO_TYPE>::TSize index )
{
    THOT_ASSERT( index < m_properties.m_size && m_properties.m_size <= m_properties.m_capacity, "VECTOR OUT OF BOUNDS" );
    return m_array[index];
}

//--------------------------------------------------------------------------------
template<VECTOR_TEMPLATE_ARGS>
typename thVector<VECTOR_TEMPLATE_ARGS_NO_TYPE>::TConstRefElement thVector<VECTOR_TEMPLATE_ARGS_NO_TYPE>::operator[]( typename thVector<VECTOR_TEMPLATE_ARGS_NO_TYPE>::TSize index )const
{
    THOT_ASSERT( index < m_properties.m_size && m_properties.m_size <= m_properties.m_capacity, "VECTOR OUT OF BOUNDS" );
    return m_array[index];
}

//--------------------------------------------------------------------------------
template<VECTOR_TEMPLATE_ARGS>
void thVector<VECTOR_TEMPLATE_ARGS_NO_TYPE>::Reserve( typename thVector<VECTOR_TEMPLATE_ARGS_NO_TYPE>::TSize size )
{
    if( size > m_properties.m_size )
    {
        ResizeTo( m_properties.m_size, size );
    }
}

//--------------------------------------------------------------------------------
template<VECTOR_TEMPLATE_ARGS>
void thVector<VECTOR_TEMPLATE_ARGS_NO_TYPE>::ShrinkToFit ( )
{
    if( m_properties.m_capacity > m_properties.m_size )
    {
        ResizeTo( m_properties.m_size, m_properties.m_size );
    }
}

//--------------------------------------------------------------------------------
template<VECTOR_TEMPLATE_ARGS>
void thVector<VECTOR_TEMPLATE_ARGS_NO_TYPE>::Resize ( TSize newSize )
{
    if( ResizePolicy::NeedResize( m_properties.m_size, m_properties.m_capacity, newSize ) )
    {
        // the resize policy wants the vector to be ACTUALLY resized;
        TSize newCapacity = ResizePolicy::RequestNewCapacity( m_properties.m_size, m_properties.m_capacity, newSize ); 
        THOT_ASSERT(newCapacity >= newSize);
        ResizeTo( newSize, newCapacity );
    }
    else
    {
        //THOT_ASSERT( newSize > m_properties.m_capacity, "RESIZE POLICY FAILED");

        // if shrink
        if( newSize < m_properties.m_size )
        {
            Helpers::DestroyElements( m_array, newSize, m_properties.m_size );
        }

        m_properties.m_size = newSize;
    }

    THOT_ASSERT( m_properties.m_size <= m_properties.m_capacity, "VECTOR CAPACITY MUST BE GREATER THEN THE SIZE" );
}

//--------------------------------------------------------------------------------
template<VECTOR_TEMPLATE_ARGS>
void thVector<VECTOR_TEMPLATE_ARGS_NO_TYPE>::Clear( )
{
    if(m_properties.m_size)
    {
        Helpers::DestroyElements( m_array, 0, m_properties.m_size );
        m_properties.m_size = 0;
    }
}

//--------------------------------------------------------------------------------
template<VECTOR_TEMPLATE_ARGS>
void thVector<VECTOR_TEMPLATE_ARGS_NO_TYPE>::ResizeTo( TSize newSize, TSize newCapacity )
{
    THOT_ASSERT( newCapacity > 0);

    //DECLARE_PROFILE_SCOPED("thVector<VECTOR_TEMPLATE_ARGS_NO_TYPE>::ResizeTo");

    T* newBuffer = NULL;
    if(newCapacity)
    {
        //DECLARE_PROFILE_SCOPED("thVector::ResizeTo: Allocate buffer");
        // allocate raw memory; we will construct latter
        newBuffer = reinterpret_cast<T*>( m_allocator.AllocAlign( ThNumericCast<unsigned int>( newCapacity * sizeof(T) ), __alignof(T) ) );
    }

    if(m_array)
    {
        //DECLARE_PROFILE_SCOPED("thVector::ResizeTo: Copy elements and destroy older");
        // copy the element that will be used;
        TSize toCopyCount = ThMin<TSize>( m_properties.m_size, newSize );

        if(toCopyCount)
        {
            //DECLARE_PROFILE_SCOPED("thVector::ResizeTo: Helpers::ConstructFromOther");
            Helpers::ConstructFromOther( m_array, newBuffer, toCopyCount );
        }

        {
            

            {
                //DECLARE_PROFILE_SCOPED("thVector::ResizeTo: Destroy old data");
                //destroy old data;
                Helpers::DestroyElements(m_array, 0, m_properties.m_size);
            }

            {
                //DECLARE_PROFILE_SCOPED_HIT_INFO("thVector::ResizeTo: Free old buffer", "bufferSize = [%d]", m_properties.m_size );
                m_allocator.FreeAlign( m_array ); // free old array;
                m_array = NULL;
            }
        }
    }

    //update vector data;
    m_properties.m_capacity = newCapacity;
    m_properties.m_size = newSize;
    m_array = newBuffer;
}

//--------------------------------------------------------------------------------
template<VECTOR_TEMPLATE_ARGS>
typename thVector<VECTOR_TEMPLATE_ARGS_NO_TYPE>::Iterator thVector<VECTOR_TEMPLATE_ARGS_NO_TYPE>::End( )
{
    return m_array + m_properties.m_size;
}

//--------------------------------------------------------------------------------
template<VECTOR_TEMPLATE_ARGS>
typename thVector<VECTOR_TEMPLATE_ARGS_NO_TYPE>::Iterator thVector<VECTOR_TEMPLATE_ARGS_NO_TYPE>::Begin( )
{
    return m_array;
}

//--------------------------------------------------------------------------------
template<VECTOR_TEMPLATE_ARGS>
typename thVector<VECTOR_TEMPLATE_ARGS_NO_TYPE>::ConstIterator thVector<VECTOR_TEMPLATE_ARGS_NO_TYPE>::End( )const
{
    return m_array + m_properties.m_size;
}

//--------------------------------------------------------------------------------
template<VECTOR_TEMPLATE_ARGS>
typename thVector<VECTOR_TEMPLATE_ARGS_NO_TYPE>::ConstIterator thVector<VECTOR_TEMPLATE_ARGS_NO_TYPE>::Begin( )const
{
    return m_array;
}

//--------------------------------------------------------------------------------
template<VECTOR_TEMPLATE_ARGS>
typename thVector<VECTOR_TEMPLATE_ARGS_NO_TYPE>::TSize thVector<VECTOR_TEMPLATE_ARGS_NO_TYPE>::PushBack( TConstRefElement element )
{
    Resize( m_properties.m_size + 1 );
    //does not call destructor of the last element and it does not have to because there is a raw memory;
    Helpers::ConstructFromOtherSingle( m_array[ m_properties.m_size-1], element );
    return m_properties.m_size -1;
}

//--------------------------------------------------------------------------------
template<VECTOR_TEMPLATE_ARGS>
void thVector<VECTOR_TEMPLATE_ARGS_NO_TYPE>::PopBack( )
{
    THOT_ASSERT( m_properties.m_size, "VECTOR IS EMPTY; CANNOT POP ANYMORE" );
    Resize( m_properties.m_size - 1); 
}

//--------------------------------------------------------------------------------
template<VECTOR_TEMPLATE_ARGS>
void thVector<VECTOR_TEMPLATE_ARGS_NO_TYPE>::Erase( Iterator first, Iterator last )
{
    THOT_ASSERT( first >= Begin() && first < End() && last>=Begin() && last<End(), "ITERATORS OUT OF BOUNDS" );

    u64 elementCount = last - first + 1;
    Helpers::DestroyElements( first, 0, elementCount );

    u64 toCopyCount = End() - last - 1;
    if( toCopyCount )
    {
        T* copySource = last + 1 ;
        T* copyDestination = first;
        for( u64 i=0; i< toCopyCount; i++ )
        {
            Helpers::ConstructFromOtherSingle( copyDestination[i], copySource[i] ); // construct because we copy to raw memory
            Helpers::DestroyElement( copySource[i] ); // destroy the source element after copy
        }
    }

    m_properties.m_size -= elementCount;
}

//--------------------------------------------------------------------------------
template<VECTOR_TEMPLATE_ARGS>
void thVector<VECTOR_TEMPLATE_ARGS_NO_TYPE>::Erase( Iterator element )
{
    Erase( element, element );
}

//--------------------------------------------------------------------------------
template<VECTOR_TEMPLATE_ARGS>
void thVector<VECTOR_TEMPLATE_ARGS_NO_TYPE>::PushBackArray( T* array, TSize size)
{
    for( TSize i=0; i<size; i++ )
    {
        PushBack( *(array + i) );
    }
}

//--------------------------------------------------------------------------------
template<VECTOR_TEMPLATE_ARGS>
void thVector<VECTOR_TEMPLATE_ARGS_NO_TYPE>::StoleData( TSelf& other )
{
    Clear();
    m_properties = other.m_properties;
    m_array = other.m_array;
    other.m_properties.Reset();
}

//--------------------------------------------------------------------------------


#undef VECTOR_TEMPLATE_ARGS
#undef VECTOR_TEMPLATE_ARGS_NO_TYPE

THOT_DECLARE_TEMPLATE_API(KERNEL_TEMPLATE_API, thVector<int>);
THOT_DECLARE_TEMPLATE_API(KERNEL_TEMPLATE_API, thVector<u32>);
THOT_DECLARE_TEMPLATE_API(KERNEL_TEMPLATE_API, thVector<s32>);
THOT_DECLARE_TEMPLATE_API(KERNEL_TEMPLATE_API, thVector<u64>);
THOT_DECLARE_TEMPLATE_API(KERNEL_TEMPLATE_API, thVector<s64>);



#endif //__KERNEL_VECTOR_H__