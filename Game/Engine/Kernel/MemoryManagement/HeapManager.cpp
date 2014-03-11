#include "Kernel_PCH.h"

#include "Kernel/MemoryManagement/HeapManager.h"


namespace MemoryManagement
{

//--------------------------------------------------------------------------------
CHeapManager* CHeapManager::GetInstance()
{
    static CHeapManager heapManager;
    return &heapManager;
}

//--------------------------------------------------------------------------------  
CHeapManager* CHeapManager::CreateInstance()
{
    return GetInstance();
}

//--------------------------------------------------------------------------------
void CHeapManager::DestroyInstance()
{
}

//--------------------------------------------------------------------------------
CHeapManager::CHeapManager()
    : m_defaultHeap( CHeap::FLAG_NO_LOCK, 1 * 1024 * 1024 * 1024, 0 )
{
}

//--------------------------------------------------------------------------------
void* CHeapManager::Alloc( size_t size)
{
    return m_defaultHeap.Alloc( size );
}

//--------------------------------------------------------------------------------
void CHeapManager::Free( void* ptr)
{
    THOT_ASSERT(m_defaultHeap.ValidateBlock(ptr), "TRYING TO FREE INVALID BLOCK");
    m_defaultHeap.Free( ptr );
}

//--------------------------------------------------------------------------------
size_t CHeapManager::GetBlockSize( void* ptr )
{
    return m_defaultHeap.GetBlockSize(ptr);
}

//--------------------------------------------------------------------------------
Bool CHeapManager::IsPointerFromHere(void* ptr)
{
    return m_defaultHeap.ValidateBlock( ptr );
}


}//namespace MemoryManagement
