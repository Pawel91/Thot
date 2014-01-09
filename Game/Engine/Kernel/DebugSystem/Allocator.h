#pragma once
#ifndef __KERNEL_ALLOCATOR_H__
#define __KERNEL_ALLOCATOR_H__

#include "Kernel\MemoryManagement\MemoryManager2.h"

//template<class T>
//class CAllocator
//{
//public:
//
//    //typedefs
//    typedef T                   value_type;
//    typedef u64                 size_type;
//    typedef u64                 difference_type;
//    typedef value_type*         pointer;
//    typedef const value_type*   const_pointer;
//    typedef value_type&         reference;
//    typedef const value_type&   const_reference;
//
//    CAllocator( );
//    CAllocator( const CAllocator<T>& other);
//    template<class U>
//    CAllocator( const CAllocator<U>& other);
//    ~CAllocator( );
//
//    template<class U>
//    struct rebind
//    {
//        typedef CAllocator<U>   other;
//    };
//
//    pointer             allocate    ( size_type size, const_pointer p = NULL );
//    void                deallocate  ( pointer p, size_type );
//    void                construct   ( pointer p, const T& other );
//
//    pointer             address     ( reference r );
//    const_pointer       address     ( const_reference r);
//    size_type           max_size    ( );
//
//    void                destroy     ( pointer p);
//
//    bool                operator == ( const CAllocator& other);
//    bool                operator != ( const CAllocator& other);
//};
//
//
//#include "Allocator.inl"



#endif /*__KERNEL_ALLOCATOR_H__*/