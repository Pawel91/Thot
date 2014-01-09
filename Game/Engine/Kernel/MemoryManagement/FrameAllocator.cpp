#include "Kernel_PCH.h"
#include "Kernel/MemoryManagement/FrameAllocator.h"

#if defined(THOT_ENABLE_DEBUG)
#   define THOT_ENABLE_DEBUG_FRAME_ALLOCATOR
#endif

//--------------------------------------------------------------------------------
CFrameAllocator::CFrameAllocator()
    :m_headerBegin          ( 0 )
    ,m_headerEnd            ( 0 )
    ,m_footerBegin          ( 0 )
    ,m_footerEnd            ( 0 )
    ,m_allocatorBegin       ( 0 )
    ,m_allocatorEnd         ( 0 )
    ,m_currentPos           ( 0 )
#if defined(THOT_ENABLE_DEBUG_FRAME_ALLOCATOR)
    ,m_maxPos               ( 0 )
    ,m_previousPos          ( 0 )
#endif
{
    //setup pointer
    m_headerBegin           = m_rawMemory;
    m_headerEnd             = m_rawMemory + ms_headerBlockSize;
    m_allocatorBegin        = m_headerEnd;
    m_allocatorEnd          = m_allocatorBegin + ms_allocatorBlockSize;
    m_footerBegin           = m_allocatorEnd;
    m_footerEnd             = m_footerBegin + ms_footerBlockSize;

    THOT_ASSERT( (m_headerEnd - m_headerBegin) == ms_headerBlockSize );
    THOT_ASSERT( (m_footerEnd - m_footerBegin) == ms_footerBlockSize );

    // setup magic number
    Memory::Set( m_headerBegin, ms_headerBlockSize, ms_headerMagicNumber );
    Memory::Set( m_footerBegin, ms_footerBlockSize, ms_footerMagicNumber );
    Memory::Set(m_allocatorBegin, ms_allocatorBlockSize, ms_freeMemoryMagicNumber);

    Validate();
}

//--------------------------------------------------------------------------------
void CFrameAllocator::OnNewFrame()
{
    Reset();
}

//--------------------------------------------------------------------------------
Bool CFrameAllocator::IsValidPointer( const void* memory)
{
    if( memory >= m_allocatorBegin && memory < m_allocatorEnd )
    {
        return true;
    }

    return false;
}

//--------------------------------------------------------------------------------
Bool CFrameAllocator::ValidateBlock( void* memory, thSize size, u8 magicNumber )
{
    THOT_ASSERT( memory >= m_headerBegin && memory <= m_footerEnd, "MEMORY[%p] IS NOT FROM THIS ALLOCATOR", memory );
    u8* memoryEnd = (u8*)memory + size;
    for( u8* ptr = (u8*)memory; ptr!=memoryEnd; ++ptr )
    {
        if( (*ptr) != magicNumber )
        {
#if defined(THOT_ENABLE_DEBUG)
            TraceMagicNumbers();
#endif
            THOT_ASSERT(    false, "MEMORY BLOCK FRAME ALLOCATION VALIDATION FAILED AT[%p] WITH PARAMETER:\nMEMORY=[%p]\nMEMORY END=[%p]\nSIZE=[%d]\nMAGIC NUMBER=[%p]\nOFFSET=[%p]", 
                            ptr, memory, memoryEnd, size, (void*)magicNumber, ptr - m_headerBegin );
            return false;
        }
    }

    return true;
}

//--------------------------------------------------------------------------------
void CFrameAllocator::TraceMagicNumbers()
{
    THOT_TRACE_LINE("CFrameAllocator MAGIC NUMBERS");
    THOT_TRACE_LINE("ms_allocatedBlockFooterMagicNumber=    [%p]", ms_allocatedBlockFooterMagicNumber);
    THOT_TRACE_LINE("ms_allocatedBlockHeaderMagicNumber=    [%p]", ms_allocatedBlockHeaderMagicNumber);
    THOT_TRACE_LINE("ms_headerMagicNumber=                  [%p]", ms_headerMagicNumber);
    THOT_TRACE_LINE("ms_footerMagicNumber=                  [%p]", ms_footerMagicNumber);
    THOT_TRACE_LINE("ms_freeMemoryMagicNumber=              [%p]", ms_freeMemoryMagicNumber);
}

