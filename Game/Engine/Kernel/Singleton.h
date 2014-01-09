#pragma once
#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include "Kernel/MemoryManagement/MemoryManager2.h"

#define SINGLETON_CREATE_INSTANCE_FN( __className, __classToCreate)     \
__className* __className::CreateInstance()                            \
{                                                                       \
    if( s_instance == NULL )                                            \
        {                                                               \
            void* mem = THOT_MALLOC( sizeof(__classToCreate) );         \
            s_instance =  new(mem) __classToCreate;                     \
        }                                                               \
    else                                                                \
    {                                                                   \
        s_instance->~__className();                                     \
        THOT_FREE(s_instance);                                          \
        void* mem = THOT_MALLOC( sizeof(__classToCreate) );             \
        s_instance =  new(mem) __classToCreate;                         \
    }                                                                   \
    return s_instance;                                                  \
}

#define SINGLETON_CREATE_INSTANCE_FN_INLINE( __className, __classToCreate)     \
THOT_FORCE_INLINE __className* __className::CreateInstance()                              \
{                                                                       \
    if( s_instance == NULL )                                            \
        {\
            void* mem = THOT_MALLOC( sizeof(__classToCreate) );           \
            s_instance =  new(mem) __classToCreate;\
        }\
    else                                                                \
    {                                                                   \
        s_instance->~__className();\
        THOT_FREE(s_instance);  \
        void* mem = THOT_MALLOC( sizeof(__classToCreate) );           \
        s_instance =  new(mem) __classToCreate;\
    }                                                                   \
    return s_instance;                                                  \
}



#define THOT_DECLARE_SINGLETON( _className )             \
private:                                            \
static    _className*        s_instance;            \
public:                                             \
static    _className*        GetInstance();       \
static    _className*        CreateInstance();    \
static    void    DestroyInstance();              

#define IMPLEMENT_SINGLETON_INSTANCE(_className)\
_className* _className::s_instance = NULL;

#define THOT_IMPLEMENT_SINGLETON( _className )   \
_className* _className::s_instance = NULL;  \
_className* _className::GetInstance()     \
{                                           \
    return s_instance;                      \
}                                           \
                                            \
SINGLETON_CREATE_INSTANCE_FN(_className,_className)\
void _className::DestroyInstance()        \
{                                           \
    if( s_instance )                        \
    {\
    s_instance->~_className();\
        THOT_FREE(s_instance);                \
    }\
}                                           


#define THOT_DECLARE_SINGLETON_LAZY(__className)    \
public: \
    static  __className* GetInstance();   \
    static  __className* CreateInstance(){ return GetInstance(); } \
    static void DestroyInstance(){}

#define THOT_IMPLEMENT_SINGLETON_LAZY(__className)\
__className* __className::GetInstance(){ static __className instance; return &instance; }

#define IMPLEMENT_SINGLETON_INLINE( _className )   \
THOT_FORCE_INLINE _className* _className::GetInstance()     \
{                                           \
    return s_instance;                      \
}                                           \
                                            \
SINGLETON_CREATE_INSTANCE_FN_INLINE(_className,_className)\
THOT_FORCE_INLINE void _className::DestroyInstance()        \
{                                           \
    if( s_instance )                        \
    {    \
        s_instance->~_className();\
        THOT_FREE(s_instance);                \
    }\
}                                           


/**
    _classTOCreate must be derivate from _className
*/
#define IMPLEMENT_SINGLETON_CUSTOM( _className, _classToCreate )\
_className* _className::s_instance = NULL;  \
_className* _className::GetInstance()     \
{                                           \
    return s_instance;                      \
}                                           \
    \
SINGLETON_CREATE_INSTANCE_FN(_className,_classToCreate)\
void _className::DestroyInstance()        \
{                                           \
    if( s_instance )                        \
    THOT_DELETE(s_instance);                \
}                                           

#if !defined(__KERNEL_MEMORY_MANAGEMENT_H__)
#   error CANNOT USE SINGLETON BEFORE INCLUDING MemoryManager.h
#endif

//--------------------------------------------------------------------------------
template<class T>
class CSingleton
{
public:
         CSingleton();
        ~CSingleton();

static    T*        GetInstance();
static    T*        CreateInstance();
static    void      DestroyInstance();

private:
static    T*        ms_instance;
};

//--------------------------------------------------------------------------------
template<class T>
CSingleton<T>::CSingleton()
{
    THOT_ASSERT(ms_instance == NULL, "MORE THEN 1 INSTANCE OF A SINGLETON IS CREATED");
    ms_instance = (T*)this;
}

//--------------------------------------------------------------------------------
template<class T> 
 T* CSingleton<T>::ms_instance = NULL;

//--------------------------------------------------------------------------------
template<class T>
THOT_FORCE_INLINE T* CSingleton<T>::GetInstance()
{
    return ms_instance;
}

//--------------------------------------------------------------------------------
template<class T>
T* CSingleton<T>::CreateInstance()
{
    return THOT_NEW T;
}

//--------------------------------------------------------------------------------
template<class T>
void CSingleton<T>::DestroyInstance()
{
    if( ms_instance )
    {
        THOT_DELETE(ms_instance);
    }
}

//--------------------------------------------------------------------------------
template<class T>
CSingleton<T>::~CSingleton()
{
}

#endif