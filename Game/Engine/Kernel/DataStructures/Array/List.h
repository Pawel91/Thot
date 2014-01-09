#ifndef __LIST_H__
#define __LIST_H__

#include "Kernel\DataTypes.h"
#include "Kernel\DebugSystem\DebugSystem.h"
#include "Kernel/Memory/Memory.h"
#include "Kernel/DataStructures/ArrayTypeBase.h"

template<class T0, class T1>
s32 DefaultCompareFunction(const T0& op1, const T1& op2 )
{
    return op1 - op2;
}


template < class T >
class  CVector:public CArrayTypeBase<T>
{
//********CONSTRUCTORS
public:
    CVector         ( T* pData, u64 nSize );
    CVector         ( );
    CVector         ( u64 capacity );
    ~CVector        ( );

static      u64     ms_invalidIndex;
typedef     s32     (*pfnCompareFunction)( const T& op1, const T& op2 );

//********INTERFACE
inline      T*          GetData             ( );
inline      const T*    GetData             ( )const;
inline      Bool        AppendBuffer        ( const T* buffer, u64 nSize );
inline      void        Empty               ( );
inline      void        Resize              ( u64 newSize );
inline      u64         GetSize             ( )const;
inline      u64         Add                 ( const T& el );
inline      u64         Insert              ( const T& el );
inline      void        InsertAt            ( u64 nIdx, const T& el );
inline      void        DeleteAndMove       ( u64 nIdx );
inline      void        DestroyObjects      ( );
inline      void        StoleData           ( CVector<T>& other );
inline      u64         Find                ( const T& element, pfnCompareFunction compareFunction = DefaultCompareFunction<T,T> ) const;

static      void        CopyVectors         ( CVector<T>& destination, const CVector<T>& source );

inline      T&          operator[]          ( u64 nIdx );
inline      const T&    operator[]          ( u64 nIdx ) const;


//*******HELPER FUNCTIONS
private:
        CVector               ( const CVector& other );
void    IncrementArraySize  ( );

void    InitFromRawData     ( const T* pData, u64 nSize  );

//*******MEMBERS
protected:

u64             m_nSize;
u64             m_nTotalSize;
T*              m_array;

static const float ms_growFactor;
};

template<class T>
u64 CVector<T>::ms_invalidIndex = 0xffffffffffffffff;

#include "List.inl"

#endif /*__LIST_H__*/