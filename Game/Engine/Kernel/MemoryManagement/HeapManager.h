#if !defined(__KERNEL_HEAP_MANAGER_H__)
#define __KERNEL_HEAP_MANAGER_H__


#include "Kernel/KernelDef.h"
#include "Kernel/MemoryManagement/Heap.h"

namespace MemoryManagement
{

    class KERNEL_API CHeapManager
    {

    public:
        static CHeapManager*       GetInstance();
        static CHeapManager*       CreateInstance();
        static void                DestroyInstance();
    
    //*********************************************
    //            CONSTR/DESTR
    //*********************************************
    public:
        CHeapManager();

    //*********************************************
    //            INTERFACE
    //*********************************************
    public:
        void*       Alloc( size_t size);
        void        Free( void* ptr);
        size_t      GetBlockSize( void* ptr );
        Bool        IsPointerFromHere( void* ptr );
    
    
    //*********************************************
    //            MEMBERS
    //*********************************************
    protected:
        CHeap   m_defaultHeap;
    };



}



#endif //__KERNEL_HEAP_MANAGER_H__