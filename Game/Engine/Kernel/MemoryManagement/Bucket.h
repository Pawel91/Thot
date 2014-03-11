#if !defined(__KERNEL_BUCKET_ALLOCATOR_H__)
#define __KERNEL_BUCKET_ALLOCATOR_H__

#include "Kernel/MemoryManagement/FreePool.h"


#if defined(THOT_ENABLE_DEBUG)
#   define BUCKET_DEBUG
#endif

namespace MemoryManagement
{

    class CBucketNode;

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
class KERNEL_API CBucket
{

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
     CBucket( u32 elementSize, u32 chunkSize );
    ~CBucket();


//*********************************************
//            INTERFACE
//*********************************************
public:
    static u32      GetPageSize();

    void*           Alloc();// alloc an element of size m_elementSize
    void            Free(void* element);// free one element;
    Bool            IsPointerFromHere(void* ptr);  


//*********************************************
//            HELPER FUNCTIONS
//*********************************************
private:
    CBucketNode*        FindBucketNodeForElement( void* allocatedElement );
    CBucketNode*        GetNewNode();
    void                DeleteNode( CBucketNode* node);
    void                SwapPools(CBucketNode* one, CBucketNode* other);

#if defined(BUCKET_DEBUG)
    Bool                VerifyList();
#endif

    //alloc and free for internal usage;
    virtual void*       InternalAlloc( thSize size);
    virtual void        InternalFree( void* ptr);
   

//*********************************************
//            MEMBERS
//*********************************************

private:
    static const u32    ms_pageSize = 4096;

protected:
    u32             m_elementSize;
    u32             m_chunkSize;
    CBucketNode*    m_head;
    CBucketNode*    m_tail;
    CBucketNode*    m_maxCountNode; // pointer to pool with the biggest nb of used elements but not full; the next bucket after this is either null or full

#if defined(BUCKET_DEBUG)
    u32             m_usedElements;
    thSize          m_totalAllocatedMemory;
#endif //BUCKET_DEBUG
};

}//namespace MemoryManagement


#endif //__KERNEL_BUCKET_ALLOCATOR_H__