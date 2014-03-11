#include "Kernel_PCH.h"

#include "Kernel/MemoryManagement/Bucket.h"
#include "Kernel/MemoryManagement/HeapManager.h"
#include "Kernel/Profiler/Profiler.h"

#include "map"


namespace MemoryManagement
{

class CBucketNode
{
    friend class CBucket;
public:
    CBucketNode( u32 elementSize, u32 poolSize)
        : m_previous    (NULL)
        , m_next        (NULL)
        , m_freePool    (NULL)
    {}

    THOT_FORCE_INLINE    CFreePool& GetFreePool(){return *m_freePool;}

private:

    CFreePool*          m_freePool; //does not own the pool
    //this are for the ordered list; the list is ordered by the number of used elements;
    CBucketNode*        m_previous;
    CBucketNode*        m_next;
};

//--------------------------------------------------------------------------------
CBucket::CBucket( u32 elementSize, u32 chunkSize )
    : m_elementSize     (elementSize)
    , m_chunkSize       (chunkSize)
    , m_head            (NULL)
    , m_tail            (NULL)
    , m_maxCountNode    (NULL)
#if defined(BUCKET_DEBUG)
    , m_usedElements          (0)  
    , m_totalAllocatedMemory  (0)
#endif
{
    m_head = m_tail = m_maxCountNode = GetNewNode();
}

//--------------------------------------------------------------------------------
CBucket::~CBucket()
{
    for( CBucketNode* node = m_head; node!=NULL; node = node->m_next )
    {
        DeleteNode(node);
    }
}

//--------------------------------------------------------------------------------
void* CBucket::InternalAlloc(thSize size)
{
    return CHeapManager::GetInstance()->Alloc(size);
}

//--------------------------------------------------------------------------------
void CBucket::DeleteNode( CBucketNode* node)
{
    if(node)
    {
        InternalFree( node->GetFreePool().GetData() );
        node->GetFreePool().~CFreePool();
        InternalFree(node->m_freePool);
        node->~CBucketNode();//call the destructor;
        InternalFree(node);//free the memory;
    }
}

//--------------------------------------------------------------------------------
CBucketNode* CBucket::GetNewNode()
{
    CBucketNode* node = new( InternalAlloc(sizeof(CBucketNode)) ) CBucketNode( m_elementSize, m_chunkSize);
    node->m_freePool = new(InternalAlloc(sizeof(CFreePool))) CFreePool( m_elementSize, m_chunkSize, InternalAlloc(m_elementSize*m_chunkSize) );

    return node;
}

//--------------------------------------------------------------------------------
void CBucket::InternalFree( void* ptr)
{
    CHeapManager::GetInstance()->Free( ptr);
}

//--------------------------------------------------------------------------------
Bool CBucket::IsPointerFromHere(void* ptr)
{
    THOT_DECLARE_PROFILE("CBucket::IsPointerFromHere");
    for( CBucketNode* node = m_head; node != NULL; node = node->m_next)
    {
        if( node->GetFreePool().IsPointerFromHere(ptr) )
        {
            return true;
        }
    }

    return false;
}

//--------------------------------------------------------------------------------
void* CBucket::Alloc()
{
    THOT_ASSERT( m_head!=NULL && m_head!= NULL && m_tail!=NULL );
    THOT_ASSERT( m_maxCountNode->m_next == NULL || m_maxCountNode->m_next->GetFreePool().IsFull() );// next node of max count node must be null or full;
    THOT_DECLARE_PROFILE("CBucket::Alloc");

#if defined(BUCKET_DEBUG)
    m_usedElements++;
#endif

    if( m_maxCountNode->GetFreePool().IsFull() )
    {
        // if the max count node is full and the previous is null then this bucket is full and we need another pool
        if( m_maxCountNode->m_previous == NULL )
        {
            THOT_ASSERT( m_maxCountNode == m_head );
            CBucketNode* node = GetNewNode();
            m_head = node;
            node->m_next = m_maxCountNode;
            m_maxCountNode->m_previous = node;
            m_maxCountNode = node;
            return m_maxCountNode->GetFreePool().Alloc();
        }
        else
        {
            m_maxCountNode = m_maxCountNode->m_previous;
            THOT_ASSERT(m_maxCountNode->GetFreePool().IsFull() == false, "THE PREVIOUS NODE OF MAX COUNT NODE MUST NOT BE FULL");
            return m_maxCountNode->GetFreePool().Alloc();
        }
    }
    else // max count node is not full
    {
        return m_maxCountNode->GetFreePool().Alloc();
    }
}

//--------------------------------------------------------------------------------
CBucketNode* CBucket::FindBucketNodeForElement( void* allocatedElement )
{
    //[TODO] find a way to optmize this functions; now is O(n) but O(log(n)) would be better
    THOT_DECLARE_PROFILE( "CBucket::FindBucketNodeForElement");

    for( CBucketNode* node = m_head; node != NULL; node = node->m_next )
    {
        if( node->GetFreePool().IsPointerFromHere( allocatedElement) )
        {
            return node;
        }
    }

    THOT_ASSERT(false, "ELEMENT NOT FOUND");
    return NULL;
}

//--------------------------------------------------------------------------------
void CBucket::SwapPools(CBucketNode* one, CBucketNode* other)
{
    //just swap the pointer to pool;
    ThSwap( one->m_freePool, other->m_freePool );
}

//--------------------------------------------------------------------------------
void CBucket::Free(void* element)
{
#if defined(BUCKET_DEBUG)
    m_usedElements--;
#endif

    THOT_DECLARE_PROFILE("CBucket::Free");
    THOT_ASSERT(element != NULL);
    CBucketNode* node = FindBucketNodeForElement(element);
    THOT_ASSERT(node!=NULL);

    Bool wasFull = node->GetFreePool().IsFull();
    node->GetFreePool().Free(element);
    
    // if is empty then is the header and is a candidate for deletion
    if( node->GetFreePool().IsEmpty() )
    {
        THOT_ASSERT( node->m_previous == NULL && m_head == node);

        //don`t delete the last node;
        if( m_head->m_next )
        {
            m_head = m_head->m_next;
            DeleteNode( node );
        }
        return;
    }

    if( node->m_previous == NULL )
    {
        THOT_ASSERT( node == m_head );
        // if there is no previous then this node is the head, with the smallest nb of used elements
        return;
    }

    // while because the node could be one of the last nodes that are full;
    while( node->m_previous &&  (node->m_previous->GetFreePool().GetUsedElementCount() > node->GetFreePool().GetUsedElementCount() ) )// this 2 nodes must be rearranged
    {
        if( node == m_maxCountNode )
        {
            m_maxCountNode = node->m_previous;
        }

        if( node->m_previous == m_head )
        {
            m_head = node; 
        }

        SwapPools(node->m_previous, node);
        node = node->m_previous;
    }

    THOT_ASSERT(VerifyList()==true);
}

//--------------------------------------------------------------------------------
Bool CBucket::VerifyList()
{
    if( m_head->m_previous != NULL )
    {
        return false;
    }

    if( m_tail->m_next != NULL )
    {
        return false;
    }

    //verify order
    for( CBucketNode* node = m_head->m_next; node!=NULL; node=node->m_next )
    {
        if( node->GetFreePool().GetUsedElementCount() > node->m_previous->GetFreePool().GetUsedElementCount() )
        {
            return false;
        }
    }

    return true;
}

}//namespace MemoryManager