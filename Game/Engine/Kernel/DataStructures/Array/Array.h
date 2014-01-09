#ifndef __ARRAY_H__
#define __ARRAY_H__

#include "Kernel/Basics.h"
#include "Kernel/DataStructures/ArrayTypeBase.h"



// wrapper for static array
template< class T, u64 nSize >
class CStaticArray:public CArrayTypeBase<T>
{
template<class T, int i, int j> friend class SArray2;
private:
    T           m_array[nSize];

    // not allowed
    CStaticArray( const CStaticArray& other )
    {
    }

public:
    CStaticArray( );
    CStaticArray( const T& el );
    CStaticArray( const T* otherArray, u64 nOtherSize );
    ~CStaticArray();

    T*              GetData             ( )    { return m_array;}
    u64             GetSize             ( ) const;
    void            DestroyObjects      ( );
    void            CopyFromOther       ( const CStaticArray<T, nSize>& other );

    T&              At                  ( u64 nIdx );
    const T&        At                  ( u64 nIdx ) const;

    T&              operator[]          ( u64 nIdx );
    const T&        operator[]          ( u64 nIdx ) const;
};

//--------------------------------------------------------------------------------
template<class T, u64 nSize>
void CStaticArray<T, nSize >::CopyFromOther( const CStaticArray<T, nSize>& other )
{
    for( u64 i=0; i<nSize; i++ )
    {
        m_array[i] = other.m_array[i];
    }
}

//--------------------------------------------------------------------------------
template<class T, u64 nSize >
inline u64 CStaticArray<T, nSize >::GetSize( ) const
{
    //return m_nSize;
    return THOT_ARRAY_SIZE(m_array);
}

template<class T, u64 nSize >
CStaticArray<T,nSize>::CStaticArray( )
{
}


template<class T, u64 nSize >
CStaticArray<T,nSize>::CStaticArray( const T& el )
{
    u64 size = GetSize();
    for( u64 i=0; i<size; i++ )
        m_array[i] = el;
}

template<class T,  u64 nSize>
CStaticArray<T,nSize>::CStaticArray(const T* otherArray, u64 nOtherSize )
{
    u64 size = GetSize();
    THOT_ASSERT( nOtherSize == GetSize());
    for(u64 i=0; i<size; i++)
    {
        m_array[i] = otherArray[i];
    }

}

template<class T, u64 nSize >
inline T& CStaticArray<T,nSize>::operator [] ( u64 nIdx )
{
    THOT_ASSERT( nIdx >=0 && nIdx < GetSize() );
    return m_array[nIdx];
}

template<class T, u64 nSize >
inline const T& CStaticArray<T,nSize>::operator[] ( u64 nIdx ) const
{
    THOT_ASSERT( nIdx >=0 && nIdx < GetSize() );
    return m_array[nIdx];
}

template<class T, u64 nSize >
inline T& CStaticArray<T,nSize>::At ( u64 nIdx )
{
    THOT_ASSERT( nIdx >=0 && nIdx < GetSize() );
    return m_array[nIdx];
}

template<class T, u64 nSize >
inline const T& CStaticArray<T,nSize>::At ( u64 nIdx ) const
{
    THOT_ASSERT( nIdx >=0 && nIdx < GetSize() );
    return m_array[nIdx];
}



template<class T, u64 nSize >
void CStaticArray<T,nSize>::DestroyObjects ( )
{
}

template<class T, u64 nSize >
CStaticArray<T,nSize>::~CStaticArray()
{
    THOT_COMPILE_ASSERT2( THOT_ARRAY_SIZE(m_array)==nSize, "CStaticArray<T,nSize> bad size" );
}



#endif /*__ARRAY_H__*/