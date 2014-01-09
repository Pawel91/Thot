#if !defined(__KERNEL_SINGLETON_LAZY_H__)
#define __KERNEL_SINGLETON_LAZY_H__


//--------------------------------------------------------------------------------
template<class T>
class CSingletonLazy
{
public:
         CSingletonLazy();
        ~CSingletonLazy();

static    T*        GetInstance();
static    T*        CreateInstance();
static    void      DestroyInstance();

private:
static    T*        ms_instance;
};

//--------------------------------------------------------------------------------
template<class T>
CSingletonLazy<T>::CSingletonLazy()
{
    THOT_ASSERT(ms_instance == NULL, "MORE THEN 1 INSTANCE OF A SINGLETON IS CREATED");
    ms_instance = (T*)this;
}

//--------------------------------------------------------------------------------
template<class T> 
 T* CSingletonLazy<T>::ms_instance = NULL;

//--------------------------------------------------------------------------------
template<class T>
THOT_FORCE_INLINE T* CSingletonLazy<T>::GetInstance()
{
    //if(!ms_instance)
    //{
    //    return CreateInstance();
    //}
    static T instance;
    return ms_instance;
}

//--------------------------------------------------------------------------------
template<class T>
T* CSingletonLazy<T>::CreateInstance()
{
    //    return THOT_NEW T;
    return GetInstance();
}

//--------------------------------------------------------------------------------
template<class T>
void CSingletonLazy<T>::DestroyInstance()
{
    //if( ms_instance )
    //{
    //    THOT_DELETE(ms_instance);
    //}
}

//--------------------------------------------------------------------------------
template<class T>
CSingletonLazy<T>::~CSingletonLazy()
{
}


#endif //__KERNEL_SINGLETON_LAZY_H__