#include "Kernel/MetaTemplates/ObjectConstructionPolicy.h"

//--------------------------------------------------------------------------------
template<class T>
THOT_FORCE_INLINE CStlAllocator<T>::CStlAllocator()
{
}

//--------------------------------------------------------------------------------
template<class T>
THOT_FORCE_INLINE CStlAllocator<T>::CStlAllocator( const CStlAllocator<T>& other )
{
}

//--------------------------------------------------------------------------------
template<class T> template<class U>
THOT_FORCE_INLINE CStlAllocator<T>::CStlAllocator( const CStlAllocator<U>& other )
{
}

//--------------------------------------------------------------------------------
template<class T>
THOT_FORCE_INLINE CStlAllocator<T>::~CStlAllocator( )
{
}

//--------------------------------------------------------------------------------
template<class T>
THOT_FORCE_INLINE typename CStlAllocator<T>::pointer CStlAllocator<T>::allocate( size_type size, const_pointer )
{
    pointer _ptr = (pointer) THOT_MALLOC( size * sizeof(T) );
    return _ptr;
}

//--------------------------------------------------------------------------------
template<class T>
THOT_FORCE_INLINE void  CStlAllocator<T>::deallocate  ( pointer p, size_type )
{
    THOT_FREE(p);
}

//--------------------------------------------------------------------------------
template<class T>
THOT_FORCE_INLINE void CStlAllocator<T>::construct( pointer p, const T& other )
{
    //new(p) T(other);
    ObjectConstructionPolicy<T>::ConstructFromOtherSingle( *p, other );
}

//--------------------------------------------------------------------------------
template<class T>
THOT_FORCE_INLINE typename CStlAllocator<T>::pointer CStlAllocator<T>::address( reference r )
{
    return &r;
}

//--------------------------------------------------------------------------------
template<class T>
THOT_FORCE_INLINE typename CStlAllocator<T>::const_pointer CStlAllocator<T>::address( const_reference r)
{
    return &r;
}

//--------------------------------------------------------------------------------
template<class T>
THOT_FORCE_INLINE typename CStlAllocator<T>::size_type CStlAllocator<T>::max_size( )
{
    return size_t(-1)/ sizeof(T);
}

//--------------------------------------------------------------------------------
template<class T>
THOT_FORCE_INLINE void CStlAllocator<T>::destroy( pointer p)
{
    ObjectConstructionPolicy<T>::DestroyElement( *p );
}

//--------------------------------------------------------------------------------
template<class T>
THOT_FORCE_INLINE bool  CStlAllocator<T>::operator == ( const CStlAllocator& other)
{
    return true;
}

//--------------------------------------------------------------------------------
template<class T>
THOT_FORCE_INLINE bool  CStlAllocator<T>::operator != ( const CStlAllocator& other)
{
    return !operator==(other);
}
//--------------------------------------------------------------------------------
