#if !defined(__KERNEL_HEAP_H__)
#define __KERNEL_HEAP_H__


#include "Kernel/DataTypes.h"
#include "Kernel/KernelDef.h"

//[TODO] make interface private and friend with CMemoryManager;
class KERNEL_API CHeap
{

public:
// native flags from http://msdn.microsoft.com/en-us/library/windows/desktop/aa366599(v=vs.85).aspx
enum EFlags
{

     FLAG_NONE                  = 0
    ,FLAG_NO_LOCK               = 0x00000001 
    ,FLAG_ENABLE_EXECUTE        = 0x00040000
    ,FLAG_GENERATE_EXEPTIONS    = 0x00000004
    ,FLAG_ZERO_MEMORY           = 0x00000008 // used only at alloc
};


public:
    CHeap ( void* handle); // wraps a allready created heap; for example the default process heap;
    CHeap ( EFlags flags, u64 initialSize, u64 maximumSize = 0 ); // creates a new heap
    ~CHeap();

public:

    void*           StringAlloc     ( u64 size);
    void            StringFree      ( void* memory );

    void*           Alloc           ( u64 size, EFlags flags = FLAG_NO_LOCK );
    void            Free            ( void* memory, EFlags flags = FLAG_NO_LOCK );
    u64             GetBlockSize    ( void* memory, EFlags flags = FLAG_NO_LOCK );
    Bool            ValidateBlock   ( void* memory, EFlags flags = FLAG_NO_LOCK );
    Bool            Validate        (  EFlags flags = FLAG_NO_LOCK  ); // validates the entire heap


private:
    u64             m_totalMemoryAllocated;
    void*           m_nativeHandle;

};


#endif //__KERNEL_HEAP_H__