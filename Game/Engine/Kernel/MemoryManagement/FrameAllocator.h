#if !defined(__KERNEL_FRAME_ALLOCATOR__)
#define __KERNEL_FRAME_ALLOCATOR__

#include "Kernel/Basics.h"
#include "Kernel/SingletonLazy.h"

class KERNEL_API CFrameAllocator: public CSingletonLazy<CFrameAllocator>
{
    template<class T> friend class CSingletonLazy;
//*********************************************
//            CONSTR/DESTR
//*********************************************
private:
    CFrameAllocator();
    ~CFrameAllocator();
public:



//*********************************************
//            INTERFACE
//*********************************************
public:
    void*           Alloc               ( thSize size );
    void            Free                ( void* memory );
    void            OnNewFrame          ();
    Bool            IsValidPointer      ( const void* memory );

//*********************************************
//            HELPERS
//*********************************************
private:
    Bool            ValidateAllocatedBlock( void* mem);
    Bool            ValidateBlock( void* memory, thSize size, u8 magicNumber );
    Bool            ValidateHeader();
    Bool            ValidateFooter();
    Bool            Validate();
    void            TraceMagicNumbers();
    void            Reset();

//*********************************************
//            MEMBERS
//*********************************************
private:
    static  const u64       ms_allocatedBlockHeaderSize         = 128;  // header size of every chunck of memory allocated
    static  const u64       ms_allocatedBlockFooterSize         = 128;  // footer size of every chunck of memory allocated
    static  const u8        ms_allocatedBlockFooterMagicNumber  = 0xee; 
    static  const u8        ms_allocatedBlockHeaderMagicNumber  = 0x89; 

    static  const u8        ms_headerMagicNumber        = 0xaa;
    static  const u8        ms_footerMagicNumber        = 0xbb;
    static  const u8        ms_freeMemoryMagicNumber    = 0xfe;
    static  const u64       ms_headerBlockSize          = KB(4);
    static  const u64       ms_footerBlockSize          = KB(4);
    static  const u64       ms_allocatorBlockSize       = MB(4);
    static  const u64       ms_totalBlockSize           = ms_allocatorBlockSize + ms_headerBlockSize + ms_footerBlockSize;

    u8                                          m_rawMemory[ms_totalBlockSize];
    u8*                                         m_headerBegin;
    u8*                                         m_headerEnd;
    u8*                                         m_footerBegin;
    u8*                                         m_footerEnd;
    u8*                                         m_allocatorBegin;
    u8*                                         m_allocatorEnd;
    u64                                         m_currentPos; // relative to m_allocatorBegin;

#if defined(THOT_ENABLE_DEBUG)
    u64                                         m_previousPos;
    u64                                         m_maxPos;
#endif
};





#endif //__KERNEL_FRAME_ALLOCATOR__