#include "Kernel_PCH.h"
#include "FileSystem.h"

#include "FileImpl.h"
#include "FileMemory.h"

namespace FileSystem
{

FileHandle CreateFile( EFileType fileType )
{
    switch( fileType  )
    {
    case EFileType::E_FILE_TYPE_NORMAL:
        return THOT_NEW CFile;
        break;
    
    case EFileType::E_FILE_TYPE_MEMORY:
        return THOT_NEW CMemoryFile;
        break;

    default:
        return NULL;
        break;
    }
}


Bool DestroyFile ( IFile* pFile )
{
    //if(pFile == NULL)
    //{
    //    return false;
    //}

    //THOT_DELETE(pFile);


    return true;
}




Bool CopyFileContent ( const CString& sourceFileName, const CString& targtargetFileNameetFile )
{
    FileSystem::FileHandle sourceFile = FileSystem::CreateFile( EFileType::E_FILE_TYPE_MEMORY );
    FileSystem::FileHandle targetFile = FileSystem::CreateFile( EFileType::E_FILE_TYPE_MEMORY );

    if( !sourceFile->Open( sourceFileName, EAccesMode::E_ACCES_MODE_READ ) )
    {
        THOT_TRACE_LINE("failed to open source file:[%s]", sourceFileName.GetBuffer() );
        return false;
    }

    // read source to buffer;
    u64 fileSize = sourceFile->GetSize();
    CString sourceContent;
    sourceContent.Resize( fileSize );

    if( !sourceFile->Read( sourceContent.GetBuffer(), fileSize, 1) )
    {
        THOT_TRACE_LINE("failed to read from file:[%s]", sourceFileName.GetBuffer() );
        return false;
    }

    if( !targetFile->Open( targtargetFileNameetFile, EAccesMode::E_ACCES_MODE_WRITE ) )
    {
        THOT_TRACE_LINE( "failed to open file:[%s]", targtargetFileNameetFile.GetBuffer() );
        return false;
    }
    

    //write to target file;

    if( !targetFile->Write( sourceContent.GetBuffer(), sourceContent.GetLenght(), 1 ) )
    {
        THOT_TRACE_LINE( "failed to write to target file:[%s]", targtargetFileNameetFile );
        return false;
    }

    return true;
}




}//********** namespace FileSystem