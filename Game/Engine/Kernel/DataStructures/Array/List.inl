
template<class T>
const float CVector<T>::ms_growFactor = 0.2f;

template<class T>
CVector<T>::CVector( const CVector& other )
{
}


template<class T>
CVector<T>::CVector ( T* pData, u64 nSize )
:m_array         ( NULL )
,m_nSize         ( 0 )
,m_nTotalSize    ( 0 )
{
    InitFromRawData( pData, nSize);
}

template<class T>
void CVector<T>::InitFromRawData( const T* pData, u64 nSize  )
{
    m_nSize = m_nTotalSize = nSize;
    m_array = THOT_NEW_ARR T[nSize];
    for( u64 i=0; i<nSize; i++ )
    {
        m_array[i] = pData[i];
    }
}



template<class T>
CVector<T>::CVector( u64 capacity )
:m_array        ( NULL )
,m_nSize        ( 0 )
,m_nTotalSize   ( capacity )
{
    m_array = THOT_NEW_ARR T[capacity];
}




template<class T>
inline  T*  CVector<T>::GetData   ( )
{
    return m_array;
}

template<class T>
inline const T* CVector<T>::GetData ( )const
{
    return m_array;
}

template<class T>
inline Bool CVector<T>::AppendBuffer( const T* buffer, u64 nSize )
{
    if( buffer == NULL )
    {
        return false;
    }

    u64 oldSize = GetSize();
    u64 nNewSize = oldSize +  nSize;
    Resize(nNewSize);

    T* copyHere = GetData() + oldSize;
    Memory::Copy( copyHere, buffer, ThNumericCast<size_t>(nSize*sizeof(T)) );

    return true;
}


template<class T>
inline void CVector<T>::IncrementArraySize()
{
    Resize(m_nSize+1);
}

template<class T>
CVector<T>::CVector( )
:m_array        ( NULL )
,m_nSize        ( 0 )
,m_nTotalSize   ( 0 )
{
}

template<class T>
inline CVector<T>::~CVector(  )
{
    //DestroyObjects();
    if( m_array )
        THOT_DELETE_ARR( m_array) ;
}

template<class T>
inline void CVector<T>::Empty()
{
    m_nSize = 0;
}

template<class T>
inline u64 CVector<T>::GetSize()const
{
    return m_nSize;
}


template<class T>
inline u64 CVector<T>::Add( const T& el )
{
    IncrementArraySize();
    m_array[ m_nSize -1 ] = el;
    return m_nSize -1;
}

template<class T>
inline u64 CVector<T>::Insert( const T& el )
{
    IncrementArraySize();
    m_array[ m_nSize -1 ] = el;
    return m_nSize -1;
}

template<class T>
inline void CVector<T>::InsertAt( u64 nIdx, const T& el )
{
    THOT_ASSERT( nIdx >=0 && nIdx < m_nSize );
    IncrementArraySize( );

    for( u64 i= m_nSize -2; i> nIdx; i-- )
    {
        m_array[i+1] = m_array[i-1];
    }

    m_array[nIdx] = el;
}

template<class T>
inline void CVector<T>::DeleteAndMove( u64 nIdx )
{
    //m_array[nIdx].~T();

    for( u64 i=nIdx; i<m_nSize-1; i++ )
    {
        m_array[i] = m_array[i+1];
    }

    m_nSize--;
}

template<class T>
inline void CVector<T>::DestroyObjects( )
{
    for( u64 i=0; i<m_nSize; i++ )
        (m_array[i]).~T();
}

template<class T>
inline T& CVector<T>::operator [] ( u64 nIdx )
{
    THOT_ASSERT( nIdx >=0 && nIdx < m_nSize );
    return m_array[nIdx];
}

template<class T>
inline const T& CVector<T>::operator [] ( u64 nIdx ) const
{
    THOT_ASSERT( nIdx >=0 && nIdx < m_nSize );
    return m_array[nIdx];
}

template<class T>
inline void CVector<T>::Resize( u64 nNewNeededSize )
{
    u64 oldSize = m_nSize;
    m_nSize = nNewNeededSize;
    if( nNewNeededSize < m_nTotalSize )
    {
        return;
    }

    //else we need to grow the array;
    T* pOldBuffer = m_array;

    u64 nGrowBy = ThMax( 16, (u64)( ms_growFactor * nNewNeededSize ) );
    m_nTotalSize = nNewNeededSize + nGrowBy;

    m_array = THOT_NEW_ARR T[m_nTotalSize];
   
    if( pOldBuffer )
    {
        // copy from old buffer to the new one
        for( u64 i=0; i<oldSize; i++ )
        {
            m_array[i] = pOldBuffer[i];
        }

        THOT_DELETE_ARR( pOldBuffer );
    }
}

template<class T>
inline void  CVector<T>::StoleData( CVector<T>& other )
{
    m_array         = other.m_array;
    m_nSize         = other.m_nSize;
    m_nTotalSize    = other.m_nTotalSize;

    other.m_array       = 0;
    other.m_nSize       = 0;
    other.m_nTotalSize  = 0;
}

template<class T>
inline u64 CVector<T>::Find( const T& element,  pfnCompareFunction compareFunction )const
{
    for( u64 i=0; i<m_nSize; i++ )
    {
        if( compareFunction( m_array[i], element) == 0 )
        {
            return i;
        }
    }

    return ms_invalidIndex;
}

template<class T>
void CVector<T>::CopyVectors( CVector<T>& destination, const CVector<T>& source )
{
    destination.Resize(source.GetSize());

    for( u64 i=0; i<source.GetSize(); i++ )
    {
        destination[i] = source[i];
    }
}