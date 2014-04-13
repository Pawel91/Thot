#include "Kernel_PCH.h"
#include "FileMemory.h"

#ifdef DECLARE_CONSTRUCTOR_LIST
#undef DECLARE_CONSTRUCTOR_LIST
#endif 

#define DECLARE_CONSTRUCTOR_LIST \
:m_pFile        ( NULL )    \
,m_nCurrPos     ( 0 )


CMemoryFile::CMemoryFile( )
DECLARE_CONSTRUCTOR_LIST 
{
}

#undef DECLARE_CONSTRUCTOR_LIST

CMemoryFile::~CMemoryFile()
{
    Close();
}

Bool  CMemoryFile::Open   ( const CString& path, u64 openMode )
{
    m_pFile = FileSystem::CreateFile( EFileType::E_FILE_TYPE_NORMAL );
    
    if( !m_pFile )
    {
        TRACE_FILE("ERROR! Could not create file when opening CMemoryFile");
        return false;
    }

    if( !m_pFile->Open( path, openMode) )
    {
        TRACE_FILE("ERROR! Could not open raw File when opening CMemoryFile");
        return false;
    }
    
    // read current file content if we have acces to it;
    if( Flags_HasProp( (dword)openMode, EAccesMode::E_ACCES_MODE_READ ) )
    {
        //read all file data to memory;
        u64 nFileSize = m_pFile->GetSize();
        if ( !m_pFile->SetCurrentPos(0) )
        {
            TRACE_FILE("ERROR! Could not set file position when opening CMemoryFile");
            return false;
        }

        m_fileContent.Resize( nFileSize + 1 );
        Memory::Set(m_fileContent.GetData(), m_fileContent.Size(), 0);
        if ( !m_pFile->Read( m_fileContent.GetData(), nFileSize, 1 ) )
        {
            TRACE_FILE("ERROR! Could not read all file data when opening CMemoryFile");
            return false;
        }
    }

    return true;
}

Bool  CMemoryFile::Close  ( )
{
    if( !m_pFile )
    {
        return false;
    }
    
    Flush();

    return m_pFile->Close();
}

Bool  CMemoryFile::Read   ( void* ptr, u64 nSize, u64 nCount )
{
    THOT_ASSERT(ptr!=NULL);
    u64 nSizeToRead = nSize * nCount;

    if( nSizeToRead + m_nCurrPos > m_fileContent.Size() )
    {
        TRACE_FILE("ERROR! CMemoryFile overflow when reading data");
        return false;
    }

    memcpy( ptr, m_fileContent.GetData() + m_nCurrPos, ThNumericCast<size_t>(nSizeToRead) );

    m_nCurrPos += nSizeToRead;

    return true;
}

Bool  CMemoryFile::Write  ( const void* ptr, u64 nSize, u64 nCount ) 
{
 
    if(!ptr)
    {
        TRACE_FILE("ERROR! CMemoryFile: cannot write NULL data to file");
        return false;
    }
    
    u64 nSizeToWrite = nSize * nCount;
    m_fileContent.PushBackArray( (byte*)ptr, nSizeToWrite );

    return true;
}

Bool CMemoryFile::ClearContent( )
{

    THOT_ASSERT(0);

    return true;
}

u64  CMemoryFile::GetSize( )const
{
    return m_fileContent.Size();
}

u64  CMemoryFile::GetCurrentPos ( )const
{
    return m_nCurrPos;
}

EAccesMode CMemoryFile::GetAccesMode( )const
{
    return m_pFile->GetAccesMode();
}

void CMemoryFile::GetPath( CString& outPath )const
{
    m_pFile->GetPath(outPath);
}

void CMemoryFile::GetName( CString& outName )const
{
    m_pFile->GetName(outName);
}

void CMemoryFile::GetExtension( CString& outExtension )const
{
    m_pFile->GetExtension(outExtension);
}

Bool CMemoryFile::SetCurrentPos   ( u64 nByteOffset )
{

    if( nByteOffset > m_fileContent.Size() )
    {
        TRACE_FILE("ERROR!  CMemoryFile: Setting position outside file range");
        return false;
    }

    m_nCurrPos = nByteOffset;
    
    return true;
} 

Bool CMemoryFile::SetCurrentPos   ( u64 nByteOffset, ESeek from )
{
    THOT_ASSERT(0);
    return false;
}


Bool CMemoryFile::Flush( )
{
    //write content of file to file;
    if( !m_pFile )
    {
        return false;
    }

    if( Flags_HasProp( (dword)m_pFile->GetAccesMode(), EAccesMode::E_ACCES_MODE_WRITE ) )
    {
        if( !m_pFile->Write( m_fileContent.GetData(), m_fileContent.Size(), 1 ) )
        {
            return false;
        }
    }

    return true;
}

