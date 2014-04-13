#if !defined(__KERNEL_BUCKET_ALLOCATOR_H__)
#define __KERNEL_BUCKET_ALLOCATOR_H__

#include "Kernel/Basics.h"
#include "Kernel/MemoryManagement/BucketPool.h"

namespace MemoryManagement
{

    class KERNEL_API CBucketAllocator
    {
    
    //*********************************************
    //            CONSTR/DESTR
    //*********************************************
    public:
         CBucketAllocator();
        ~CBucketAllocator();

        //singleton interface
        static CBucketAllocator*    GetInstance();
        static CBucketAllocator*    CreateInstance();
        static void                 DestroyInstance();
    
    
    //*********************************************
    //            INTERFACE
    //*********************************************
    public:
        void*           Alloc(thSize size);
        void            Free(void* memory);
        u64             GetBlockSize(void* memory);
        Bool            Validate(void* ptr);
        Bool            IsPointerFromHere(void* ptr);
        Bool            IsValid();
        Bool            CanAllocSize(thSize size);
    
    
    //*********************************************
    //            MEMBERS
    //*********************************************
    protected:
    static const u32    ms_bucketsMaxSize = 4 * 1024 * 1024;
    CBucketPool         m_bucketPool;
    };


}//namespace MemoryManagement


#endif