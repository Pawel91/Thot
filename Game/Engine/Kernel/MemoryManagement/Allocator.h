#if !defined(__KERNEL_SMART_ALLOCATOR_H__)
#define __KERNEL_SMART_ALLOCATOR_H__

#include "Kernel/Basics.h"

#include "Kernel/MemoryManagement/MemoryManager2.h"
#include "Kernel/MemoryManagement/FrameAllocator.h"
#include "Kernel/MemoryManagement/MemoryUtils.h"

//--------------------------------------------------------------------------------
class KERNEL_API CAllocatorBase
{

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
    CAllocatorBase( void* owner);

//*********************************************
//            INTERFACE
//*********************************************
public:


//*********************************************
//            MEMBERS
//*********************************************
protected:
    void*   m_owner;
};

//--------------------------------------------------------------------------------
class KERNEL_API CDefaultAllocator
{

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
    CDefaultAllocator( void* owner );


//*********************************************
//            INTERFACE
//*********************************************
public:
    const void*     GetOwner()const;

//*********************************************
//            MEMBERS
//*********************************************
protected:

};

//--------------------------------------------------------------------------------
class KERNEL_API CSmartAllocator: public CAllocatorBase
{

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
    typedef CAllocatorBase super;
    CSmartAllocator( void* owner);
    CSmartAllocator( const CSmartAllocator& other );

//*********************************************
//            INTERFACE
//*********************************************
public:
    Bool            IsOwnerOnStack      ( ){ return m_isOwnerOnStack;}
    void*           Alloc               ( thSize size );
    void            Free                ( void* memory );
    void*           AllocAlign          ( thSize size, thSize alignment );
    void            FreeAlign           ( void* mem );

//*********************************************
//            MEMBERS
//*********************************************
protected:
    Bool            m_isOwnerOnStack;
};

//--------------------------------------------------------------------------------
template<class T>
class CStlAllocator
{
public:
    template<class T> friend class CStlAllocator;

    //typedefs
    typedef T                   value_type;
    typedef u64                 size_type;
    typedef u64                 difference_type;
    typedef value_type*         pointer;
    typedef const value_type*   const_pointer;
    typedef value_type&         reference;
    typedef const value_type&   const_reference;

    CStlAllocator( );
    CStlAllocator( const CStlAllocator<T>& other);
    template<class U>
    CStlAllocator( const CStlAllocator<U>& other);
    ~CStlAllocator( );

    template<class U>
    struct rebind
    {
        typedef CStlAllocator<U>   other;
    };

    pointer             allocate    ( size_type size, const_pointer p = NULL );
    void                deallocate  ( pointer p, size_type );
    void                construct   ( pointer p, const T& other );

    pointer             address     ( reference r );
    const_pointer       address     ( const_reference r);
    size_type           max_size    ( );

    void                destroy     ( pointer p);

    bool                operator == ( const CStlAllocator& other);
    bool                operator != ( const CStlAllocator& other);

};

#include "Kernel/MemoryManagement/StlAllocator.inl"


#endif //__KERNEL_SMART_ALLOCATOR_H__