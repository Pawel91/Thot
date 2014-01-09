
template<class T>
THOT_FORCE_INLINE CAllocator<T>::CAllocator( ){}

template<class T>
THOT_FORCE_INLINE CAllocator<T>::CAllocator( const CAllocator<T>& other ){}

template<class T> template<class U>
THOT_FORCE_INLINE CAllocator<T>::CAllocator( const CAllocator<U>& other ){}


template<class T>
THOT_FORCE_INLINE CAllocator<T>::~CAllocator( ){}


template<class T>
THOT_FORCE_INLINE typename CAllocator<T>::pointer CAllocator<T>::allocate( size_type size, const_pointer )
{
    pointer _ptr = THOT_MALLOC_TYPE( size, value_type);
    return _ptr;
}

template<class T>
THOT_FORCE_INLINE void  CAllocator<T>::deallocate  ( pointer p, size_type )
{
    THOT_FREE(p);
}

template<class T>
THOT_FORCE_INLINE void CAllocator<T>::construct( pointer p, const T& other )
{
    new(p) T(other);
}

template<class T>
THOT_FORCE_INLINE typename CAllocator<T>::pointer CAllocator<T>::address( reference r )
{
    return &r;
}

template<class T>
THOT_FORCE_INLINE typename CAllocator<T>::const_pointer CAllocator<T>::address ( const_reference r)
{
    return &r;
}

template<class T>
THOT_FORCE_INLINE typename CAllocator<T>::size_type CAllocator<T>::max_size    ( )
{
    return 0xFFFFFFFFFFFFFFFF / sizeof(T);
}

template<class T>
THOT_FORCE_INLINE void CAllocator<T>::destroy( pointer p)
{
    p->~T();
}

template<class T>
THOT_FORCE_INLINE bool  CAllocator<T>::operator == ( const CAllocator& other)
{
    return true;
}

template<class T>
THOT_FORCE_INLINE bool  CAllocator<T>::operator != ( const CAllocator& other)
{
    return !operator==(other);
}
