#include "Kernel_PCH.h"

#include "Kernel/MemoryManagement/FreePool.h"

struct SListNode
{
    u8*         m_nextNode;
};

THOT_COMPILE_ASSERT(sizeof(SListNode) == sizeof(void*));

//--------------------------------------------------------------------------------
CFreePool::CFreePool( u32 elementSize, u32 poolSize, void* buffer )
    : m_elementSize         (elementSize)
    , m_poolSize            (poolSize)
    , m_usedElementCount    (poolSize)
    , m_rawData             (NULL)
    , m_freeHead            (NULL)
    , m_ownRawData          (false)
{
    THOT_ASSERT( elementSize >= sizeof(void*), "ONE ELEMENT MUST HOLD AT LEAST ONE POINTER");

    if(!buffer)
    {
        m_rawData = (u8*)THOT_MALLOC( elementSize * poolSize );
        m_ownRawData = true;
    }
    else
    {
        m_rawData = (u8*)buffer;
        m_ownRawData = false;
    }

    for( u32 i=0; i<poolSize; i++ )
    {
        u8* element = m_rawData + i*elementSize;
        PushFree( element );
    }

}

//--------------------------------------------------------------------------------
void* CFreePool::GetData()
{
    return m_rawData;
}

//--------------------------------------------------------------------------------
const void* CFreePool::GetData()const
{
    return m_rawData;
}

//--------------------------------------------------------------------------------
u32 CFreePool::GetElementSize()
{
    return m_elementSize;
}

//--------------------------------------------------------------------------------
u32 CFreePool::GetUsedElementCount()
{
    return m_usedElementCount;
}

//--------------------------------------------------------------------------------
u32 CFreePool::GetPoolSize()
{
    return m_poolSize;
}

//--------------------------------------------------------------------------------
void* CFreePool::Alloc()
{
    return PopFree();
}

//--------------------------------------------------------------------------------
void CFreePool::Free( void* element)
{
    PushFree(element);
}

//--------------------------------------------------------------------------------
Bool CFreePool::IsFull()const
{
    return m_usedElementCount == m_poolSize;
}

//--------------------------------------------------------------------------------
Bool CFreePool::IsEmpty()const
{
    return m_usedElementCount == 0;
}

//--------------------------------------------------------------------------------
Bool CFreePool::IsPointerFromHere(void* data)const
{
    void* endOfPool = (m_rawData + m_poolSize * m_elementSize);
    return m_rawData <= data && data < endOfPool;
}

//--------------------------------------------------------------------------------
u32 CFreePool::GetMemoryOverhead()const
{
    return (m_poolSize - m_usedElementCount) * m_elementSize + sizeof(CFreePool);
}

//--------------------------------------------------------------------------------
void CFreePool::PushFree(void* element)
{
    THOT_ASSERT( IsPointerFromHere(element) && m_usedElementCount <= m_poolSize );
    SListNode* node = (SListNode*)element;
    node->m_nextNode = m_freeHead;
    m_freeHead = (u8*)node;
    m_usedElementCount--;
}

//--------------------------------------------------------------------------------
void CFreePool::Release()
{
    if(m_rawData && m_ownRawData)
    {
        THOT_FREE(m_rawData);
        m_ownRawData = false;
    }
    
    m_rawData = NULL;
    m_freeHead = NULL;
    m_usedElementCount = 0;
    
}

//--------------------------------------------------------------------------------
u8* CFreePool::PopFree()
{
    if( m_freeHead == NULL)
    {
        THOT_ASSERT(m_usedElementCount == m_poolSize);
        return NULL;
    }

    u8* freeElement = m_freeHead;
    SListNode* node = (SListNode*)m_freeHead;
    m_freeHead = node->m_nextNode;
    m_usedElementCount++;

    return freeElement;
}

//--------------------------------------------------------------------------------
CFreePool::~CFreePool()
{
    Release();
}
