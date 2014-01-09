#pragma once
#ifndef __KERNEL_FILE_MEMORY_H__
#define __KERNEL_FILE_MEMORY_H__

#include "File.h"
#include "Kernel\DataStructures\Array\Vector.h"
#include "FileSystem.h"



template class thVector<byte>;
class CFile;
class CMemoryFile: public IFile
{

//*********************************************
//************CONSTR/DESTR*********************
//*********************************************

//friend with factory function;
friend FileSystem::FileHandle FileSystem::CreateFile( EFileType fileType );;
protected:
    CMemoryFile( );

public:
virtual     ~CMemoryFile();

//*********************************************
//************INTERFACE************************
//*********************************************
public:
typedef thVector<byte> TFileContent;


virtual         Bool                    Open            ( const CString& path, u64 openMode )                       override;
virtual         Bool                    Close           ( )                                                         override;
virtual         Bool                    Read            ( void* ptr, u64 nSize, u64 nCount )                        override;
virtual         Bool                    Write           ( const void* ptr, u64 nSize, u64 nCount )                  override;
virtual         Bool                    ClearContent    ( )                                                         override;

    //************GET FUNTIONS
virtual         u64                     GetSize         ( )const                                                    override;
virtual         u64                     GetCurrentPos   ( )const                                                    override;
virtual         EAccesMode              GetAccesMode    ( )const                                                    override;
virtual         void                    GetPath         ( CString& outPath )const                                   override;
virtual         void                    GetName         ( CString& outName )const                                   override;
virtual         void                    GetExtension    ( CString& outExtension )const                              override;

    //***********SET FUNCTIONS
virtual         Bool                    SetCurrentPos   ( u64 nByteOffset )                                         override; 
virtual         Bool                    SetCurrentPos   ( u64 nByteOffset, ESeek from )                             override;


//*********************************************
//************HELPERS**************************
//*********************************************
protected:
            Bool    InitFromFile    ( const CFile& file );
            Bool    Flush           ( );

//*********************************************
//************MEMBERS**************************
//*********************************************
protected:
        TFileContent            m_fileContent;
        u64                     m_nCurrPos;
        FileSystem::FileHandle  m_pFile;

};



#endif /*__KERNEL_FILE_MEMORY_H__*/