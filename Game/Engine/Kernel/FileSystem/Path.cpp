#include "Kernel_PCH.h"
#include "Path.h"

#include "Kernel/ThotWindows.h"
#include "Shlwapi.h"
#include "Commdlg.h"

#undef DeleteFile

void CPath::GetPathSplitter ( CString& out )
{
#if defined THOT_PLATFORM_WINDOWS
    out = "\\";
#else
#   error UNDEFINED PLATFORM
#endif
}

Bool CPath::SetDefaultDataPath  ( )
{
    CString dataPath;
    //if( !CPath::GetDataPath(dataPath) )
    //{
    //    return false;
    //}

    CPath::SetCurrPath(/*dataPath +*/ "..\\");
    CString currPath;
    CPath::GetCurrPath(currPath);

    return true;
}

Bool CPath::GetDataPath( CString& out )
{
    char* szDataPath = getenv("GAME_DATA_DIR");
    out = szDataPath;
    if( szDataPath == NULL )
    {
        return false;
    }

    return true;
}


Bool CPath::GetCurrPath ( CString& outPath )
{
#if defined THOT_PLATFORM_WINDOWS    
    
    const u32 nBufferSize = MAX_PATH;
    char stringPath[nBufferSize];
    
    DWORD dwRet;

    dwRet = GetCurrentDirectoryA( nBufferSize, stringPath );

    if( dwRet == 0 )
    {
       TRACE_PATH("GetCurrentDirectory failed (%d)\n", GetLastError());
       return false;
    }

    if(dwRet > nBufferSize)
    {
        TRACE_PATH("Buffer too small; need %d characters\n", dwRet);
        return false;
    }


    outPath = stringPath;
    return true;

#else
#   error UNDEFINED PLATFORM
#endif 
}

Bool CPath::GetAbsolutePath ( const CString& relPath, CString& outAbsolutePath )
{
#if defined THOT_PLATFORM_WINDOWS

    const u32 nBufferSize = MAX_PATH;
    char absolutePath[nBufferSize];

    //TODO: reasearch last param of this function;
    DWORD retval = 0;
    retval = GetFullPathNameA(  relPath
                                ,nBufferSize
                                ,absolutePath
                                ,NULL);
    
    if (retval == 0) 
    {
        // Handle an error condition.
        TRACE_PATH ("CPath: GetFullPathName failed (%d)\n", GetLastError());
        return false;
    }
    outAbsolutePath = absolutePath;

    return true;

#else
#   error UNDEFINED PLATFORM
#endif
}

Bool CPath::FileExists( const CString& path )
{
#if defined THOT_PLATFORM_WINDOWS
    
    DWORD ftyp = GetFileAttributesA( path );
    if (ftyp == INVALID_FILE_ATTRIBUTES)
    {
        return false;  //something is wrong with your path!
    }

    return true;    // this 

#else
#   error UNDEFINED PLATFORM
#endif /*defined _WIN32*/
}

Bool CPath::GetDriverLetter( const CString& path, CString& out )
{
#ifdef THOT_PLATFORM_WINDOWS

    int rez =  PathGetDriveNumberA(path);
    if( rez ==-1)
    {
        TRACE_PATH("CPath: Failed to get drive number");
        return false;
    }

    char ch[2] =  "\0";
    ch[0] =   'A' + rez;
    out = ch;
    out += ":";

    return true;
#else
#   error UNDEFINED PLATFORM
#endif
}



Bool CPath::IsDirectory ( const CString& path )
{
#if defined THOT_PLATFORM_WINDOWS

    return PathIsDirectoryA( path )?true:false;

#else
#   error UNDEFINED PLATFORM
#endif
}

Bool CPath::IsAbsolute( const CString& path )
{
    return !IsRelative(path);
}

Bool CPath::IsDirectoryEmpty( const CString& path )
{
 #if defined THOT_PLATFORM_WINDOWS

    return PathIsDirectoryEmptyA( path )?true:false;

#else
#   error UNDEFINED PLATFORM
#endif

}

