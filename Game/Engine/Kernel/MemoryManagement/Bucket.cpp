#include "Kernel_PCH.h"

#include "Kernel/MemoryManagement/Bucket.h"
#include "Kernel/MemoryManagement/BucketPool.h"
#include "Kernel/MemoryManagement/HeapManager.h"
#include "Kernel/Profiler/Profiler.h"

#include "map"

#if defined(BUCKET_DEBUG)
#   define VERIFY_BUCKET_LIST() THOT_ASSERT(VerifyList()==true, "INTERNAL LIST VALIDATION FAILS")
#   define BUCKET_LIST_ASSERT( __expr, ...) do{if(!(__expr)){DumpList();*((int*)0) = 13;}THOT_ASSERT(__expr, __VA_ARGS__);}while(false)
#   define BUCKET_TRACE(__expr, ...) THOT_TRACE_LINE(__expr, __VA_ARGS__)
#else
#   define BUCKET_LIST_ASSERT( __expr, ...) void()
#   define VERIFY_BUCKET_LIST() void()
#   define BUCKET_TRACE(__expr, ...) void()
#endif

#if defined(BUCKET_DEBUG)
//#   define DUMP_LIST DumpList
#   define DUMP_LIST void
#else
#   define DUMP_LIST void
#endif

namespace MemoryManagement
{

class CBucketNode
{
    friend class CBucket;
public:
    CBucketNode(u32 elementSize)
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
CBucket::CBucket( u32 elementSize, CBucketPool* bucketPool)
    : m_elementSize     (elementSize)
    , m_head            (NULL)
    , m_tail            (NULL)
    , m_maxCountNode    (NULL)
    , m_ownerBucketPool (bucketPool)
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
    for( CBucketNode* node = m_head; node!=NULL;)
    {
        CBucketNode* toDelete = node;
        toDelete->m_next = NULL;
        node = node->m_next;
        m_head = node;
        m_tail = toDelete == m_tail?NULL:m_tail;
        if(node)
        {
            node->m_previous = NULL;

        }

#if defined(BUCKET_DEBUG)
        if(toDelete->GetFreePool().GetUsedElementCount())
        {
            BUCKET_TRACE("MEMORY LEAK DETECTED");
        }
#endif

        DeleteNode(toDelete);
    }
}

//--------------------------------------------------------------------------------
void CBucket::DeleteNode( CBucketNode* node)
{
    THOT_ASSERT(node);
    if(node)
    {
        THOT_ASSERT( !(m_head == m_tail)? (node!=m_head && node!=m_tail && node!=m_maxCountNode) : true, "DANGLING POINTERS DETECTED" );
        THOT_ASSERT( node->m_next? node->m_next->m_previous != node: true, "DANGLING POINTERS DETECTED" );
        THOT_ASSERT( node->m_previous? node->m_previous->m_next != node : true, "DANGLING POINTERS DETECTED" );

        node->m_freePool->~CFreePool();
        node->~CBucketNode();
        m_ownerBucketPool->FreePage(this, node);
    }
}

//--------------------------------------------------------------------------------
CBucketNode* CBucket::GetNewNode()
{
    CBucketPool::SPage page = m_ownerBucketPool->AllocPage( this );

    if( !page.m_pageAdrees )
    {
        return NULL;
    }

    u8* memory = (u8*)page.m_pageAdrees;
    u32 reservedMemory = sizeof(CBucketNode) + sizeof(CFreePool);
    CBucketNode* node = new(memory) CBucketNode(m_elementSize);
    memory += sizeof(CBucketNode);
    u32 poolSize = (page.m_size - reservedMemory) / m_elementSize;
    node->m_freePool = new(memory) CFreePool( m_elementSize,  poolSize, memory + sizeof(CFreePool) );
    return node;
}

//--------------------------------------------------------------------------------
u32 CBucket::GetElementSize()
{
    return m_elementSize;
}

//--------------------------------------------------------------------------------
Bool CBucket::Validate(void* pageAdress, void* ptr)
{
    CBucketNode* node = (CBucketNode*)pageAdress;
    return node->GetFreePool().Validate(ptr);
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
    // we try to allocate from the page with max element count

    THOT_ASSERT( m_head!=NULL && m_head!= NULL && m_tail!=NULL );
    THOT_ASSERT( m_maxCountNode->m_next == NULL || m_maxCountNode->m_next->GetFreePool().IsFull() );// next node of max count node must be null or full;
    //THOT_DECLARE_PROFILE("CBucket::Alloc");
    VERIFY_BUCKET_LIST();
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
            if( !node )
            {
                return NULL;
            }

            m_head = node;
            node->m_next = m_maxCountNode;
            m_maxCountNode->m_previous = node;
            m_maxCountNode = node;

            VERIFY_BUCKET_LIST();
            return m_maxCountNode->GetFreePool().Alloc();
        }
        else
        {
            m_maxCountNode = m_maxCountNode->m_previous;
            THOT_ASSERT(m_maxCountNode->GetFreePool().IsFull() == false, "THE PREVIOUS NODE OF MAX COUNT NODE MUST NOT BE FULL");
            VERIFY_BUCKET_LIST();
            return m_maxCountNode->GetFreePool().Alloc();
        }
    }
    else // max count node is not full
    {
        VERIFY_BUCKET_LIST();
        void* element = m_maxCountNode->GetFreePool().Alloc();

        //but if is full now and we have other nodes
        if( m_maxCountNode->GetFreePool().IsFull() && m_maxCountNode->m_previous )
        {
            m_maxCountNode = m_maxCountNode->m_previous;
        }
        VERIFY_BUCKET_LIST();

        return element;
    }
}

