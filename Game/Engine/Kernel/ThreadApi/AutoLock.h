#if !defined(__AUTO_LOCK_H__)
#define __AUTO_LOCK_H__

template<typename LOCK_TYPE>
class CAutoLock
{
public:
    inline CAutoLock( LOCK_TYPE& lock)
        : m_lock        (&lock)
    {
        m_lock->Lock();
    }

    inline ~CAutoLock()
    {
        m_lock->Unlock();
    }
private:
    LOCK_TYPE*      m_lock;
};


#endif //__AUTO_LOCK_H__