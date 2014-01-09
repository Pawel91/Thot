#include "Kernel_PCH.h"
#include "StackWalker.h"
#include "Kernel/ThotWindows.h"
#include "Kernel/DebugSystem/Tracing.h"
#include "Kernel/Utils/StringUtils.h"
#include "Kernel/FileSystem/Path.h"
#include "Kernel/Profiler/Profiler.h"
#include <dbghelp.h>

namespace StackWalker
{
    Bool InitDebug()
    {
        SymSetOptions(SYMOPT_LOAD_LINES);
        BOOL initRes = SymInitialize(GetCurrentProcess(), NULL, TRUE);
        if (!initRes)
        {
            THOT_TRACE_LINE( "SymInitialize failed with error %d", GetLastError());
        }
        return initRes?true:false;
    }

    //--------------------------------------------------------------------------------
    Bool GetFunctionPointerInfo( u64 addr, SFunctionInfo& outFunctionInfo )
    {
        outFunctionInfo.m_functionPointer = ThNumericCast<void*>( addr );

        char symbolName[MAX_SYM_NAME + 1];
        char buffer[sizeof(IMAGEHLP_SYMBOL64) + MAX_SYM_NAME*sizeof(TCHAR)] = {0};
        IMAGEHLP_LINE64 line;
        DWORD64 dis64 = 0;
        DWORD dis = 0;
        IMAGEHLP_SYMBOL64 *pSym = NULL;
        BOOL res;

        pSym = (IMAGEHLP_SYMBOL64 *) buffer;
        pSym->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
        pSym->MaxNameLength = MAX_PATH;

        res = SymGetSymFromAddr64(GetCurrentProcess(), addr, &dis64, pSym);
        if (!res)
        {
            CString error = StringUtils::FormatString("SymGetSymFromAddr64 fails, error=%ld", GetLastError());
            outFunctionInfo.m_errorString = error.c_str();
            return FALSE;
        }
        else
        {
            strcpy(symbolName, pSym->Name);
        }

        memset(&line, 0, sizeof(line));
        line.SizeOfStruct = sizeof(line);
        res = SymGetLineFromAddr64(GetCurrentProcess(), addr, &dis, &line);

        if (!res)
        {

            CString error = StringUtils::FormatString("UNKNOWN FUNCTION AT ADDRESS[%p]; SymGetLineFromAddr64 fails, error=%ld;", addr, GetLastError() );
            outFunctionInfo.m_errorString = error.c_str();
            return FALSE;
        }
        else
        {
            char szFileName[128];
            Memory::Set(szFileName, 128, 0);
            CPath::GetFileName( line.FileName, szFileName, 128 );
            outFunctionInfo.m_functionName = symbolName;
            outFunctionInfo.m_fileName = szFileName;
            outFunctionInfo.m_line = line.LineNumber;
        }

        return TRUE;
    }

    //--------------------------------------------------------------------------------
    SFunctionInfo::SFunctionInfo( void* functionPointer, const char* functionName, const char* fileName, u64 line )
        : m_functionPointer     ( functionPointer )
        , m_functionName        ( functionName )
        , m_fileName            ( fileName )
        , m_line                ( line)
    {
    }

    //--------------------------------------------------------------------------------
    SFunctionInfo::SFunctionInfo(const SFunctionInfo& other)
        : m_functionPointer     ( other.m_functionPointer )
        , m_line                ( other.m_line )
        , m_functionName        ( other.m_functionName )
        , m_fileName            ( other.m_fileName )
        , m_errorString         ( other.m_errorString)
    {
    }

    //--------------------------------------------------------------------------------
    SFunctionInfo::SFunctionInfo()
        : m_functionPointer (NULL)
        , m_line            (0)
    {
    }

    //--------------------------------------------------------------------------------
    const SFunctionInfo& SFunctionInfo::operator =  (const SFunctionInfo& other)
    {
        m_functionPointer = other.m_functionPointer;
        m_functionName = other.m_functionName;
        m_fileName = other.m_fileName;
        m_line = other.m_line;
        m_errorString = other.m_errorString;

        return *this;
    }

    //--------------------------------------------------------------------------------
    Bool SFunctionInfo::IsValid()
    {
        return m_errorString.GetLenght() == 0;
    }

    //--------------------------------------------------------------------------------
    void SFunctionInfo::GetDebugString( CString& outString )
    {
        if(IsValid())
        {
            outString += StringUtils::FormatString( "FUNCTION [%s] FROM %s(%d)", m_functionName.c_str(), m_fileName.c_str(), m_line );
        }
        else
        {
            outString += StringUtils::FormatString( "CANNOT DECODE FUNCTION PTR[%p], ERROR STRING = [%s]",m_functionPointer, m_errorString.c_str() );
        }
    }

    //--------------------------------------------------------------------------------
    CStackInfo::CStackInfo()
        : m_functionsCount  (0)
    {

    }
    //--------------------------------------------------------------------------------
    CStackInfo::CStackInfo( const CStackInfo& other )
    {
        m_functionInfos.CopyFromOther( other.m_functionInfos );
        m_functionsCount = other.m_functionsCount;
    }

    //--------------------------------------------------------------------------------  
    CStackInfo::~CStackInfo()
    {
    }

    //--------------------------------------------------------------------------------
    void CStackInfo::GetCurrentStackInfo( CStackInfo& outStackInfo, u32 stackFramesCount )
    {
        //DECLARE_PROFILE_SCOPED("CStackInfo::GetCurrentStackInfo");
        static bool init = false;
        if(!init)
        {
            init = InitDebug();
        }

        stackFramesCount += 2;

        PVOID* arrayOfPointers = (PVOID*)alloca( stackFramesCount * sizeof(PVOID) );;
        memset( arrayOfPointers, 0, stackFramesCount * sizeof(PVOID) );
        CaptureStackBackTrace( 0, stackFramesCount, arrayOfPointers, NULL);
        
        for( u32 idx = 0; idx < stackFramesCount; idx++)
        {
            PVOID func = arrayOfPointers[idx];
            if( !func )
            {
                break;
            }

            SFunctionInfo functionInfo;
            GetFunctionPointerInfo((u64)func, functionInfo);

            THOT_ASSERT(outStackInfo.m_functionsCount < outStackInfo.m_functionInfos.GetSize() );
            outStackInfo.m_functionInfos[outStackInfo.m_functionsCount] = functionInfo;
            outStackInfo.m_functionsCount++;
        }
    }

    //--------------------------------------------------------------------------------
    void CStackInfo::DebugTrace()
    {
        THOT_TRACE_LINE("============ BEGIN STACK TRACE:");
        for( u64 i=0; i<m_functionsCount; i++ )
        {
            CString debugInfo;
            m_functionInfos[i].GetDebugString(debugInfo);
            THOT_TRACE_LINE("%s", debugInfo.c_str() );
        }

    THOT_TRACE_LINE("============ END STACK TRACE:");
    }

    //--------------------------------------------------------------------------------
    void CStackInfo::DebugGetStringInfo( CString& out )
    {
        out = "";
        out += "============ BEGIN STACK TRACE:\n";
        for( u64 i=0; i<m_functionsCount; i++ )
        {
            if( m_functionInfos[i].IsValid())
            {
                CString debugInfo;
                m_functionInfos[i].GetDebugString(debugInfo);
                out += StringUtils::FormatString("%s\n", debugInfo.GetBuffer() );
            }
        }

        out += "============ END STACK TRACE:";
    }

}//namespace StackWalker