//--------------------------------------------------------------------------------
void CBucket::SwapNodes(CBucketNode* p, CBucketNode* q)
{
    // verify if we swap head or tail
    if( p == m_tail)
    {
        m_tail = q;
    }
    else if( q == m_tail )
    {
        m_tail = p;
    }

    if( p == m_head)
    {
        m_head = q;
    }
    else if( q == m_head )
    {
        m_head = p;
    }

    //begin the actual swapping
    if( p->m_next != q && p->m_previous != q )
    {
        CBucketNode* p_prev = p->m_previous;
        CBucketNode* p_next = p->m_next;
        CBucketNode* q_prev = q->m_previous;
        CBucketNode* q_next = q->m_next;

        q->m_next = p_next;
        q->m_previous = p_prev;

        p->m_previous = q_prev;
        p->m_next = q_next;

        if( p_prev )
        {
            p_prev->m_next = q;
        }

        if( p_next )
        {
            p_next->m_previous = q;
        }

        if( q_prev )
        {
            q_prev->m_next = p;
        }

        if( q_next )
        {
            q_next->m_previous = p;
        }
    }
    else
    {
        // let 'p' be the first node and 'q' the second
        if( ! (p->m_next == q ) )
        {
            ThSwap(p,q);
        }

        CBucketNode* p_prev = p->m_previous;
        CBucketNode* q_next = q->m_next;

        p->m_previous = q;
        p->m_next = q_next;

        q->m_next = p;
        q->m_previous = p_prev;

        if( p_prev )
        {
            p_prev->m_next = q;
        }

        if(q_next)
        {
            q_next->m_previous = p;
        }
    }
}

