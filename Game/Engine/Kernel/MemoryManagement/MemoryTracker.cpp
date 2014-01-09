#include "Kernel_PCH.h"
#include "MemoryTracker.h"
#include "Kernel/DataStructures/CString.h"
#include "Kernel/Utils/StringUtils.h"

#if defined(THOT_ENABLE_MEMORY_TRACKING)

namespace MemoryManagement
{
    //--------------------------------------------------------------------------------
    CTracker::CTracker()
    {
           
    }

    //--------------------------------------------------------------------------------
    CTracker::~CTracker()
    {
        DebugPrintState();
    }

    //---------------------------------------------------------------------------------------
    void CTracker::OnMemoryOperation( const CMemoryOperation& operation )
    {
        CMemoryOperationWrapper wrapperOperation;
        wrapperOperation.m_memoryOperation = operation;
#if defined(THOT_CATCH_MEMORY_OPERATION_STACK)
        StackWalker::CStackInfo::GetCurrentStackInfo( wrapperOperation.m_stackInfo );
#endif

        if( wrapperOperation.m_memoryOperation.m_operation & EMemoryOperation_Allocation )
        {
            THOT_ASSERT( m_memOpMap.find( wrapperOperation.m_memoryOperation.m_realBuffer) == m_memOpMap.end(), "THIS MEMORY OPERATION WAS ALLREADY ADDED" );
            m_memOpMap.insert( TMemOpPair( wrapperOperation.m_memoryOperation.m_realBuffer, wrapperOperation ) );
        }
        else // free memory operation
        {
            TMemOpIterator it =  m_memOpMap.find(wrapperOperation.m_memoryOperation.m_realBuffer);
            THOT_ASSERT( it != m_memOpMap.end(), "FOR A FREE MEMORY OPERATION WE CANNOT FOUND THE ALLOCATION OPERATION" );
            m_memOpMap.erase( it );
        }
    }

    //--------------------------------------------------------------------------------
    void CTracker::DebugGetStateString( CString& outString)
    {
        outString += StringUtils::FormatString( "//////////////////////////////////////////////////////////\n" );
        outString += StringUtils::FormatString( "////////////// MEMORY TRACKER STATE //////////////////////\n" );
        outString += StringUtils::FormatString( "//////////////////////////////////////////////////////////\n" );
        outString += StringUtils::FormatString( "\n" );

        u64 totalUsedMemory = 0;
        u64 totalUsedObjects = 0;
        for( TMemOpIterator it = m_memOpMap.begin(); it != m_memOpMap.end(); ++it )
        {
        const CMemoryOperation& memOperation = it->second.m_memoryOperation;            
        outString += StringUtils::FormatString( "=========== MEMORY OPERATION ============\n" );
        outString += StringUtils::FormatString( "==  m_operation            = [%s]\n", CMemoryOperation::EMemoryOperationToString( memOperation.m_operation ) );
        outString += StringUtils::FormatString( "==  m_bufferSize           = [%d]\n", memOperation.m_bufferSize    );
        outString += StringUtils::FormatString( "==  m_realBufferSize       = [%d]\n", memOperation.m_realBufferSize);
        outString += StringUtils::FormatString( "==  m_buffer               = [%p]\n", memOperation.m_buffer        );
        outString += StringUtils::FormatString( "==  m_realBuffer           = [%p]\n", memOperation.m_realBuffer    );
        outString += StringUtils::FormatString( "==  m_objectCount          = [%d]\n", memOperation.m_objectCount   );
        outString += StringUtils::FormatString( "==  m_fileLine             = [%d]\n", memOperation.m_fileLine      );
        outString += StringUtils::FormatString( "==  m_fileName             = [%s]\n", memOperation.m_fileName      );
        outString += StringUtils::FormatString( "=========================================\n" );
        outString += StringUtils::FormatString( "\n" );

        totalUsedMemory += memOperation.m_realBufferSize;
        totalUsedObjects += memOperation.m_objectCount;
        }

        outString += StringUtils::FormatString( "=============== SUMMARY =================\n" );
        outString += StringUtils::FormatString( "== totalUsedMemory         = [%d b, %.3f kb]\n", totalUsedMemory, bToKb(totalUsedMemory) );
        outString += StringUtils::FormatString( "== totalUsedObjects        = [%d]\n", totalUsedObjects);
        outString += StringUtils::FormatString( "=========================================\n" );

        
        outString += StringUtils::FormatString( "//////////////////////////////////////////////////////////\n" );
        outString += StringUtils::FormatString( "////////////// END MEMORY TRACKER STATE //////////////////\n" );
        outString += StringUtils::FormatString( "//////////////////////////////////////////////////////////\n" );
    }

    //--------------------------------------------------------------------------------
    void CTracker::DebugPrintState()
    {
        CString stringState;
        DebugGetStateString( stringState );
        THOT_TRACE_LINE( "%s", stringState.c_str() );
    }

    //--------------------------------------------------------------------------------

}// namespace MemoryManagement


#endif //THOT_ENABLE_MEMORY_TRACKING