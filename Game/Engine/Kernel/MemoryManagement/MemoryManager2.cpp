#include "Kernel_PCH.h"
#include "MemoryManager2.h"

#include "Kernel/MemoryManagement/MemoryConfig.h"
#include "Kernel/MemoryManagement/MemoryOperation.h"
#include "Kernel/MemoryManagement/MemoryHandling.h"

#include "Kernel/MemoryManagement/HeapManager.h"

#if defined(THOT_MEM_ENABLE_BUCKETS_SYSTEM)
#   include "Kernel/MemoryManagement/BucketAllocator.h"
#endif

#include "string.h"

#define MEM_TRACKING_ON_MALLOC(__buffer, __size, __file, __line) \
    MEM_HANDLING_ADD_OPERATION(__buffer, __buffer, __size, __size, MemoryManagement::EMemoryOperation_Malloc, 0, __file, __line)

#define MEM_TRACKING_ON_FREE(__buffer, __size, __file, __line) \
    MEM_HANDLING_ADD_OPERATION(__buffer, __buffer, __size, __size, MemoryManagement::EMemoryOperation_Free, 0, __file, __line)



namespace MemoryManagement
{
    //THOT_IMPLEMENT_SINGLETON_LAZY(CManager);
    //--------------------------------------------------------------------------------
    CManager* CManager::CreateInstance()
    {
        return GetInstance();
    }

    //--------------------------------------------------------------------------------
    CManager* CManager::GetInstance()
    {
        static CManager instance;
        return &instance;
    }

    //--------------------------------------------------------------------------------
    void CManager::DestroyInstance()
    {
    }

    //--------------------------------------------------------------------------------
    CManager::CManager()
    {
#if defined(THOT_MEM_ENABLE_BUCKETS_SYSTEM)
        CBucketAllocator::CreateInstance();
#endif
    }

    //----------------------------------------------------------------------
    void* CManager::Malloc( size_t size )
    {
        void* mem = InternalAlloc(size);
        return mem;
    }

    //----------------------------------------------------------------------
    void CManager::Free( void* memory )
    {
        InternalFree(memory);
    }

    //----------------------------------------------------------------------
    void* CManager::Debug_Malloc( size_t size, const char* file, u64 line )
    {
        void* mem = InternalAlloc(size);
        MEM_TRACKING_ON_MALLOC( mem, size, file, line );
        return mem;

    }
    
    //----------------------------------------------------------------------
    void    CManager::Debug_Free( void* memory, const char* file, u64 line )
    {
        MEM_TRACKING_ON_FREE( memory, GetBlockSize(memory), file, line );
        InternalFree( memory );
    }

    //----------------------------------------------------------------------
    Bool CManager::Validate( void* memory )
    {
#if defined(THOT_MEM_ENABLE_BUCKETS_SYSTEM)
        if( CBucketAllocator::GetInstance()->IsPointerFromHere(memory) )
        {
            return CBucketAllocator::GetInstance()->Validate(memory);
        }
#endif
        return CHeapManager::GetInstance()->IsPointerFromHere(memory);
    }
    //----------------------------------------------------------------------
    u64 CManager::GetBlockSize( void* memory )
    {
#if defined(THOT_MEM_ENABLE_BUCKETS_SYSTEM)
        if( CBucketAllocator::GetInstance()->IsPointerFromHere(memory) )
        {
            return CBucketAllocator::GetInstance()->GetBlockSize(memory);
        }
#endif
        return CHeapManager::GetInstance()->GetBlockSize(memory);
    }

    //--------------------------------------------------------------------------------
    void* CManager::InternalAlloc( size_t size)
    {
#if defined(THOT_MEM_ENABLE_BUCKETS_SYSTEM)
        if( CBucketAllocator::GetInstance()->CanAllocSize(size))
        {
            void* ptr = CBucketAllocator::GetInstance()->Alloc( size );
            if( ptr )
            {
                return ptr;
            }
        }
#endif

        return CHeapManager::GetInstance()->Alloc(size);
    }

    //--------------------------------------------------------------------------------
    void CManager::InternalFree( void* memory)
    {
#if defined(THOT_MEM_ENABLE_BUCKETS_SYSTEM)
        if( CBucketAllocator::GetInstance()->IsPointerFromHere(memory) )
        {
            CBucketAllocator::GetInstance()->Free(memory);
            return;
        }
#endif

        CHeapManager::GetInstance()->Free(memory);
    }


}//namespace MemoryManagement


