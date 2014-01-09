
template<class T>
CSmartResource<T>::CSmartResource ()
{
    m_refCounter = THOT_NEW CRefCounter;
    CRefCounter->AddRef();
}