inline  CRefCounter::CRefCounter()
    :m_refCount(0)
{
}

inline void CRefCounter::AddRef()
{
    m_refCount++;
}

inline u32 CRefCounter::GetRefCount()
{
    return m_refCount;
}

inline u32 CRefCounter::Release()
{
    THOT_ASSERT(m_refCount>0);
    return --m_refCount;
}
