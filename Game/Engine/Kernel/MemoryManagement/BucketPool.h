#if !defined(__BUCKET_POOL_H__)
#define __BUCKET_POOL_H__


#include "Kernel/Basics.h"
#include "Kernel/MemoryManagement/BucketsConfig.h"
#include "Kernel/MemoryManagement/BucketPoolBase.h"




namespace MemoryManagement
{

class CBucket;
class KERNEL_API CBucketPool:public CBucketPoolBase
{

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
    typedef CBucketPoolBase super;
     CBucketPool( u32 maxPoolSize );
    ~CBucketPool();

    enum EState
    {
         EState_Invalid
        ,EState_AddingBuckets
        ,EState_Valid
    };

    // part of a page is reserved by bucket pool internal management so we store the real page info into a structure
    struct SPage
    {
        SPage()
            : m_pageAdrees(NULL)
            , m_size(0)
        {
        }

        SPage(void* adress, u32 size)
            : m_pageAdrees(adress)
            , m_size(size)
        {
        }

        SPage( const SPage& other)
            : m_pageAdrees( other.m_pageAdrees)
            , m_size(other.m_size)
        {}
        void*       m_pageAdrees;
        u32         m_size;
    };

    //every allocated page has a header
    struct SPageHeader
    {
        CBucket*        m_bucket;
    };


//*********************************************
//            INTERFACE
//*********************************************
public:

    void*       Alloc( thSize size );
    void        Free( void* memory);
    Bool        IsPointerFromHere(void* ptr);
    Bool        Validate(void* ptr);
    thSize      GetBlockSize(void* ptr);
    Bool        IsValid();

    void        BeginAddBuckets();
    Bool        AddBucket(u32 elementSize);
    void        EndAddBuckets();

    //TODO: this functions should be accessed only by CBucket
    SPage       AllocPage(CBucket* requesterBucket);
    void        FreePage(CBucket* requesterBucket, void* adress);


//*********************************************
//            MEMBERS
//*********************************************
protected:
    u32                         m_bucketsPoolSize;
    EState                      m_state;
    



};


}// namespace MemoryManagement
#endif //__BUCKET_POOL_H__