#if !defined( __KERNEL_MEMORY_STATISTICS_H__)
#define __KERNEL_MEMORY_STATISTICS_H__


#include "Kernel/DataTypes.h"
#include "Kernel/Defines.h"
#include "Kernel/SingletonLazy.h"
#include "Kernel/Memory/Memory.h"
#include "Kernel/MemoryManagement/MemoryOperation.h"
    
namespace MemoryManagement
{

    class CMemoryStatistics:public CSingletonLazy<CMemoryStatistics>
    {
    public:
        struct SData
        {
            SData()
            {
                Memory::Set(this, sizeof(SData), 0 );
            }

            u64         m_nNewCalls;
            u64         m_nNewArrCalls;
            u64         m_ndeleteCalls;
            u64         m_ndeleteArrCalls;
            u64         m_nMallocCalls;
            u64         m_nFreeCalls;
            u64         m_nMaxMemRequest;
            u64         m_nMaxMemory;
            u64         m_nCurrentMemory;
            u64         m_nTotalAllocatedMemory;
            u64         m_nObjectsAllocatedByNew;
            u64         m_nCurrentAllocatedObjects;
        };

    public:

         CMemoryStatistics();
        ~CMemoryStatistics();
    public:

        void        OnMemoryOperation   ( const CMemoryOperation& operation );


    private:

    private:

        SData       m_data;
    };

}// namespace MemoryManagement




#endif //__KERNEL_MEMORY_STATISTICS_H__