//--------------------------------------------------------------------------------
void CBucket::Free( void* pageAdress, void* element)
{
#if defined(BUCKET_DEBUG)
    m_usedElements--;
#endif

    THOT_DECLARE_PROFILE("CBucket::Free");
    THOT_ASSERT(element != NULL);
    CBucketNode* node = (CBucketNode*)pageAdress;
    THOT_ASSERT(node!=NULL);

    VERIFY_BUCKET_LIST();
    Bool wasFull = node->GetFreePool().IsFull();
    node->GetFreePool().Free(element);

    // if is empty then is a candidate for deletion
    if( node->GetFreePool().IsEmpty() )
    {
        BUCKET_LIST_ASSERT( node->m_previous? (node->m_previous->GetFreePool().GetUsedElementCount() == 1) : true );

        //don`t delete the last node;
        //if( m_head->m_next )
        //{
        //    m_head = m_head->m_next;
        //    m_head->m_previous = NULL;
        //    DeleteNode( node );
        //    VERIFY_BUCKET_LIST();
        //}

        //don`t delete the last node
        if( node->m_previous || node->m_next )
        {
            if( node != m_head )
            {
                SwapNodes(m_head, node);
                THOT_ASSERT(node->m_previous == NULL);
                m_head = node->m_next;
                m_head->m_previous = NULL;
                node->m_next = NULL;
            }
            else
            {
                THOT_ASSERT(node->m_previous == NULL);
                m_head = m_head->m_next;
                m_head->m_previous = NULL;
                node->m_next = NULL;
            }

            DeleteNode(node);
            VERIFY_BUCKET_LIST();
        }
        VERIFY_BUCKET_LIST();
        return;
    }

    //if we free from maxCountNode;
    if( node == m_maxCountNode )
    {
        if( m_maxCountNode->m_previous && (m_maxCountNode->m_previous->GetFreePool().GetUsedElementCount() > m_maxCountNode->GetFreePool().GetUsedElementCount()) )
        {
            m_maxCountNode = m_maxCountNode->m_previous;
        }
    }

    if(wasFull)
    {
        m_maxCountNode = node;
    }

    DUMP_LIST();
    // reorder the list
    // while because the node could be one of the last nodes that are full;
    while( node->m_previous &&  (node->m_previous->GetFreePool().GetUsedElementCount() > node->GetFreePool().GetUsedElementCount()) )// this 2 nodes must be rearranged
    {
        
        SwapNodes(node->m_previous, node);
        DUMP_LIST();
    }
    
    DUMP_LIST();
    VERIFY_BUCKET_LIST();
}

//--------------------------------------------------------------------------------
// BEGIN DEBUG STUFF
#if defined(BUCKET_DEBUG)
Bool CBucket::VerifyList()
{
    if( m_head->m_previous != NULL )
    {
        BUCKET_LIST_ASSERT(false);
        return false;
    }

    if( m_tail->m_next != NULL )
    {
        BUCKET_LIST_ASSERT(false);
        return false;
    }

    //verify order
    if( m_head != m_tail )
    {
        Bool tailHit = false;
        CBucketNode* maxCountNode = m_head;
        for( CBucketNode* node = m_head->m_next; node!=NULL; node=node->m_next )
        {
            BUCKET_LIST_ASSERT( node->m_previous->m_next == node );

            if( !node->GetFreePool().IsFull() && node->GetFreePool().GetUsedElementCount() > maxCountNode->GetFreePool().GetUsedElementCount() )
            {
                maxCountNode = node;
            }

            if(node == m_tail)
            {
                tailHit = true;
            }

            if( node->m_previous->GetFreePool().GetUsedElementCount() > node->GetFreePool().GetUsedElementCount() )
            {
                BUCKET_LIST_ASSERT(false, "INTERNAL LIST IS UNORDERED");
                return false;
            }
        }

        BUCKET_LIST_ASSERT(tailHit == true);
        BUCKET_LIST_ASSERT( m_maxCountNode->GetFreePool().GetUsedElementCount() == maxCountNode->GetFreePool().GetUsedElementCount() );

        if( m_maxCountNode->GetFreePool().GetUsedElementCount() != maxCountNode->GetFreePool().GetUsedElementCount() )
        {
            return false;
        }

        return tailHit == true;
    }

    return true;
}

//--------------------------------------------------------------------------------
void CBucket::DumpList()
{
    CString debugString;
    debugString += StringUtils::FormatString("=============== BEGIN BUCKET LIST\n");
    for( CBucketNode* node = m_head; node!=NULL; node=node->m_next )
    {
        debugString += StringUtils::FormatString("NODE ptr[%p], count [%d]", node, node->GetFreePool().GetUsedElementCount());
        if(node == m_head)
        {
            debugString += CString(" <- m_head");
        }
        
        if(node == m_maxCountNode)
        {
            debugString += CString(" <- m_maxCountNode");
        }
        
        if(node == m_tail)
        {
            debugString += CString(" <- m_tail");
        }

        debugString += CString("\n");

    }
    debugString += StringUtils::FormatString("=============== END BUCKET LIST");

    BUCKET_TRACE( "%s", debugString.c_str() );
}
#endif// BUCKET_DEBUG
//--------------------------------------------------------------------------------

}//namespace MemoryManager