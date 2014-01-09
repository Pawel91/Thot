
template<class T>
THOT_FORCE_INLINE CBTree<T>::CBTree()
    :m_root     ( NULL )
{

}

template<class T>
CBTree<T>::~CBTree()
{
    if( m_root )
    {
        THOT_DELETE(m_root);
    }
}