#ifndef __KERNEL_FILE_SYSTEM__
#define __KERNEL_FILE_SYSTEM__

#include "File.h"
#include "FileTypes.h"
#include "Kernel\Utils\SmartPointer.h"


#ifdef CreateFile
#   undef CreateFile
#   pragma message( "CreateFile is defined; posible conflict with windows.h")
#endif CreateFile


namespace FileSystem
{

template class CSmartPtr<IFile>;
typedef CSmartPtr<IFile> FileHandle;

KERNEL_API      FileHandle      CreateFile      ( EFileType fileType );
KERNEL_API      FileHandle      CreateTempFile  ( );

KERNEL_API      Bool            CopyFileContent ( const CString& sourceFileName, const CString& targetFileName );
KERNEL_API      Bool            DestroyFile     ( IFile* pFile );
KERNEL_API      Bool            FileExists      ( const char* path );

}



#endif /*__KERNEL_FILE_SYSTEM__*/