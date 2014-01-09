#pragma once
#ifndef __KERNEL_BTREE_NODE_H__
#define __KERNEL_BTREE_NODE_H__


template<class T>
class CBTreeNode // node of a binary tree node
{
    template<class T> friend class CBTree;
    template<class T> friend class CBSTree;
public:
    CBTreeNode( CBTreeNode<T>& otherNode );
    CBTreeNode( const T& key);
    CBTreeNode();

    Bool                    operator == ( const CBTreeNode<T>& otherNode );//compare by key only
    const CBTreeNode<T>&    operator =  ( const CBTreeNode<T>& otherNode );

    const T&            GetKey  ()const;
    T&                  GetKey  ();

    operator const T&   ( ) const;
    operator  T&        ( );

    CBTreeNode<T>*  GetLeftChild    ( );
    CBTreeNode<T>*  GetRightChild   ( );
    Bool            IsLeaf          ( );

protected:
    T               m_key;
    CBTreeNode*     m_leftChild;
    CBTreeNode*     m_rightChild;
};

template<class T>
THOT_FORCE_INLINE CBTreeNode<T>::CBTreeNode( const T& key )
    :m_key          ( key )
    ,m_rightChild   ( NULL )
    ,m_leftChild    ( NULL )
{
}

template<class T>
THOT_FORCE_INLINE CBTreeNode<T>::CBTreeNode(   )
    :m_rightChild   ( NULL )
    ,m_leftChild    ( NULL )
{
}

template<class T>
THOT_FORCE_INLINE CBTreeNode<T>::operator const T&   ( ) const
{
    return m_key;
}


template<class T>
THOT_FORCE_INLINE CBTreeNode<T>::operator  T&( )
{
    return m_key;
}


template<class T>
THOT_FORCE_INLINE CBTreeNode<T>* CBTreeNode<T>::GetLeftChild ( )
{
    return m_leftChild;
}

template<class T>
THOT_FORCE_INLINE CBTreeNode<T>*  CBTreeNode<T>::GetRightChild ( )
{
    return m_rightChild;
}

template<class T>
THOT_FORCE_INLINE Bool CBTreeNode<T>::operator == ( const CBTreeNode<T>& otherNode )
{
    return m_key == otherNode.m_key;
}

template<class T>
THOT_FORCE_INLINE const CBTreeNode<T>& CBTreeNode<T>::operator = ( const CBTreeNode<T>& otherNode )
{
    m_key = otherNode.m_key;
    m_leftChild = otherNode.m_leftChild;
    m_rightChild = otherNode.m_rightChild;
}

template<class T>
THOT_FORCE_INLINE CBTreeNode<T>::CBTreeNode( CBTreeNode<T>& otherNode )
{
    m_key = otherNode.m_key;
    m_leftChild = otherNode.m_leftChild;
    m_rightChild = otherNode.m_rightChild;
}

template<class T>
const T& CBTreeNode<T>::GetKey  ()const
{
    return m_key;
}

template<class T>
T& CBTreeNode<T>::GetKey  ()
{
    return m_key;
}

template<class T>
Bool CBTreeNode<T>::IsLeaf( )
{
    return m_rightChild == NULL && m_leftChild == NULL;
}

#endif /*__KERNEL_BTREE_NODE_H__*/