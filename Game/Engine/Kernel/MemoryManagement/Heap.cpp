#include "Kernel_PCH.h"
#include "Heap.h"

#include "Kernel/DebugSystem/Assert.h"
#include "Kernel/KernelUtils.h"
#include "Kernel/ThotWindows.h"
#include "Kernel/Profiler/Profiler.h"

//#define THOT_ENABLE_DEBUG_FREE

#if defined(THOT_ENABLE_DEBUG_FREE)
#   include "Kernel/DebugSystem/StackWalker.h"
#endif



//------------------------------------------------------------------------------------------
CHeap::CHeap ( void* handle)
    :m_nativeHandle (handle)
    ,m_totalMemoryAllocated(0)
{
    if( !Validate() )
    {
        THOT_ASSERT( false, "FAILED TO VALIDATE HEAP");
    }
}

//------------------------------------------------------------------------------------------
CHeap::CHeap( EFlags flags, u64 initialSize, u64 maximumSize )
    : m_nativeHandle        ( NULL )
    , m_totalMemoryAllocated(0)
{
    flags = FLAG_NONE;
    m_nativeHandle = HeapCreate( ThNumericCast<DWORD>(flags), ThNumericCast<SIZE_T>(initialSize), ThNumericCast<SIZE_T>(maximumSize) );
    if( !m_nativeHandle )
    {
        THOT_ASSERT( false, "FAILED TO CREATE A PRIVATE HEAP WITH: flags = [%d], initialSize = [%d], maximumSize = [%d]", flags, initialSize, maximumSize );
    }
}

//------------------------------------------------------------------------------------------
CHeap::~CHeap()
{
    // destroy heap only if it is a private heap created by user
    //if( m_nativeHandle != ms_defaultProcessHeapHandle)
    {
        if( !HeapDestroy( m_nativeHandle ) )
        {
            THOT_ASSERT(false, "FAILED TO DESTROY HEAP");
        }
    }
}

//------------------------------------------------------------------------------------------
void* CHeap::Alloc( u64 size, CHeap::EFlags flags )
{
    m_totalMemoryAllocated += size;
    flags = FLAG_NONE;
    void* memory = HeapAlloc( m_nativeHandle, flags, size );
    THOT_TRAP( memory, "OUT OF MEMORY?");
    return memory;
}

//------------------------------------------------------------------------------------------
void  CHeap::Free( void* memory, CHeap::EFlags flags )
{
    DECLARE_PROFILE_SCOPED_HIT_INFO("CHeap::Free", "memorySize = [%d b], [%.3f kb]", GetBlockSize(memory), bToKb(GetBlockSize(memory)) );
    //THOT_DECLARE_PROFILE("CHeap::Free");

    flags = FLAG_NONE;
    THOT_ASSERT( ValidateBlock( memory), "TRYING TO FREE MEMORY WHICH IS NOT FROM THIS HEAP OR IT WAS CORRUPTED" );

#if defined(THOT_ENABLE_DEBUG_FREE)
    CString stringDebugFree;
    StackWalker::CStackInfo stackInfo;
    StackWalker::CStackInfo::GetCurrentStackInfo(stackInfo);
    stackInfo.DebugGetStringInfo( stringDebugFree );

    THOT_TRACE_LINE("FREE MEMORY[%p] of size[%d] from:\n%s", memory, GetBlockSize(memory), stringDebugFree.c_str() );

#endif


    if( !HeapFree( m_nativeHandle, flags, memory) )
    {
        THOT_ASSERT( false, "FAILED TO ALLOC FROM HEAP");
    }

}

//--------------------------------------------------------------------------------
void* CHeap::StringAlloc( u64 size)
{
    m_totalMemoryAllocated += size;
    EFlags flags = FLAG_NONE;
    void* memory = HeapAlloc( m_nativeHandle, flags, size );
    THOT_TRAP( memory, "OUT OF MEMORY?");
    return memory;
}

//--------------------------------------------------------------------------------
void CHeap::StringFree( void* memory )
{
    CHeap::EFlags flags = FLAG_NONE;
    THOT_ASSERT( ValidateBlock( memory), "TRYING TO FREE MEMORY WHICH IS NOT FROM THIS HEAP OR IT WAS CORRUPTED" );
    if( !HeapFree( m_nativeHandle, flags, memory) )
    {
        THOT_ASSERT( false, "FAILED TO ALLOC FROM HEAP");
    }
}

//------------------------------------------------------------------------------------------
u64 CHeap::GetBlockSize    ( void* memory, CHeap::EFlags flags )
{
    flags = FLAG_NONE;
    u64 size = ThNumericCast<u64>( HeapSize( m_nativeHandle, flags, memory ) );

    return size;
}

//------------------------------------------------------------------------------------------

Bool CHeap::ValidateBlock( void* memory, CHeap::EFlags flags )
{
    flags = FLAG_NONE;
    Bool value = HeapValidate( m_nativeHandle, flags, memory )? true:false;
    return value;
}

//------------------------------------------------------------------------------------------
Bool CHeap::Validate( CHeap::EFlags flags )
{
    flags = FLAG_NONE;
    return HeapValidate( m_nativeHandle, flags, NULL )?true:false;
}

//------------------------------------------------------------------------------------------
