#include "Kernel_PCH.h"

#include "Kernel/MemoryManagement/BucketPool.h"
#include "Kernel/MemoryManagement/Bucket.h"
#include "Kernel/MemoryManagement/HeapManager.h"
#include "Kernel/ThotWindows.h"


namespace MemoryManagement
{

//--------------------------------------------------------------------------------
CBucketPool::CBucketPool( u32 maxPoolSize )
    : super                             (maxPoolSize/BUCKETS_PAGE_SIZE)
    , m_bucketsPoolSize                 (maxPoolSize)
    , m_state                           (CBucketPool::EState_Invalid)
{
    THOT_ASSERT( (maxPoolSize & ( (BUCKETS_PAGE_SIZE-1))) == 0, "BUCKET POOL SIZE MUST BE MULTIPLE OF BUCKETS_PAGE_SIZE");
}

//--------------------------------------------------------------------------------
CBucketPool::~CBucketPool()
{
}

//--------------------------------------------------------------------------------
void* CBucketPool::Alloc( thSize size )
{
    if( CBucket* bucket = FindBestFitBucketForElementSize( ThNumericCast<u32>(size) ) )
    {
        return bucket->Alloc();
    }

    return NULL;
}

//--------------------------------------------------------------------------------
void CBucketPool::Free(void* memory)
{
    THOT_ASSERT(IsPointerFromHere(memory));

    u32 pageIndex = GetPageIndexFromAddress( memory );
    void* pageAdress = GetPageAddressFromIndex(pageIndex);
    SPageHeader* pageHeader = (SPageHeader*)pageAdress;
    void* pageAdressSentToBucket = (u8*)pageAdress + sizeof(SPageHeader);
    pageHeader->m_bucket->Free( pageAdressSentToBucket, memory );
}

//--------------------------------------------------------------------------------
CBucketPool::SPage CBucketPool::AllocPage( CBucket* requesterBucket )
{
    u32 pageIndex = GetUncommittedPageIndex();
    if(pageIndex == BUCKETS_INVALID_PAGE_INDEX)
    {
        // no free pages left; bucket pool is full
        return SPage();
    }
    u8* pageAdress = (u8*)CommitPage( pageIndex );
    SPageHeader* header = new(pageAdress) SPageHeader;
    header->m_bucket = requesterBucket;
    pageAdress += sizeof(SPageHeader);

    return SPage(pageAdress, BUCKETS_PAGE_SIZE - sizeof(SPageHeader));
}

//--------------------------------------------------------------------------------
void CBucketPool::FreePage(CBucket* requesterBucket, void* adress)
{
    THOT_ASSERT(requesterBucket && adress);
    u32 pageIndex = GetPageIndexFromAddress(adress);
    THOT_ASSERT(IsPageCommitted(pageIndex));
    DecommitPage(pageIndex);
}

//--------------------------------------------------------------------------------
Bool CBucketPool::Validate(void* ptr)
{
    if( !IsPointerFromHere(ptr) )
    {
        return false;
    }

    u32 pageIndex = GetPageIndexFromAddress(ptr);
    void* pageAdress = GetPageAddressFromIndex(pageIndex);
    SPageHeader* header = (SPageHeader*) pageAdress;
    return header->m_bucket->Validate( (u8*)pageAdress + sizeof(SPageHeader), ptr );
}

//--------------------------------------------------------------------------------
Bool CBucketPool::IsPointerFromHere(void* ptr)
{
    u32 pageIndex = GetPageIndexFromAddress(ptr);
    if( pageIndex == BUCKETS_INVALID_PAGE_INDEX)
    {
        return false;
    }
    return IsPageCommitted(pageIndex);
}

//--------------------------------------------------------------------------------
thSize CBucketPool::GetBlockSize(void* ptr)
{
    u32 pageIndex = GetPageIndexFromAddress(ptr);
    if(pageIndex==BUCKETS_INVALID_PAGE_INDEX || !IsPageCommitted(pageIndex))
    {
        return 0;
    }

    void* pageAdress = GetPageAddressFromIndex(pageIndex);
    SPageHeader* pageHeader = (SPageHeader*)pageAdress;

    //[TODO] is the pointer really used?  
    return pageHeader->m_bucket->GetElementSize();
}

//--------------------------------------------------------------------------------
void CBucketPool::BeginAddBuckets()
{
    THOT_ASSERT(m_state == EState_Invalid );
    m_state = EState_AddingBuckets;
}

//--------------------------------------------------------------------------------
Bool CBucketPool::AddBucket(u32 elementSize)
{
    return CreateNewBucket(elementSize) != NULL;
}

//--------------------------------------------------------------------------------
void CBucketPool::EndAddBuckets()
{
    THOT_ASSERT(m_state == EState_AddingBuckets);
    m_state = EState_Valid;

#if defined(BUCKET_POOL_DEBUG)

    u32 maxBucketSize = GetPoolSize();
    u32 pagesWaste = GetMaxPageCount() * 64;//computed by me:D; 8 bytes from bucket pool header and rest from bucket header;

    THOT_TRACE_LINE("BUCKET POOL MAX SIZE       = [%d]", maxBucketSize);
    THOT_TRACE_LINE("PAGES WASTE                = [%d]", pagesWaste);
#endif
}

//--------------------------------------------------------------------------------
Bool CBucketPool::IsValid()
{
    return m_state == EState_Valid;
}

//--------------------------------------------------------------------------------


}// namespace MemoryManagement