//--------------------------------------------------------------------------------
Bool CFrameAllocator::ValidateHeader( )
{
    return ValidateBlock( m_headerBegin, ms_headerBlockSize, ms_headerMagicNumber );
}

//--------------------------------------------------------------------------------
Bool CFrameAllocator::ValidateFooter( )
{
    return ValidateBlock( m_footerBegin, ms_footerBlockSize, ms_footerMagicNumber );
}

//--------------------------------------------------------------------------------
Bool CFrameAllocator::Validate()
{
    if( !ValidateHeader() || !ValidateFooter())
    {
        return false;
    }

    return true;
}

//--------------------------------------------------------------------------------
void CFrameAllocator::Reset()
{
    Memory::Set(m_allocatorBegin, ms_allocatorBlockSize, ms_freeMemoryMagicNumber);
    m_currentPos = 0;
}

//--------------------------------------------------------------------------------
CFrameAllocator::~CFrameAllocator()
{
    Validate();
}

//--------------------------------------------------------------------------------
void* CFrameAllocator::Alloc( thSize size )
{
#if defined(THOT_ENABLE_DEBUG_FRAME_ALLOCATOR)
    Validate();
#endif

    if( m_currentPos + size + ms_allocatedBlockHeaderSize + ms_allocatedBlockFooterSize >= ms_allocatorBlockSize )
    {
        THOT_TRACE_LINE( "CFrameAllocator OVERFLOW" );
        return NULL;
    }

    u8* header = m_allocatorBegin + m_currentPos;
    u8* memory = header + ms_allocatedBlockHeaderSize;
    u8* footer = memory + size;

#if defined(THOT_ENABLE_DEBUG_FRAME_ALLOCATOR)
    //validate previous footer
    u8* previousFooter = header - ms_allocatedBlockFooterSize;
    if( m_currentPos > 0 )
    {
        ValidateBlock( previousFooter, ms_allocatedBlockFooterSize, ms_allocatedBlockFooterMagicNumber );
    }

    Memory::Set( header, ms_allocatedBlockHeaderSize, ms_allocatedBlockHeaderMagicNumber );
    Memory::Set( footer, ms_allocatedBlockFooterSize, ms_allocatedBlockFooterMagicNumber );
#endif


#if defined(THOT_ENABLE_DEBUG_FRAME_ALLOCATOR)
    m_previousPos = m_currentPos;
#endif //THOT_ENABLE_DEBUG_FRAME_ALLOCATOR
    m_currentPos += ms_allocatedBlockHeaderSize + ms_allocatedBlockFooterSize + size;

#if defined(THOT_ENABLE_DEBUG_FRAME_ALLOCATOR)
    if( m_currentPos > m_maxPos )
    {
        m_maxPos = m_currentPos;
    }
#endif

    return memory;
}

//--------------------------------------------------------------------------------
Bool CFrameAllocator::ValidateAllocatedBlock( void* mem)
{
    THOT_ASSERT( IsValidPointer(mem) );
    void* header = (u8*)mem - ms_allocatedBlockHeaderSize;
    return ValidateBlock( header, ms_allocatedBlockHeaderSize, ms_allocatedBlockHeaderMagicNumber );
}

//--------------------------------------------------------------------------------
void CFrameAllocator::Free( void* memory )
{
#if defined(THOT_ENABLE_DEBUG_FRAME_ALLOCATOR)
    ValidateAllocatedBlock(memory);
#endif
}

//--------------------------------------------------------------------------------
