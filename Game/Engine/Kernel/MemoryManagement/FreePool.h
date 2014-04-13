#if !defined(__KERNEL_FREE_POOL_H__)
#define __KERNEL_FREE_POOL_H__

#include "Kernel/Basics.h"

struct SListNode;

/**
    Memory pool that can alloc fixed size elements
    And has a fixed size of total elements; cannot grow or shrink
*/
class KERNEL_API CFreePool
{
//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
     CFreePool( u32 elementSize, u32 poolSize, void* buffer = NULL );
    ~CFreePool();

//*********************************************
//            INTERFACE
//*********************************************
public:
    template<typename T>
    T* AllocT()
    {
        THOT_COMPILE_ASSERT(sizeof(T)>=sizeof(void*));
        THOT_ASSERT(sizeof(T)==m_elementSize);
        return (T*)Alloc();
    }

    void*                   Alloc(); // alloc one block of size elementSize
    void                    Free( void* element);
    Bool                    IsPointerFromHere(void* data)const;
    const void*             GetData()const;
    void*                   GetData();
    Bool                    IsFull()const;
    Bool                    IsEmpty()const;
    void                    Release();//release all memory
    u32                     GetElementSize();
    u32                     GetPoolSize();//total size in elements
    u32                     GetUsedElementCount();
    u32                     GetMemoryOverhead()const;
    Bool                    Validate(void* ptr);


//*********************************************
//            HELPER FUNCTIONS
//*********************************************
private:
    void            PushFree(void* element);
    u8*             PopFree();



//*********************************************
//            MEMBERS
//*********************************************
private:
    u8*             m_rawData;
    u8*             m_freeHead;// head pointer to link list of free elements
    u32             m_elementSize;
    u32             m_poolSize;
    u32             m_usedElementCount;
    Bool            m_ownRawData;
};

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
template<class T>
class CFreePoolTempl
{
public:
    CFreePoolTempl( u32 poolSize )
        : m_freePool(sizeof(T), poolSize)

        T*          Alloc()             { return (T*)m_freePool.Alloc();}
        void        Free(T* element)    { m_freePool.Free(element);}
        void        Release()           { m_freePool.Release();}
        Bool        IsEmpty()           { return m_freePool.IsEmpty();}
        Bool        IsFull()            { return m_freePool.IsFull();}
        Bool        IsPointerFromHere() { return m_freePool.IsPointerFromHere();}


        const CFreePool& GetInternalFreePool()const{ return m_freePool; }

private:
    CFreePool       m_freePool;
};



#endif //__KERNEL_FREE_POOL_H__