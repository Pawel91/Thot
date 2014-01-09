#include "Kernel_PCH.h"
#include "FileImpl.h"

#include "Path.h"

#include <stdio.h>
#include <sys/types.h> 
#include <sys/stat.h>




#define DECLARE_CONSTRUCTOR_LIST  \
:m_pFile        ( NULL )\
,m_nSize        ( 0 )\
,m_nCurrPos     ( 0 )

//*********************************
//      ADD HERE ALL CONSTRUCTORS
//*********************************

CFile::CFile()
DECLARE_CONSTRUCTOR_LIST
{

}

#undef DECLARE_CONSTRUCTOR_LIST

CFile::~CFile()
{
    Close();
}



Bool CFile::ClearContent( )
{
    if( !m_pFile )
    {
        TRACE_FILE("ERROR!  CFile: cannot clear file content; no std file was created");
        return false;
    }

    if ( fclose(m_pFile) !=0 )
    {
        TRACE_FILE("ERROR!  CFile: cannot close std file");
        return false;
    }

    CString filePath;
    GetPath(filePath);

#if defined _WIN32 && defined _MSC_VER
    if( fopen_s( &m_pFile, filePath, "wb")!=0 )
#else
#   error UNDEFINED PLATFORM
#endif /*defined _WIN32 && defined _MSC_VER*/ 
    {
        TRACE_FILE("ERROR!  CFile: cannot open std file with 'wb' to force file clearing");
        return false;
    }

    if ( !Open( filePath, (u64)GetAccesMode() ) )
    {
        TRACE_FILE("ERROR!  CFile: cannot reopen file after clearning it");
        return false;
    }


    return true;
}

u64 CFile::ComputeByteOffsetFromBigining   ( u64 offset, ESeek from )
{
    if( from == ESeek::E_SEEK_BEGIN )
        return offset;

    u64 nOffsetFromBeginning = 0;
    if( from == ESeek::E_SEEK_END )
    {
        nOffsetFromBeginning = m_nSize - offset;
    }
    else if( from == ESeek::E_SEEK_CURR )
    {
        nOffsetFromBeginning = m_nCurrPos + offset;
    }

    return nOffsetFromBeginning;
}

u64 CFile::StdGetFileSize ( const CString& path )
{
    if( !m_pFile )
    {
        return 0;
    }

#define GET_WHIT_STAT

#if !defined GET_WHIT_STAT
    u64 nFileSize = 0;

    u64 nCurrPos = ftell( m_pFile );
    
    //put at the end
    fseek( m_pFile, 0, SEEK_END );
    nFileSize = ftell( m_pFile );

    // put at position before query
    fseek(m_pFile, (long)nCurrPos, SEEK_SET );

    return nFileSize;
#else
    struct _stat buf;
    int result;
    // Get data associated with "crt_stat.c": 
    result = _stat( path.GetBuffer(), &buf );
    THOT_ASSERT( result==0 );

    return buf.st_size;

#endif 
}

Bool CFile::StdGetOpenMode( u64 openMode, CString& outOpenMode )
{
    switch( openMode )
    {
    case EAccesMode::E_ACCES_MODE_APPEND:
    {
        outOpenMode = "ab";
        break;
    }

    case EAccesMode::E_ACCES_MODE_READ:
    {
        outOpenMode = "rb";
        break;
    }

    case EAccesMode::E_ACCES_MODE_WRITE:
    {
        outOpenMode = "wb";
        break;
    }

    case EAccesMode::E_ACCES_MODE_WRITE | EAccesMode::E_ACCES_MODE_READ :
    {
        outOpenMode = "wb+";
        break;
    }

    case EAccesMode::E_ACCES_MODE_READ | EAccesMode::E_ACCES_MODE_TEXT:
    {
        outOpenMode = "r";
        break;
    }


    case EAccesMode::E_ACCES_MODE_WRITE | EAccesMode::E_ACCES_MODE_TEXT:
    {
        outOpenMode = "w";
        break;
    }


    default:
        TRACE_FILE("ERROR! Could not fiind open mode");
        return false;
    break;


    }//switch;
        
    return true;
}

