#pragma once
#ifndef __ARRAY_2D_H__
#define __ARRAY_2D_H__


#include "Kernel\DataStructures\Array\Array.h"

template <class T, int nLines, int nColums>
class  SArray2
{
private:
    T               m_array[nLines][nColums];
 

public:
    SArray2( );
    SArray2( const T otherArray[nLines][nColums] );

    T*                  GetData             ( );
    const T*            GetData             ( )const;
    u32                 GetLines            ( )const;
    u32                 GetColums           ( )const;
    T&                  At                  ( int nLine, int nCol );
    const T&            At                  ( int nLine, int nCol )const;

    CStaticArray<T,nColums>&          operator[]          ( int i );
    const CStaticArray<T,nColums>&    operator[]          ( int i )const;

};

template<class T, int nLines, int nColums> 
SArray2<T, nLines, nColums>::SArray2()
{
}

template<class T, int nLines, int nColums>
SArray2<T, nLines, nColums>::SArray2( const T otherArray[nLines][nColums] )
{
    for( int i=0; i<nLines; i++ )
    for( int j=0; j<nColums; j++ )
    {
        m_array[i][j] = otherArray[i][j];
    }
}

template<class T, int nLines, int nColums> 
inline u32 SArray2<T, nLines, nColums>::GetLines( )const
{
    return nLines;
}

template<class T, int nLines, int nColums> 
inline u32 SArray2<T, nLines, nColums>::GetColums( )const
{
    return nColums;
}

template<class T, int nLines, int nColums> 
inline T& SArray2<T, nLines, nColums>::At( int nLine, int nCol )
{
    return m_array[nLine][nCol];
}

template<class T, int nLines, int nColums> 
inline const T& SArray2<T, nLines, nColums>::At ( int nLine, int nCol )const
{
    return m_array[nLine][nCol];
}

template<class T, int nLines, int nColums> 
inline CStaticArray<T,nColums>& SArray2<T, nLines, nColums>::operator[]( int i )
{
    THOT_ASSERT( i>=0 && i<nLines);
    CStaticArray<T,nColums>* pArray = NULL;
    pArray =  reinterpret_cast<CStaticArray<T,nColums>*>((byte*)m_array[i]);
    return *pArray;
}

template<class T, int nLines, int nColums> 
inline const CStaticArray<T,nColums>&  SArray2<T, nLines, nColums>::operator[] ( int i )const
{
    THOT_ASSERT( i>=0 && i<nLines);
    CStaticArray<T,nColums>* pArray = NULL;
    pArray =  reinterpret_cast<CStaticArray<T,nColums>*>((byte*)m_array[i]);
    return *pArray;
}


template<class T, int nLines, int nColums> 
T* SArray2<T, nLines, nColums>::GetData ( )
{
    return (T*)m_array;
}


template<class T, int nLines, int nColums> 
const T* SArray2<T, nLines, nColums>::GetData ( )const
{
    return (const T*)m_array;
}


#endif /*__ARRAY_2D_H__*/