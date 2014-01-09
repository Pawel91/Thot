#include "Kernel_PCH.h"
#include "MemoryManager2.h"

#include "Kernel/MemoryManagement/MemoryConfig.h"
#include "Kernel/MemoryManagement/MemoryOperation.h"
#include "Kernel/MemoryManagement/MemoryHandling.h"

#include "string.h"

#define MEM_TRACKING_ON_MALLOC(__buffer, __size, __file, __line) \
    MEM_HANDLING_ADD_OPERATION(__buffer, __buffer, __size, __size, MemoryManagement::EMemoryOperation_Malloc, 0, __file, __line)

#define MEM_TRACKING_ON_FREE(__buffer, __size, __file, __line) \
    MEM_HANDLING_ADD_OPERATION(__buffer, __buffer, __size, __size, MemoryManagement::EMemoryOperation_Free, 0, __file, __line)



namespace MemoryManagement
{
    //THOT_IMPLEMENT_SINGLETON_LAZY(CManager);
    //--------------------------------------------------------------------------------
    CManager*       CManager::CreateInstance()
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
        : ms_defaultHeap( CHeap::FLAG_NO_LOCK, 1 * 1024 * 1024 * 1024, 0 )
    {}
    //----------------------------------------------------------------------
    void*   CManager::Malloc( size_t size )
    {
        void* mem = HeapAlloc(size);
        return mem;
    }

    //----------------------------------------------------------------------
    void    CManager::Free( void* memory )
    {
        HeapFree(memory);
    }

    //----------------------------------------------------------------------
    void* CManager::Debug_Malloc( size_t size, const char* file, u64 line )
    {
        void* mem = HeapAlloc(size);
        MEM_TRACKING_ON_MALLOC( mem, size, file, line );
        return mem;

    }
    
    //----------------------------------------------------------------------
    void    CManager::Debug_Free( void* memory, const char* file, u64 line )
    {
        MEM_TRACKING_ON_FREE( memory, GetBlockSize(memory), file, line );
        HeapFree( memory );
        
    }


    //----------------------------------------------------------------------
    void* CManager::HeapAlloc( size_t size )
    {
        void* memory = ms_defaultHeap.Alloc( size );
        return memory;
    }

    //----------------------------------------------------------------------
    void  CManager::HeapFree( void* memory )
    {
        ms_defaultHeap.Free( memory );
    }

    //----------------------------------------------------------------------
    Bool CManager::Validate( void* memory )
    {
        return ms_defaultHeap.ValidateBlock(memory);
    }
    //----------------------------------------------------------------------
    u64 CManager::GetBlockSize( void* memory )
    {
        return ms_defaultHeap.GetBlockSize(memory);
    }

}//namespace MemoryManagement


