#if !defined(__KERNEL_BUCKET_H__)
#define __KERNEL_BUCKET_H__

#include "Kernel/MemoryManagement/BucketsConfig.h"
#include "Kernel/MemoryManagement/FreePool.h"

namespace MemoryManagement
{

class CBucketNode;
class CBucketPool;

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
class KERNEL_API CBucket
{

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
     CBucket( u32 elementSize, CBucketPool* bucketPool );
    ~CBucket();


//*********************************************
//            INTERFACE
//*********************************************
public:

    void*           Alloc();// alloc an element of size m_elementSize
    void            Free(void* pageAdress, void* element);// free one element;
    Bool            IsPointerFromHere(void* ptr);
    Bool            Validate(void* pageAdress, void* ptr);
    u32             GetElementSize();

//*********************************************
//            HELPER FUNCTIONS
//*********************************************
private:
    CBucketNode*        GetNewNode();
    void                DeleteNode( CBucketNode* node);
    void                SwapNodes(CBucketNode* q, CBucketNode* p);

#if defined(BUCKET_DEBUG)
    Bool                VerifyList();
    void                DumpList();
#endif

//*********************************************
//            MEMBERS
//*********************************************
protected:
    u32             m_elementSize;
    CBucketNode*    m_head;
    CBucketNode*    m_tail;
    CBucketNode*    m_maxCountNode; // pointer to pool with the biggest nb of used elements but not full; the next bucket after this is either null or full

    CBucketPool*    m_ownerBucketPool;
#if defined(BUCKET_DEBUG)
    u32             m_usedElements;
    thSize          m_totalAllocatedMemory;
#endif //BUCKET_DEBUG
};

}//namespace MemoryManagement


#endif //__KERNEL_BUCKET_H__