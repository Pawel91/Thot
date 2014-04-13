#ifndef __CSTRING_H__
#define __CSTRING_H__

#include "Kernel/DebugSystem/DebugSystem.h"
#include "Kernel/KernelUtils.h"
#include "Kernel/Externals.h"
#include "Kernel/MemoryManagement/Heap.h"
#include "Kernel/MemoryManagement/Allocator.h"
#include <string.h>
#include <string>

class KERNEL_API CString
{

//*****CONSTRUCTORS
public:

inline      CString     ( char* pBuff, Bool ownThisBuffer );
inline      CString     ( char* pBuffer, thSize bufferSize, Bool ownThisBuffer);
inline      CString     ( const char* pBuff );
inline      CString     ( );
inline      CString     ( const CString& other );

#ifdef THOT_ENABLE_MOVE_CONSTRUCTOR
inline      CString     ( CString&& otherTemp );
#endif /*THOT_ENABLE_MOVE_CONSTRUCTOR*/

inline     ~CString     ( );



//***INTERFACE
inline      u64             GetLenght           ( )const { return m_nSize; }
inline      void            OwnBuffer           ( char* pBuffer );
inline      Bool            IsEmpty             ( )const{ return m_nSize == 0; }
inline      void            ToUpper             ( );
inline      void            ToLower             ( );
inline      void            Resize              ( u64 nNewNeededSize );
inline      char*           GetBuffer           ( ) { return m_pString; }
inline      const char*     GetBuffer           ( )const {return m_pString;}
inline      const char*     c_str               ( )const { return GetBuffer();}
inline      void            Empty               ( );
inline      int             ToInt               ( );
inline      Bool            SubStr              ( u64 from, u64 lenght, CString& out );
inline      u64             Find                ( char ch );
inline      void            Append              ( const char ch );
inline      void            SetInternalBufferOwnership  ( Bool own = true );


//***STATIC FUNCTIONS
static      void            s_Concat            ( const CString& a, const CString& b, CString& out );
static      s32             Compare             ( const CString& a, const CString& b);


//*****OPERATOR OVERRIDES
inline      char                operator []         ( u64 nIdx )const;
inline      char&               operator []         ( u64 nIdx );
inline      Bool                operator ==         ( const CString& other)const;
inline      Bool                operator ==         ( const char* pBuff )const;
inline      const CString&      operator =          ( CString&& otherTemp );
inline      const CString&      operator =          ( const CString& other );
inline      const CString&      operator =          ( const char* pBuff );
inline      CString             operator +          ( const CString& other )const;
inline      const CString&      operator +=         ( const CString& other );
inline      const CString&      operator +=         ( const char* pBuff );
inline      Bool                 operator <          ( const CString& other );
inline      Bool                 operator <=         ( const CString& other );

inline      Bool                 operator >          ( const CString& other );
inline      Bool                 operator >=         ( const CString& other );


inline      operator const char*                    ( )const;
inline      operator char*                          ( );
inline      operator std::string                    ( );
inline      operator const std::string              ( )const;

//****HELPERS
protected:

            void            InitFromOther           ( const CString& other );
inline      void            InitFromOtherTemp       ( CString& other );
inline      void            InitFromBuff            ( const char* pBuff );
inline      void            Destroy                 ( );

//*****MEMBERS
private:
        char*           m_pString;
        u64             m_nSize;
        u64             m_nMaxSize;
        Bool            m_ownBuffer;
        CSmartAllocator m_allocator;

static  const   float       ms_growFactor;
static  CHeap&              GetStringHeap();

public:
static  const   u64         ms_invalidIndex;
};


//template<class _Ty>
struct StdStringLess
//: public std::binary_function<_Ty, _Ty, bool>
{	// functor for operator<
bool operator()(const CString& _Left, const CString& _Right) const
	{	// apply operator< to operands
	    return CString::Compare(_Left, _Right)<0?true:false;
	}
};

//******* GLOBAL CONSTANTS
extern KERNEL_API const CString g_dataPath;

#include "CString.inl"

#endif /*__STRING_H__*/