#if !defined(__KERNEL_MEMORY_TRACKER_H__)
#define __KERNEL_MEMORY_TRACKER_H__

#include "Kernel/MemoryManagement/MemoryConfig.h"


#if defined(THOT_MEM_ENABLE_TRACKING)

#include "Kernel/MemoryManagement/MemoryOperation.h"
#include "Kernel/MetaTemplates/MetaTemplates.h"
#include "Kernel/SingletonLazy.h"

#if defined(THOT__MEM_CATCH_OPERATION_STACK)
#   include "Kernel/DebugSystem/StackWalker.h"
#endif 

#include "map"

class CString;
namespace MemoryManagement
{
    ///////////////////////////////////////////////////////////////////////////
    //          MAIN CLASS USED TO TRACK ALL MEMORY ALLOCATIONS/DEALLOCATIONS
    //////////////////////////////////////////////////////////////////////////
    class CTracker: public CSingletonLazy<CTracker>
    {
        class CMemoryOperationWrapper
        {
        public:
            CMemoryOperation            m_memoryOperation;

#if defined(THOT__MEM_CATCH_OPERATION_STACK)
            StackWalker::CStackInfo     m_stackInfo;
#endif
        };
    

    public:
        CTracker();
        ~CTracker();

    public:
        void    OnMemoryOperation      ( const CMemoryOperation& operation );

    private:
        void        DebugPrintState();
        void        DebugGetStateString( CString& outString);

    private:
        typedef std::pair<void*, CMemoryOperationWrapper>   TMemOpPair;
        typedef std::map<void*, CMemoryOperationWrapper>    TMemOpMap;
        typedef TMemOpMap::iterator                         TMemOpIterator;
        typedef TMemOpMap::const_iterator                   TMemOpConstIterator;

        TMemOpMap           m_memOpMap;
    };


}// namespace MemoryManagement

#endif //THOT_MEM_ENABLE_TRACKING

#endif //__KERNEL_MEMORY_TRACKER_H__