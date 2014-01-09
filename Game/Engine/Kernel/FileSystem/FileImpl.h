#pragma once
#ifndef __KERNEL_FILE_IMPLEMENTED_H__
#define __KERNEL_FILE_IMPLEMENTED_H__


#include "File.h"
#include "FileSystem.h"
#include "FileTypes.h"



struct _iobuf;
/**
    Wrapper class for standard file;
*/
class CFile: public IFile
{
//*********************************************
//************CONSTR/DESTR*********************
//*********************************************
friend FileSystem::FileHandle FileSystem::CreateFile( EFileType fileType );
protected:
    CFile();
public:
                
    virtual     ~CFile();


//*********************************************
//************INTERFACE************************
//*********************************************
public:

    virtual         Bool                    Open            ( const CString& path, u64 openMode )                   override;
    virtual         Bool                    Close           ( )                                                     override;
    virtual         Bool                    Read            ( void* ptr, u64 nSize, u64 nCount )                    override;
    virtual         Bool                    Write           ( const void* ptr, u64 nSize, u64 nCount )              override;
    virtual         Bool                    ClearContent    ( )                                                     override;

    //************GET FUNCTIONS
    virtual         u64                     GetSize         ( )const                                                override;
    virtual         u64                     GetCurrentPos   ( )const                                                override;
    virtual         EAccesMode              GetAccesMode     ( )const                                                override;
    virtual         void                    GetPath         ( CString& outPath )const                               override;
    virtual         void                    GetName         ( CString& outName )const                               override;
    virtual         void                    GetExtension    ( CString& outExtension )const                          override;

    //***********SET FUNCTIONS
    virtual         Bool                    SetCurrentPos   ( u64 nByteOffset )                                     override; 
    virtual         Bool                    SetCurrentPos   ( u64 nByteOffset, ESeek from )                         override;



//*********************************************
//************HELPERS**************************
//*********************************************
private:
        Bool        StdGetOpenMode                  ( u64 openMode, CString& outOpenMode );
        u64         StdGetFileSize                  ( const CString& path );
        void        InitAfterOpen                   ( const CString& path, u64 openMode );
        u64         ComputeByteOffsetFromBigining   ( u64 offset, ESeek from );
//*********************************************
//************MEMBERS**************************
//*********************************************
protected:
    _iobuf*         m_pFile;
    u64             m_nOpenMode;
    u64             m_nSize;
    u64             m_nCurrPos;
    CString         m_path;


};


#endif /*__KERNEL_FILE_IMPLEMENTED_H__*/