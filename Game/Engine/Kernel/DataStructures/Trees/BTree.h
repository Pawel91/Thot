#pragma once
#ifndef __KERNEL_BTREE_H__
#define __KERNEL_BTREE_H__

#include "BNode.h"

template<class T>
class CBTree
{
public:
        CBTree();
virtual ~CBTree();

typedef  CBTreeNode<T>      TNode;


protected:
    CBTreeNode<T>*      m_root;
};


#include "BTree.inl"

#endif /*__KERNEL_BTREE_H__*/