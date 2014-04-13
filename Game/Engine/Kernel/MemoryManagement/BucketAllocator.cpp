#include "Kernel_PCH.h"

#include "Kernel/MemoryManagement/BucketAllocator.h"

namespace MemoryManagement
{

//--------------------------------------------------------------------------------
    CBucketAllocator::CBucketAllocator()
        : m_bucketPool  (ms_bucketsMaxSize)
    {
        m_bucketPool.BeginAddBuckets();

        for( u32 bucketSize = 8; bucketSize <= 256; bucketSize += 4 )
        {
            m_bucketPool.AddBucket(bucketSize);
        }

        m_bucketPool.EndAddBuckets();
    }

//--------------------------------------------------------------------------------
    Bool CBucketAllocator::CanAllocSize(thSize size)
    {
        return size>=8 && size<=256 && size%4==0;
    }

//--------------------------------------------------------------------------------
    Bool CBucketAllocator::IsPointerFromHere(void* ptr)
    {
        return m_bucketPool.IsPointerFromHere( ptr );
    }

//--------------------------------------------------------------------------------
    Bool CBucketAllocator::IsValid()
    {
        return m_bucketPool.IsValid();
    }

//--------------------------------------------------------------------------------
    CBucketAllocator::~CBucketAllocator()
    {
    
    }

//--------------------------------------------------------------------------------
    CBucketAllocator* CBucketAllocator::GetInstance()
    {
        static CBucketAllocator bucketAllocator;
        return &bucketAllocator;
    }

//--------------------------------------------------------------------------------
    CBucketAllocator* CBucketAllocator::CreateInstance()
    {
        return GetInstance();
    }

//--------------------------------------------------------------------------------
    void CBucketAllocator::DestroyInstance()
    {
    }


//--------------------------------------------------------------------------------
    void* CBucketAllocator::Alloc(thSize size)
    {
        return m_bucketPool.Alloc(size);
    }

//--------------------------------------------------------------------------------
    void CBucketAllocator::Free(void* memory)
    {
        m_bucketPool.Free(memory);
    }

//--------------------------------------------------------------------------------
    u64 CBucketAllocator::GetBlockSize( void* memory)
    {
        return m_bucketPool.GetBlockSize(memory);       
    }

//--------------------------------------------------------------------------------
    Bool CBucketAllocator::Validate(void* ptr)
    {
        return m_bucketPool.Validate(ptr);
    }

//--------------------------------------------------------------------------------


}// namespace MemoryManagement