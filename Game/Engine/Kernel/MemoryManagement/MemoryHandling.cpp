#include "Kernel_PCH.h"
#include "MemoryHandling.h"

#include "Kernel/DebugSystem/Assert.h"
#include "Kernel/MemoryManagement/MemoryOperation.h"

#if defined(THOT_MEM_ENABLE_TRACKING)
#   include "Kernel/MemoryManagement/MemoryStatistics.h"
#endif //THOT_MEM_ENABLE_TRACKING

#if defined(THOT_MEM_ENABLE_STATISTICS)
#   include "Kernel/MemoryManagement/MemoryTracker.h"
#endif //THOT_MEM_ENABLE_STATISTICS

#include "string.h"


namespace MemoryManagement
{

    

    void CMemoryOperationHandler::AddMemoryOperation( const CMemoryOperation& operation )
    {
        THOT_ASSERT( operation.m_fileLine != 0, "MEMORY OPERATION INCOMPLETE" );
        THOT_ASSERT( operation.m_fileName[0] != 0, "MEMORY OPERATION INCOMPLETE" );

#if defined(THOT_MEM_ENABLE_TRACKING)
        CTracker::GetInstance()->OnMemoryOperation( operation );
#endif //THOT_MEM_ENABLE_TRACKING

#if defined(THOT_MEM_ENABLE_STATISTICS)
        CMemoryStatistics::GetInstance()->OnMemoryOperation( operation );
#endif //THOT_MEM_ENABLE_STATISTICS
    }


        CMemoryOperationHandler* CMemoryOperationHandler::GetInstance()
        {
            static CMemoryOperationHandler instance;
            return &instance;
        }
        
        CMemoryOperationHandler* CMemoryOperationHandler::CreateInstance()
        {
            return GetInstance();
        }
        
        void CMemoryOperationHandler::DestroyInstance()
        {
        }

        CNewDeleteHandlerBase::CNewDeleteHandlerBase( const char* file, u64 line )
        : m_line    ( line )
        {
            strcpy( m_file, file );
        }


}// namespace MemoryManagement