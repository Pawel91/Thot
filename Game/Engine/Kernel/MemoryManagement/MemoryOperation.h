#if !defined(__KERNEL_MEMORY_OPERATION_H__)
#define __KERNEL_MEMORY_OPERATION_H__


#include "Kernel/Basics.h"
#include "Kernel/Memory/Memory.h"


namespace MemoryManagement
{
    class CManager;

    enum EMemoryOperation
    {
        EMemoryOperation_None = 0
        
        ,EMemoryOperation_Malloc        = 1<<1
        ,EMemoryOperation_New           = 1<<2
        ,EMemoryOperation_NewArray      = 1<<3

        ,EMemoryOperation_Free          = 1<<4
        ,EMemoryOperation_Delete        = 1<<5
        ,EMemoryOperation_DeleteArray   = 1<<6

        ,EMemoryOperation_Allocation    = EMemoryOperation_Malloc | EMemoryOperation_New | EMemoryOperation_NewArray
        ,EMemoryOperation_Remove        = EMemoryOperation_Free | EMemoryOperation_Delete | EMemoryOperation_DeleteArray
        ,EMemoryOperation_All           = 0xFFFFFFFF
    };

    class CMemoryOperation
    {
    public:
        friend class MemoryManagement::CManager;

        inline CMemoryOperation()
        {
            Memory::Set( this, sizeof(CMemoryOperation), 0 );
        }

    public:
        static const char*     EMemoryOperationToString( EMemoryOperation op  );

    public:
        EMemoryOperation            m_operation;
        u64                         m_bufferSize;
        u64                         m_realBufferSize;
        void*                       m_buffer;
        void*                       m_realBuffer;
        u64                         m_objectCount; // only if operation is new or delete
        u64                         m_fileLine;
        char                        m_fileName[256];
    };


}// namespace MemoryManagement

#endif //__KERNEL_MEMORY_OPERATION_H__