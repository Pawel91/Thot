#include "Kernel_PCH.h"
#include "Kernel/MemoryManagement/BucketPoolBase.h"

#include "Kernel/MemoryManagement/Bucket.h"
#include "Kernel/MemoryManagement/HeapManager.h"
#include "Kernel/ThotWindows.h"

namespace MemoryManagement
{

//--------------------------------------------------------------------------------
CBucketPoolBase::CBucketPoolBase(u32 pageCount)
    : m_committedPagesPackedSize        (0)
    , m_pageCount                       (pageCount)
    , m_committedPagesPacked            (NULL)
    , m_uncommitedIndex                 (0)
    , m_uncommitedPages                 (NULL)
#if defined(BUCKET_POOL_DEBUG)
    , m_totalInternalAllocSize          (0)
#endif

{
    m_baseAddress = (u8*)VirtualAlloc(NULL, GetPoolSize(), MEM_RESERVE, PAGE_NOACCESS );

    m_uncommitedPages = (u32*)InternalAlloc( m_pageCount* sizeof(u32));
    Memory::Set(m_uncommitedPages, sizeof(m_uncommitedPages), -1 );
    for( u32 i=0; i< m_pageCount; i++ )
    {
        PushUncommittedPage(i);
    }

    m_committedPagesPackedSize = (m_pageCount + (8 - (m_pageCount%8)) ) /8;
    m_committedPagesPacked = (u8*)InternalAlloc(m_committedPagesPackedSize);
    Memory::Set( m_committedPagesPacked, m_committedPagesPackedSize, 0);    

    for( u32 i=0; i< THOT_ARRAY_SIZE(m_buckets); i++ )
    {
        m_buckets[i] = NULL;
    }
}

//--------------------------------------------------------------------------------
CBucketPoolBase::~CBucketPoolBase()
{
    for( u32 i=0; i< THOT_ARRAY_SIZE(m_buckets); i++ )
    {
        if( m_buckets[i] )
        {
            m_buckets[i]->~CBucket();
            InternalFree(m_buckets[i]);
        }
    }

    VirtualFree( m_baseAddress, GetPoolSize(), MEM_RELEASE);
    InternalFree(m_committedPagesPacked);
}
//--------------------------------------------------------------------------------
CBucket* CBucketPoolBase::FindBestFitBucketForElementSize( u32 elementSize )
{
    if(elementSize >= BUCKETS_MAX_ELEMENTSIZE)
    {
        return NULL;
    }
    
    u32 bestFitElementSize = (elementSize + BUCKETS_GRANULARITY-1) &(~BUCKETS_GRANULARITY);

    return m_buckets[elementSize];
}

//--------------------------------------------------------------------------------
u32 CBucketPoolBase::GetPageIndexFromAddress(void* adress)const
{
    u8* end = m_baseAddress + GetPoolSize();
    if( !( m_baseAddress <= end && adress <= end ) )
    {
        return BUCKETS_INVALID_PAGE_INDEX;
    }

    u32 pageIndex = ThNumericCast<u32>( ((u8*)adress-m_baseAddress)/BUCKETS_PAGE_SIZE);

    return pageIndex;
}

//--------------------------------------------------------------------------------
void* CBucketPoolBase::GetPageAddressFromIndex( u32 index)
{
    THOT_ASSERT(m_baseAddress, "MEMORY FOR BUCKET POOL IS NOT RESERVED");
    THOT_ASSERT( index != BUCKETS_INVALID_PAGE_INDEX && index < m_pageCount, "INVALID PAGE INDEX");
    return m_baseAddress + (index*BUCKETS_PAGE_SIZE);
}

//--------------------------------------------------------------------------------
Bool CBucketPoolBase::IsPageCommitted( u32 pageIndex)const
{
    THOT_ASSERT(pageIndex < m_pageCount, "INVALID PAGE INDEX");
    
    u32 byteIndex = pageIndex/8;
    u32 bitIndex = pageIndex%8;
    u8 _byte = m_committedPagesPacked[byteIndex];
    return (_byte & ( 0x80 >> bitIndex ))? true:false;
}

//--------------------------------------------------------------------------------
u32 CBucketPoolBase::GetUncommittedPageIndex()
{
    if( m_uncommitedIndex == -1)
    {
        return BUCKETS_INVALID_PAGE_INDEX;
    }
    return PopUncommitedPage();
}

//--------------------------------------------------------------------------------
void* CBucketPoolBase::CommitPage( u32 pageIndex)
{
    THOT_ASSERT(m_baseAddress, "MEMORY FOR BUCKET POOL IS NOT RESERVED");
    THOT_ASSERT(!IsPageCommitted(pageIndex));

    if( pageIndex == BUCKETS_INVALID_PAGE_INDEX || pageIndex >= m_pageCount)
    {
        return false;
    }

    void* pageAdress = GetPageAddressFromIndex(pageIndex);
    void* ptr = VirtualAlloc( pageAdress, BUCKETS_PAGE_SIZE,  MEM_COMMIT, PAGE_READWRITE );
    THOT_ASSERT( ptr = pageAdress );

    SetCommitted(pageIndex, true);
    return pageAdress;
}

//--------------------------------------------------------------------------------
Bool CBucketPoolBase::DecommitPage( u32 pageIndex)
{
    THOT_ASSERT(m_baseAddress, "MEMORY FOR BUCKET POOL IS NOT RESERVED");
    THOT_ASSERT(IsPageCommitted(pageIndex));

    void* pageAdress = GetPageAddressFromIndex( pageIndex );
    VirtualFree( pageAdress, BUCKETS_PAGE_SIZE, MEM_DECOMMIT );
    SetCommitted(pageIndex, false);
    PushUncommittedPage(pageIndex);

    return true;
}

//--------------------------------------------------------------------------------
void CBucketPoolBase::SetCommitted( u32 pageIndex, Bool commited)
{
    THOT_ASSERT(pageIndex < m_pageCount, "INVALID PAGE INDEX");
    
    u32 byteIndex = pageIndex/8;
    u32 bitIndex = pageIndex%8;
    u8& _byte = m_committedPagesPacked[byteIndex];
    _byte |= ( 0x80 >> bitIndex );

    THOT_ASSERT(IsPageCommitted(pageIndex) == true);
}

//--------------------------------------------------------------------------------
CBucket* CBucketPoolBase::CreateNewBucket(u32 elementSize)
{
    THOT_ASSERT(elementSize < BUCKETS_MAX_ELEMENTSIZE);
    THOT_ASSERT(m_buckets[elementSize]==NULL, "BUCKET FOR THIS SIZE ALREADY CREATED" );
    if( elementSize > BUCKETS_MAX_ELEMENTSIZE || m_buckets[elementSize]!=NULL )
    {
        return NULL;
    }

    m_buckets[elementSize] = new(InternalAlloc(sizeof(CBucket))) CBucket( elementSize, (CBucketPool*)this);

    return m_buckets[elementSize];
}

//--------------------------------------------------------------------------------
void CBucketPoolBase::DestroyBucket( CBucket* bucket )
{
    if(!bucket)
    {
        return;
    }
    bucket->~CBucket();
    InternalFree(bucket);
}

//--------------------------------------------------------------------------------
void CBucketPoolBase::PushUncommittedPage(u32 freePageIndex)
{
    THOT_ASSERT(freePageIndex< m_pageCount);

    m_uncommitedPages[m_uncommitedIndex++] = freePageIndex;
}

//--------------------------------------------------------------------------------
u32 CBucketPoolBase::PopUncommitedPage()
{
    if(m_uncommitedIndex == -1)
    {
        return BUCKETS_INVALID_PAGE_INDEX;
    }

    return m_uncommitedPages[--m_uncommitedIndex];
}

//--------------------------------------------------------------------------------
u32 CBucketPoolBase::GetCommittedPageCount()
{
    u32 count=0;
    for( u32 i=0; i<m_pageCount; i++ )
    {
        if( IsPageCommitted(i) )
        {
            count++;
        }
    }
    return count;
}

//--------------------------------------------------------------------------------
void* CBucketPoolBase::InternalAlloc(u32 size)
{
    BUCKET_POOL_DEBUG_ONLY( m_totalInternalAllocSize+=size );

    return MemoryManagement::CHeapManager::GetInstance()->Alloc(size);
}

//--------------------------------------------------------------------------------
void  CBucketPoolBase::InternalFree(void* memory)
{
    BUCKET_POOL_DEBUG_ONLY( m_totalInternalAllocSize -= ThNumericCast<u32>( MemoryManagement::CManager::GetInstance()->GetBlockSize(memory)) );
    MemoryManagement::CHeapManager::GetInstance()->Free(memory);
}

//--------------------------------------------------------------------------------
}//namespace MemoryManagement