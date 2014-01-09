#pragma once
#ifndef __KERNEL_SMART_POINTER_H__
#define __KERNEL_SMART_POINTER_H__

#include "RefCounter.h"

template<class T>
class CSmartPtr
{
public:
    CSmartPtr   ( T* ptr );
    CSmartPtr   ( const CSmartPtr<T>& other );
    ~CSmartPtr  ();

const CSmartPtr<T>& operator = ( const CSmartPtr<T>& other );


public:
    typedef void (*fnDeallocator)( void* ptr );

static void         DefaultDeallocator  ( void* ptr );
static void         RegisterDeallocator ( fnDeallocator deallocator );

    T*          operator -> ();
    const T*    operator -> ()const;

    T&          operator * ();
    const T&    operator * ()const;

    operator T*         ( );
    operator const T*   ( )const;

private:
    void            InitFromOther   ( const CSmartPtr<T>& other );
    void            ReleaseThis     ( );
    
static fnDeallocator    ms_defaultDeallocator;

    T*              m_data;
    CRefCounter*    m_refCounter;
};


#include "SmartPointer.inl"

#endif