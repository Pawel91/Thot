#if !defined(__KERNEL_VECTOR_HELPERS_H__)
#define __KERNEL_VECTOR_HELPERS_H__

#include "Kernel/Basics.h"
#include "Kernel/MetaTemplates/MetaTemplates.h"
#include "Kernel/Memory/Memory.h"

//--------------------------------------------------------------------------------
template< class T >
class VectorResizePolicy
{
    //[TODO] make private and friend with vector;
public:
    static THOT_FORCE_INLINE bool        NeedResize          ( size_t oldSize, size_t oldCapacity, size_t newNeededSize );
    static THOT_FORCE_INLINE size_t      RequestNewCapacity  ( size_t oldSize, size_t oldCapacity, size_t newNeededSize );
};

//--------------------------------------------------------------------------------
template<class T>
THOT_FORCE_INLINE bool VectorResizePolicy<T>::NeedResize( size_t oldSize, size_t oldCapacity, size_t newNeededSize )
{
    if( newNeededSize > oldCapacity )
    {
        return true;
    }

    return false;
}

//--------------------------------------------------------------------------------
template<class T>
THOT_FORCE_INLINE size_t VectorResizePolicy<T>::RequestNewCapacity( size_t oldSize, size_t oldCapacity, size_t newNeededSize )
{
    THOT_ASSERT( newNeededSize > oldSize);
    if(oldCapacity)
    {
        return oldCapacity + oldCapacity/2; // exponential grow;
    }

    // first in vector we have 4 elements
    return ThMax<size_t>( 4, newNeededSize  );
}

#endif //__KERNEL_VECTOR_HELPERS_H__