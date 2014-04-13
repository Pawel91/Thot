#include "Kernel/Basics.h"

#include "Kernel/MemoryManagement/BucketsConfig.h"

namespace MemoryManagement
{
    class CBucket;

    //contains some low-level management
    class KERNEL_API CBucketPoolBase
    {
    public:
        CBucketPoolBase(u32 pageCount);
        ~CBucketPoolBase();

    protected:
    inline u32  GetMaxPageCount()const{return m_pageCount;}
    inline u32  GetPoolSize()const{ return m_pageCount * BUCKETS_PAGE_SIZE;}
    CBucket*    FindBestFitBucketForElementSize(u32 elementSize);
    u32         GetPageIndexFromAddress(void* adress)const;
    void*       GetPageAddressFromIndex(u32 index);
    Bool        IsPageCommitted(u32 pageIndex)const;
    u32         GetUncommittedPageIndex();
    void*       CommitPage(u32 pageIndex);
    Bool        DecommitPage(u32 pageIndex);
    void        SetCommitted( u32 pageIndex, Bool commited);
    CBucket*    CreateNewBucket( u32 elementSize );
    void        DestroyBucket( CBucket* bucket );
    void        PushUncommittedPage(u32 freePageIndex);
    u32         PopUncommitedPage();
    u32         GetCommittedPageCount();

    void*       InternalAlloc(u32 size);
    void        InternalFree(void* memory);
    
    private:
    u8*                         m_baseAddress;
    const u32                   m_pageCount;
    u8*                         m_committedPagesPacked;
    u32                         m_committedPagesPackedSize;
    u32*                        m_uncommitedPages;
    u32                         m_uncommitedIndex;
    CBucket*                    m_buckets[BUCKETS_MAX_ELEMENTSIZE];
#if defined(BUCKET_POOL_DEBUG)
    u32         m_totalInternalAllocSize;
#endif
    };



};//namespace MemoryManagement