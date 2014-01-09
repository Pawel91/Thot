#if !defined(__KERNEL_MEMORY_MANAGEMENT_H__)
#define __KERNEL_MEMORY_MANAGEMENT_H__

#include "Kernel/KernelDef.h"
#include "Kernel/Basics.h"
#include "Kernel/Defines.h"

#include "Kernel/MemoryManagement/MemoryConfig.h"
#include "Kernel/MemoryManagement/Heap.h"
#include "Kernel/MemoryManagement/MemoryHandling.h"


#if defined(THOT_PLATFORM_WINDOWS)
#   if !defined(_NEW_)
#       define _NEW_
    namespace std{struct nothrow_t{};}
#   else
#       error _NEW_ is allready defined; system files included before Kernel includes
#   endif
#endif 

// OVERRIDE new/delete OPERATORS TO ALLOCATE FROM MemoryManager
// standard new/delete operators
void* operator new( size_t size );
void operator delete( void* memory);

// standard array new/delete
void* operator new[]( size_t size);
void operator delete[](void* mem);

// placement new
void* operator new( size_t size, void* place);
void operator delete( void*, void* place);

namespace MemoryManagement
{
    //[TODO] add alloc align
    class KERNEL_API CManager
    {
    //THOT_DECLARE_SINGLETON_LAZY(CManager);
    public:
    static CManager*        CreateInstance();
    static CManager*        GetInstance();
    static void             DestroyInstance();


    private:
        CManager();
    public:
     friend void*   ::operator new        ( size_t size );
     friend void    ::operator delete     ( void* memory);
     friend void*   ::operator new[]      ( size_t size);
     friend void    ::operator delete[]   (void* mem);

    // MALLOC/FREE FUNCTIONS TO REPLACE STANDARD malloc/free. [TODO] add MallocAligned
    public:

        void*    Debug_Malloc        ( size_t size, const char* file, u64 line );
        void     Debug_Free          ( void* memory, const char* file, u64 line );
        
        u64      GetBlockSize        ( void* memory );
        Bool     Validate            ( void* memory );
#if defined(THOT_ENABLE_MEMORY_TRACKING) // use only the debug versions when tracking is enabled
    private:
#endif
        void*    Malloc              ( size_t size );
        void     Free                ( void* memory );

    // INTERNAL MEMORY FUNCTIONS USED TO ALLOCATE
    private:


        void*    HeapAlloc           ( size_t size );
        void     HeapFree            ( void* memory );

    // THE DEFAULT HEAP THAT WE WILL USE TO ALLOCATE MEMORY
    private:
        CHeap ms_defaultHeap;
    };

}//namespace MemoryManager

//----------------------------------------------------------------------
// standard new/delete operators
inline void* operator new( size_t size )
{
    void* mem = MemoryManagement::CManager::GetInstance()->HeapAlloc( size );
    return mem;
}

inline void operator delete( void* memory)
{
    MemoryManagement::CManager::GetInstance()->HeapFree( memory );
}

// standard array new/delete
inline void* operator new[]( size_t size)
{
    void* mem = MemoryManagement::CManager::GetInstance()->HeapAlloc( size );
    return mem;
}

inline void operator delete[](void* mem)
{
    MemoryManagement::CManager::GetInstance()->HeapFree( mem );
}

inline void* operator new( size_t size, void* place)
{
    return place;
}

inline void operator delete( void*, void* place)
{
}


#if defined(THOT_ENABLE_MEMORY_TRACKING)
#   define THOT_NEW                             MemoryManagement::CNewHandler(__FILE__, __LINE__) * new
#   define THOT_NEW_ARR                         MemoryManagement::CNewArrayHandler(__FILE__, __LINE__) * new    
#   define THOT_DELETE(__ptr)                   delete (MemoryManagement::CDeleteHandler(__FILE__, __LINE__) ^ __ptr )
#   define THOT_DELETE_ARR(__ptr)               delete[] (MemoryManagement::CDeleteArrayHandler(__FILE__, __LINE__) ^ __ptr)
#   define THOT_SAFE_DELETE(__ptr)              do{ THOT_DELETE(__ptr); __ptr = NULL;}while(false)
#   define THOT_FREE( __memory )                MemoryManagement::CManager::GetInstance()->Debug_Free( __memory, __FILE__, __LINE__ )
#   define THOT_MALLOC( __size)                 MemoryManagement::CManager::GetInstance()->Debug_Malloc(__size, __FILE__, __LINE__ )
#   define THOT_MALLOC_TYPE(__size,type)        (type*)MemoryManagement::CManager::GetInstance()->Debug_Malloc(__size, __FILE__, __LINE__ )
#else
#   define THOT_NEW                             new
#   define THOT_NEW_ARR                         new
#   define THOT_DELETE(__ptr)                   do{ delete __ptr;}while(false)
#   define THOT_SAFE_DELETE(__ptr)              do{ THOT_DELETE(__ptr); __ptr = NULL;}while(false)
#   define THOT_DELETE_ARR(__ptr)               do{ delete[] __ptr; }while(false)
#   define THOT_FREE( __memory )                MemoryManagement::CManager::GetInstance()->Free( __memory )
#   define THOT_MALLOC( __size)                 MemoryManagement::CManager::GetInstance()->Malloc(__size )
#   define THOT_MALLOC_TYPE(__size, type)       (type*)MemoryManagement::CManager::GetInstance()->Malloc(__size)
#endif //THOT_ENABLE_MEMORY_TRACKING







#endif //__KERNEL_MEMORY_MANAGEMENT_H__