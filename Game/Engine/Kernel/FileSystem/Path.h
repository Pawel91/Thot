#pragma once
#ifndef __KERNEL_PATH_H__
#define __KERNEL_PATH_H__

#include "Kernel\DataStructures\CString.h"

#ifdef _DEBUG
#   ifndef TRACE_PATH
#       define TRACE_PATH(_format, ...) THOT_TRACE_LINE(_format, __VA_ARGS__);
#   else
#       error TRACE_FILE allready defined; change macro name to resolve conflict;
#   endif /*TRACE_FILE*/
#else
#   define TRACE_PATH(_format, ...)
#endif /*_DEBUG*/

struct KERNEL_API SPathInfo
{
    CString     m_driver;
    CString     m_path;
    CString     m_fileName;
    CString     m_fileExtension;
};

class KERNEL_API CPath
{

//*********************************************
//************CONSTR/DESTR*********************
//*********************************************
public:



//*********************************************
//************INTERFACE************************
//*********************************************
public:



//*********************************************
//************STATIC FUNCTIONS*****************
//*********************************************
public:


static  Bool        SetDefaultDataPath  ( );
static  Bool        GetDataPath         ( CString& out );
static  Bool        GetDriverLetter     ( const CString& path,  CString& outDrive );
static  Bool        IsDirectoryEmpty    ( const CString& path );
static  Bool        IsAbsolute          ( const CString& path );
static  Bool        IsRelative          ( const CString& path );
static  Bool        FileExists          ( const CString& path );
static  Bool        IsDirectory         ( const CString& path ); 
static  void        GetPathSplitter     ( CString& out );
static  Bool        SetCurrPath         ( const CString& path );
static  Bool        GetCurrPath         ( CString& outPath );
static  Bool        GetAbsolutePath     ( const CString& relPath, CString& outAbsolutePath );
static  Bool        SplitAbsolutePath   ( CString& absolutePath, SPathInfo& out );
static  Bool        CreateDir           ( CString& dirName );
static  Bool        GetFileExtension    ( const CString& filePath, CString& outExt );
static  Bool        GetFileExtension    ( const char* szFilePath, char* outExtension, u32 outBufferSize );
static  Bool        GetFileName         ( const CString& filePath, CString& outFileName );
static  Bool        GetFileName         ( const char* szFilePath, char* outFileName, u32 outBufferSize);
static  Bool        DeleteFile          (const CString& fileName );
static  Bool        DirectoryExists     ( const CString& dir );

//*********************************************
//************MEMBERS**************************
//*********************************************
protected:

};


#endif /*__KERNEL_PATH_H__*/