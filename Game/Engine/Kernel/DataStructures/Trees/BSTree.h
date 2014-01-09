#ifndef __KERNEL_BSTREE_H__
#define __KERNEL_BSTREE_H__

#include "BTree.h"

template<class T>
class CBSTree: public CBTree<T>
{
public:
    CBSTree();


virtual     Bool            Insert      ( const T& element );
virtual     Bool            Delete      ( const T& element );
            const TNode*    Search      ( const T& element );

            Bool        ParseInorder    ( thVector<T>& outInorderVector );
            Bool        ParsePreorder   ( thVector<T>& outPreorderVector );
            u64         GetHeight       ( );

private:
    Bool    InsertRecursive         ( CBTreeNode<T>* node, const T& element );
    void    ParseInorderRecursive   ( CBTreeNode<T>* node, thVector<T>& outInorderVector );
    void    ParsePreorderRecursive  ( CBTreeNode<T>* node, thVector<T>& outPreorderVector );
    TNode*  SearchRecursive         ( CBTreeNode<T>* node, const T& element );
    u64     GetHeightRecursive      ( CBTreeNode<T>* node );

protected:
    u64         m_nodeCount;

};

#include "BSTree.inl"

#endif __KERNEL_BSTREE_H__