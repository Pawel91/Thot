#pragma once

#ifndef __FILE_H__
#define __FILE_H__

#include "FileTypes.h"
#include "Kernel\DataStructures\CString.h"

#ifdef _DEBUG

#define ASSERT_ON_TRACE

#ifndef TRACE_FILE
#   ifndef ASSERT_ON_TRACE
#       define TRACE_FILE(_format, ...) THOT_TRACE_LINE(_format, __VA_ARGS__);
#else
#       define TRACE_FILE(_format, ...) do{ THOT_TRACE_LINE(_format, __VA_ARGS__); THOT_ASSERT(0); }while(false)
#endif /*ASSERT_ON_TRACE*/
#   else
#       error TRACE_FILE allready defined; change macro name to resolve conflict;
#   endif /*TRACE_FILE*/
#else
#   define TRACE_FILE(_format, ...)
#endif /*_DEBUG*/



/**
    File interface;
*/
class KERNEL_API IFile
{

//*********************************************
//************CONSTR/DESTR*********************
//*********************************************
protected:
    IFile(){}
public:

virtual     ~IFile()                = 0;


//*********************************************
//************INTERFACE************************
//*********************************************
public:

virtual         Bool                    Open            ( const CString& path, u64 openMode )                               = 0;
virtual         Bool                    Close           ( )                                                                 = 0;
virtual         Bool                    Read            ( void* ptr, u64 nSize, u64 nCount )                                = 0;
virtual         Bool                    Write           ( const void* ptr, u64 nSize, u64 nCount )                          = 0;
virtual         Bool                    ClearContent    ( )                                                                 = 0;

                Bool                    WriteFormat     ( const char* format, ...);
                Bool                    Write           ( const CString& string);

//************GET FUNTIONS
virtual         u64                     GetSize         ( )const                                                            = 0;
virtual         u64                     GetCurrentPos   ( )const                                                            = 0;
virtual         EAccesMode              GetAccesMode    ( )const                                                            = 0;
virtual         void                    GetPath         ( CString& outPath )const                                           = 0;
virtual         void                    GetName         ( CString& outName )const                                           = 0;
virtual         void                    GetExtension    ( CString& outExtension )const                                      = 0;

//***********SET FUNCTIONS
virtual         Bool                    SetCurrentPos   ( u64 nByteOffset )                                                 = 0; 
virtual         Bool                    SetCurrentPos   ( u64 nByteOffset, ESeek from )                                     = 0;
};

#endif __FILE_H__