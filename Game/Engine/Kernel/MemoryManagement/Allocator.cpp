#include "Kernel_PCH.h"
#include "Kernel/MemoryManagement/Allocator.h"

//--------------------------------------------------------------------------------
CAllocatorBase::CAllocatorBase( void* owner)
    : m_owner           (owner)
{

}

//--------------------------------------------------------------------------------
CSmartAllocator::CSmartAllocator( const CSmartAllocator& other )
    : super             ( other.m_owner )
    , m_isOwnerOnStack  (other.m_isOwnerOnStack)
{
}

//--------------------------------------------------------------------------------
CSmartAllocator::CSmartAllocator( void* owner)
    : super                 (owner)
    , m_isOwnerOnStack      (false)
{
    m_isOwnerOnStack = IsPointerOnStack( m_owner );
}

//--------------------------------------------------------------------------------
void* CSmartAllocator::Alloc( thSize size )
{
    void* memory = NULL;
    if( m_isOwnerOnStack)
    {
        memory = CFrameAllocator::GetInstance()->Alloc( size );
    }

    if( !memory )
    {
        memory = THOT_MALLOC( size );
    }

    return memory;
}

//--------------------------------------------------------------------------------
void  CSmartAllocator::Free( void* memory )
{
    if( CFrameAllocator::GetInstance()->IsValidPointer(memory) )
    {
        CFrameAllocator::GetInstance()->Free( memory );
    }
    else
    {
        THOT_FREE( memory );        
    }
}

//--------------------------------------------------------------------------------
void* CSmartAllocator::AllocAlign( thSize size, thSize alignment )
{
    return Alloc( size );
}

//--------------------------------------------------------------------------------
void  CSmartAllocator::FreeAlign( void* mem )
{
    Free(mem);
}
