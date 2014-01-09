#pragma once
#ifndef __STACK_H__
#define __STACK_H__

#include "Kernel\Kernel.h"

template<class T>
class CStackNode
{
template<class U> friend class CStack ;
public:
    CStackNode();
    CStackNode( const T& el );

protected:
    T               m_nInfo;
    CStackNode*     m_pPrev;    // previous node
};

template<class T>
CStackNode<T>::CStackNode()
:m_pPrev            ( NULL )
{

}

template < class T >
CStackNode<T>::CStackNode( const T& el )
:m_pPrev            ( NULL )
,m_nInfo            ( el )
{

}

/**
    Template Stack as a linked list;
*/
template<class T>
class CStack
{
public:
    CStack( int _maxSize = 10000 );

// push and pop returns current size of the stack
    int             Push        ( const T& el );
    int             Pop         ( );
    T&              Peek        ( );
    const T&        Peek        ( )const;
    int             GetCurrSize ( )const{ return m_nCurrSize; }

protected:
    CStackNode<T>*          m_pTop;
    int                     m_nCurrSize;
    int                     m_nMaxSize;
};

template <class T>
CStack<T>::CStack( int _maxSize )
:m_pTop             ( NULL )
,m_nCurrSize        ( 0 )
,m_nMaxSize         ( _maxSize )
{
    
}

template <class T> 
inline int CStack<T>::Push ( const T& el )
{
    THOT_ASSERT( m_nCurrSize < m_nMaxSize );
    CStackNode<T>* pNode = THOT_NEW CStackNode<T>(el);
    pNode->m_pPrev = m_pTop;
    m_pTop = pNode;
    m_nCurrSize++;
    
    return m_nCurrSize;
}

template <class T> 
inline int CStack<T>::Pop ( )
{
    THOT_ASSERT( m_nCurrSize>0 ); // stack underflow;
    CStackNode<T>* pNode = m_pTop->m_pPrev;
    THOT_DELETE( m_pTop );
    m_pTop = pNode;
    m_nCurrSize--;
    return m_nCurrSize;
}

template <class T> 
inline T& CStack<T>::Peek ( )
{
    return m_pTop->m_nInfo;
}

template <class T> 
inline const T& CStack<T>::Peek ( )const
{
    return m_pTop->m_nInfo;
}

#endif /*__STACK_H__*/