
template<class T>
typename CSmartPtr<T>::fnDeallocator CSmartPtr<T>::ms_defaultDeallocator = CSmartPtr<T>::DefaultDeallocator;



template<class T>
void CSmartPtr<T>::DefaultDeallocator( void* ptr )
{
    THOT_DELETE( (T*)ptr );
}

#ifndef DECLARE_DEFAULT_CONSTRUCTOR_LIST
#define DECLARE_DEFAULT_CONSTRUCTOR_LIST \
:m_refCounter       ( NULL)     \
,m_data             ( NULL )


#else
#   error DECLARE_DEFAULT_CONSTRUCTOR_LIST allready defined
#endif


template<class T>
THOT_FORCE_INLINE void CSmartPtr<T>::RegisterDeallocator ( fnDeallocator deallocator )
{
    if( !deallocator )
    {
        return;
    }

    ms_defaultDeallocator = deallocator;
}


template<class T> 
THOT_FORCE_INLINE CSmartPtr<T>::CSmartPtr( T* ptr )
    DECLARE_DEFAULT_CONSTRUCTOR_LIST
{
    m_data = ptr;
    m_refCounter = THOT_NEW CRefCounter;
    m_refCounter->AddRef();
}

template<class T>
THOT_FORCE_INLINE CSmartPtr<T>::CSmartPtr( const CSmartPtr<T>& other )
    DECLARE_DEFAULT_CONSTRUCTOR_LIST
{
    InitFromOther( other );
}

#undef DECLARE_DEFAULT_CONSTRUCTOR_LIST

template<class T> 
THOT_FORCE_INLINE CSmartPtr<T>::~CSmartPtr()
{
    ReleaseThis();
}

template<class T>
THOT_FORCE_INLINE const CSmartPtr<T>& CSmartPtr<T>::operator = ( const CSmartPtr<T>& other )
{
    InitFromOther(other);

    return *this;
}

template<class T>
THOT_FORCE_INLINE void CSmartPtr<T>::InitFromOther( const CSmartPtr<T>& other )
{
    ReleaseThis();

    m_data = other.m_data;
    m_refCounter = other.m_refCounter;
    m_refCounter->AddRef();
}


template<class T>
THOT_FORCE_INLINE void CSmartPtr<T>::ReleaseThis( )
{
    // nothing to release
    if( !m_refCounter )
    {
        return;
    }

    if( m_refCounter->Release() == 0 )
    {
        if( m_data )
        {
            ms_defaultDeallocator(m_data);
        }

        THOT_DELETE(m_refCounter);
    }

    m_data = NULL;
    m_refCounter = NULL;
}




template<class T>
THOT_FORCE_INLINE T* CSmartPtr<T>::operator -> ()
{
    return m_data;
}

template<class T>
THOT_FORCE_INLINE const T* CSmartPtr<T>::operator -> ()const
{
    return m_data;
}

template<class T>
T& CSmartPtr<T>::operator * ()
{
    return *m_data;
}

template<class T>
const T& CSmartPtr<T>::operator * ()const
{
    return *m_data;
}

template<class T>
THOT_FORCE_INLINE CSmartPtr<T>::operator T*( )
{
    return m_data;
}

template<class T>
THOT_FORCE_INLINE CSmartPtr<T>::operator const T*   ( )const
{
    return m_data;
}