Bool CPath::SetCurrPath( const CString& path )
{
#if defined THOT_PLATFORM_WINDOWS
    if ( SetCurrentDirectoryA(path) == 0 )
    {
        TRACE_PATH("CPath: Cannot set current directory");
        return false;
    }

    return true;
#else
#   error UNDEFINED PLATFORM
#endif /*_Win32*/
}

Bool CPath::IsRelative( const CString& path )
{
 #if defined THOT_PLATFORM_WINDOWS

    return PathIsRelativeA( path )?true:false;

#else
#   error UNDEFINED PLATFORM
#endif
}


Bool    CPath::SplitAbsolutePath   ( CString& absolutePath, SPathInfo& out )
{
    //fiind position of '.' wich separate extension and then fiind withc separate the driver;
    CString path;
    if( CPath::IsRelative(absolutePath) )
    {
        if ( !CPath::GetAbsolutePath( absolutePath, path ) )
        {
            return false;
        }
    }
    else
    {
        path = absolutePath;
    }


    //fiind ':'
    u64 nColonPos=0;
    Bool bFindColon = false;

    if( (nColonPos = path.Find(':') ) == CString::ms_invalidIndex )
    {
        return false;
    }

    if( !path.SubStr(0, nColonPos+1, out.m_driver ) )
    {
        return false;
    }

    
    char* ext = PathFindExtensionA( path );
    out.m_fileExtension = ext;

    out.m_fileName = "";
    for( char* ch = ext-1; *ch != '\\'; ch-- )
    {
        out.m_fileName.Append(*ch);
    }



    return true;
}

//--------------------------------------------------------------------------------
Bool    CPath::CreateDir     ( CString& dirName )
{
    THOT_ASSERT(0);
    return true;
}

//--------------------------------------------------------------------------------
Bool CPath::GetFileExtension    ( const CString& filePath, CString& outExt )
{

    char* ext = PathFindExtensionA( filePath.GetBuffer() );
    if( !ext )
    {
        return false;
    }

    outExt = ext;

    return true;
}

//--------------------------------------------------------------------------------
Bool CPath::GetFileExtension( const char* szFilePath, char* outExtension, u32 outBufferSize )
{
    char* ext = PathFindExtensionA( szFilePath );
    if( strlen(ext) < outBufferSize )
    {
        strcpy( outExtension, ext );
        return true;
    }

    return false;
}

Bool CPath::DeleteFile( const CString& fileName )
{
    if( DeleteFileA( fileName.c_str() ) == 0 )
    {
        return false;
    }

    return true;
}

//---------------------------------------------------------------------------------------------

Bool CPath::GetFileName( const CString& filePath, CString& outFileName )
{
    outFileName = "";
    const u32 maxSize = 256;
    char tempBuffer[maxSize];
    memset( tempBuffer, 0, maxSize );

    if( GetFileTitleA( filePath.GetBuffer(), tempBuffer, maxSize ) != 0 )
    {
        return false;
    }

    CString extension;
    if( !CPath::GetFileExtension( filePath, extension) )
    {
        return false;
    }

    outFileName = tempBuffer + extension;
    return true;
}

//--------------------------------------------------------------------------------
Bool CPath::GetFileName( const char* szFilePath, char* outFileName, u32 outBufferSize)
{
    if( GetFileTitleA( szFilePath, outFileName, outBufferSize ) != 0 )
    {
        return false;
    }

    thSize currentSize = strlen(outFileName);
    char* extensionBegin = outFileName + currentSize;

    if( !GetFileExtension( szFilePath, extensionBegin, outBufferSize - ThNumericCast<u32>(currentSize) ) )
    {
        return false;
    }

    return true;
}

//--------------------------------------------------------------------------------
Bool CPath::DirectoryExists( const CString& dir )
{
  DWORD dwAttrib = GetFileAttributesA(dir.GetBuffer());

  return (dwAttrib != INVALID_FILE_ATTRIBUTES && 
         (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}