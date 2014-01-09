#include "Kernel/DataTypes.h"
#include "Kernel/KernelDef.h"
#include "Kernel/DataStructures/Array/Array.h"
#include "Kernel/DataStructures/CString.h"
#include "Kernel/DataStructures/FixedString.h"

namespace StackWalker
{
    //--------------------------------------------------------------------------------
    struct KERNEL_API SFunctionInfo
    {
        SFunctionInfo( );
        SFunctionInfo( void* functionPointer, const char* functionName, const char* fileName, u64 line );
        SFunctionInfo( const SFunctionInfo& other );

        const SFunctionInfo& operator =  (const SFunctionInfo& other);

        Bool    IsValid();
        void    GetDebugString( CString& outString );


        void*               m_functionPointer;
        u64                 m_line;
        CFixedString<64>    m_functionName;
        CFixedString<64>    m_fileName;
        CFixedString<64>    m_errorString;
    };

    THOT_DECLARE_TEMPLATE_API( KERNEL_TEMPLATE_API, CStaticArray<SFunctionInfo, 62> );

    //--------------------------------------------------------------------------------
    class KERNEL_API CStackInfo
    {
    public:
        friend KERNEL_API Bool GetFunctionPointerInfo( u64 addr, CString& outInfo );
        CStackInfo();
        ~CStackInfo();
        CStackInfo( const CStackInfo& other );

        void DebugTrace();
        void DebugGetStringInfo( CString& out );

    public:
        static void GetCurrentStackInfo( CStackInfo& outStackInfo, u32 stackFramesCount = ms_maxStackFrames );
        static const u32        ms_maxStackFrames = 62;
    private:
        CStaticArray<SFunctionInfo, ms_maxStackFrames>  m_functionInfos;
        u64                                             m_functionsCount;
    };

    //--------------------------------------------------------------------------------
    KERNEL_API Bool InitDebug();
    KERNEL_API Bool GetFunctionPointerInfo( u64 addr, CString& outInfo );

}// namespace StackWalker


#define STACK_WALKER_INIT() StackWalker::InitDebug()
#define STACK_WALKER_TRACE_FUNCTION(f) StackWalker::TracePointerInfo((DWORD64)(f))
