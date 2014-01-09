#include "Kernel_PCH.h"
#include "File.h"
#include "Kernel/Utils/StringUtils.h"

//--------------------------------------------------------------------------------
IFile::~IFile(){}

//--------------------------------------------------------------------------------
Bool IFile::Write( const CString& string)
{
    return Write( string.c_str(), string.GetLenght(), 1 );
}

//--------------------------------------------------------------------------------
Bool IFile::WriteFormat( const char* format, ...)
{
    THOT_ASSERT( false, "NOT IMPLEMENTED");
    return false;
    //Write( StringUtils::FormatString( format ) );
}