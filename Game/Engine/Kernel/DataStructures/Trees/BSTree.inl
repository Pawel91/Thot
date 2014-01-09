
template<class T>
CBSTree<T>::CBSTree()
    :m_nodeCount        ( 0 )
{
    
}

template<class T>
Bool CBSTree<T>::Insert( const T& element )
{
    if( !m_root )
    {
        m_root = THOT_NEW TNode(element);
        m_nodeCount ++;
        return true;
    }
    else if( InsertRecursive( m_root, element ) )
    {
        m_nodeCount ++;
        return true;
    }

    return false;
}

template<class T>
THOT_NO_INLINE Bool CBSTree<T>::InsertRecursive( CBTreeNode<T>* node, const T& element )
{
    if(!node)
    {
        return false;
    }

    CBTreeNode<T>& refNode = *node;
    if( element == refNode )
    {
        return false;
    }

    if( element > refNode )
    {
        TNode* rightChild = refNode.GetRightChild();
        if( ! rightChild )
        {
            refNode.m_rightChild = THOT_NEW TNode (element);
            return true;
        }
        else
        {
            return InsertRecursive( rightChild, element );
        }
    }
    else //element < refNode
    {
        TNode* leftChild = refNode.GetLeftChild();
        if( !leftChild )
        {
            refNode.m_leftChild = THOT_NEW TNode(element);
            return true;
        }
        else
        {
            return InsertRecursive( leftChild, element );
        }
    }

}



template<class T>
Bool CBSTree<T>::Delete( const T& element )
{
    return false;
}

template<class T>
THOT_FORCE_INLINE Bool CBSTree<T>::ParseInorder   ( thVector<T>& outInorderVector )
{
    outInorderVector.Resize(0);
    ParseInorderRecursive(m_root,outInorderVector);
    return true;
}

template<class T>
void CBSTree<T>::ParseInorderRecursive( CBTreeNode<T>* node, thVector<T>& outInorderVector )
{
    if( !node )
    {
        return;
    }

    ParseInorderRecursive( node->GetLeftChild(), outInorderVector );
    outInorderVector.Add( *node );
    ParseInorderRecursive( node->GetRightChild(), outInorderVector );
}

template<class T>
Bool CBSTree<T>::ParsePreorder( thVector<T>& outPreorderVector )
{
    outPreorderVector.Resize(0);
    ParsePreorderRecursive(m_root, outPreorderVector);
    return true;
}

template<class T>
void CBSTree<T>::ParsePreorderRecursive ( CBTreeNode<T>* node, thVector<T>& outPreorderVector )
{
    if(!node)
    {
        return ;
    }

    ParsePreorderRecursive( node->GetRightChild(), outPreorderVector );
    outPreorderVector.Add( *node );
    ParsePreorderRecursive( node->GetLeftChild(), outPreorderVector );
}

template<class T>
THOT_FORCE_INLINE const typename CBSTree<T>::TNode* CBSTree<T>::Search( const T& element )
{
    return SearchRecursive( m_root, element );
}

template<class T>
typename CBSTree<T>::TNode*  CBSTree<T>::SearchRecursive( CBTreeNode<T>* node,  const T& element )
{
    if( !node )
    {
        return NULL;
    }

    if( element > *node )
    {
        SearchRecursive( node->GetRightChild(), element );
    }
    else if( element < *node)
    {
        SearchRecursive( node->GetLeftChild(), element );
    }
    
    
    return node;

}

template<class T>
THOT_NO_INLINE u64 CBSTree<T>::GetHeightRecursive( CBTreeNode<T>* node )
{
    if( !node )
    {
        return 0;
    }

    return 1 + ThMax( GetHeightRecursive(node->GetLeftChild()), GetHeightRecursive( node->GetRightChild() ) );
}

template<class T>
THOT_FORCE_INLINE u64 CBSTree<T>::GetHeight( )
{
    return GetHeightRecursive( m_root ) - 1;
}