void CFile::InitAfterOpen ( const CString& path, u64 openMode )
{
    m_nOpenMode = openMode;
    m_nSize = StdGetFileSize( path );
    CPath::GetAbsolutePath( path, m_path);
}

Bool CFile::Open( const CString& path, u64 openMode ) 
{
    CString stdOpenMode;
    
    if( !StdGetOpenMode( openMode, stdOpenMode  ) )
    {
        TRACE_FILE( "Invalid File open mode" );
        return false;
    }


// open file; return false if unsuccesful
#if defined(THOT_PLATFORM_WINDOWS)
    if ( fopen_s( &m_pFile, path, stdOpenMode ) !=0 )
    {
        TRACE_FILE("Could not open file [%s]", path.GetBuffer() );
        return false;
    }
#else
#   error UNSUPORTED PLATFORM
#endif
    
    InitAfterOpen(path, openMode );
    return true;
}

Bool CFile::Close( )
{
    if( !m_pFile )
    {
        return false;
    }

    fclose( m_pFile );
    m_pFile = NULL;

    return true;
}

/**
    Read 'nCount' elements of size equal to 'nSize', summing a total of nCount * nSize bytes;
    Return number of elements readed;
*/
Bool CFile::Read ( void* ptr, u64 nSize, u64 nCount )
{
    //verify file acces
    if( !Flags_HasProp( (dword)m_nOpenMode, EAccesMode::E_ACCES_MODE_READ ) )
    {
        TRACE_FILE("CFile:  Cannot read from file due to acces options");
        return false;
    }

    if( !m_pFile )
    {
        TRACE_FILE("ERROR!  CFile: std file was not created");
        return false;
    }

    THOT_ASSERT(ptr!=NULL);

    size_t bytesWritten = 0;
    //bytesWritten  = fread( ptr, nSize, nCount, m_pFile );

    bytesWritten  = fread( ptr, 1, ThNumericCast<size_t>(nCount * nSize), m_pFile );
    if( bytesWritten != nCount * nSize )    
    {
        THOT_TRACE("Source code = %s\n", ptr);
        TRACE_FILE("ERROR! fread: Could not read from stream;");
        return false;
    }   
 
    m_nCurrPos += nCount * nSize;

    return true;
}

Bool CFile::Write( const void* ptr, u64 nSize, u64 nCount )
{
    //verify file acces
    if( !Flags_HasProp( (dword)m_nOpenMode, EAccesMode::E_ACCES_MODE_WRITE ) )
    {
        TRACE_FILE("CFile:  Cannot write to file due to acces options");
        return false;
    }

    if( !m_pFile )
    {
        return false;
    }

   if( fwrite( ptr, ThNumericCast<size_t>(nSize), ThNumericCast<size_t>(nCount), m_pFile) != ThNumericCast<size_t>(nCount) )
   {
        TRACE_FILE("ERROR! fwrite: Could not write to stream;");
        return false;
   }

    u64 bytesWrited = nSize * nCount;
    
    m_nSize += bytesWrited;
    m_nCurrPos += bytesWrited;

    return true;
}

u64  CFile::GetSize( )const
{
    return m_nSize;
}

u64  CFile::GetCurrentPos( )const
{
    return m_nCurrPos;
}

EAccesMode CFile::GetAccesMode( )const
{
    return (EAccesMode)m_nOpenMode;
}

void CFile::GetPath ( CString& outPath )const
{
    
}

void CFile::GetName ( CString& outName )const
{

}

void CFile::GetExtension ( CString& outExtension )const
{
}

Bool CFile::SetCurrentPos ( u64 nByteOffset )
{
    if( !m_pFile )
    {
        return false;
    }

    if( nByteOffset > m_nSize )
    {
        return false;
    }


    if ( fseek( m_pFile, (long)nByteOffset, SEEK_SET ) !=0 )
    {
        return false;    
    }

    m_nCurrPos = nByteOffset;
    
    return true;
}

Bool CFile::SetCurrentPos ( u64 nByteOffset, ESeek from )
{
    u64 nOffsetFromBeg = ComputeByteOffsetFromBigining(nByteOffset, from);
    return  SetCurrentPos(nOffsetFromBeg);
}




