#ifndef __KERNEL_STRING_UTILS_H__
#define __KERNEL_STRING_UTILS_H__
#include "Kernel\KernelDef.h"
#include "Kernel\DataStructures\Array\Vector.h"
#include "Kernel\DataStructures\CString.h"



namespace StringUtils
{

 struct KERNEL_API SStringCommand
{
    CString     m_attribute;
    CString     m_value;

    SStringCommand(){}
    SStringCommand( const SStringCommand& other );
    const SStringCommand& operator = ( const SStringCommand& other );

private:
    void    InitFromOther( const SStringCommand& other );

};

typedef thVector<CString>          TCommandLineArray;
typedef thVector<SStringCommand>   TCommands;

KERNEL_API  char*       CharToString        ( char ch );
KERNEL_API  void        SplitCommandLine    ( const CString& commandLine, TCommandLineArray& outCmdLine, char lineSeparator = ' ' );
KERNEL_API  void        SplitCommandLine    ( const CString& commandLine, TCommands& outCmds, char lineSeparator = ' ', char assigner = '=' );
KERNEL_API  CString     Quote               (const CString& str);

KERNEL_API const char* FormatString_cstr(  const char* format, ...  );
KERNEL_API CString FormatString (  const char* format, ...  );

}




#endif /*__KERNEL_STRING_UTILS_H__*/