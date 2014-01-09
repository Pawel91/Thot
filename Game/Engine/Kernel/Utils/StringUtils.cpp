#include "Kernel_PCH.h"
#include "StringUtils.h"
#include "stdio.h"

#include "Kernel/ThotWindows.h"

namespace StringUtils
{

SStringCommand::SStringCommand( const SStringCommand& other )
{
    InitFromOther(other);
}


const SStringCommand& SStringCommand::operator = ( const SStringCommand& other )
{
    InitFromOther(other);
    return *this;
}


void SStringCommand::InitFromOther( const SStringCommand& other )
{
    m_attribute = other.m_attribute;
    m_value = other.m_value;
}





char* CharToString ( char ch )
{
    static char string[] = "\0\0";
    string[0] = ch;
    return string;
}



KERNEL_API void SplitCommandLine    ( const CString& commandLine, TCommandLineArray& outCmdLine, char lineSeparator  )
{
    u64 nSize = commandLine.GetLenght();
    CString line;
    for( u64 i=0; i<nSize; i++ )
    {
        if( commandLine[i]== lineSeparator )
        {
            if( !line.IsEmpty() )
            {
                outCmdLine.PushBack( line );
            }

            line.Empty();
        }
        else
        {
            char ch[2];
            ch[1]='\0';
            ch[0] = commandLine[i];
            line += ch;
        }
    
    }

    //add last line;
    if( !line.IsEmpty() )
    {
        outCmdLine.PushBack(line);
    }
}


//--------------------------------------------------------------------------------
KERNEL_API const char* FormatString_cstr(  const char* format, ...  )
{
    if( !format )
    {
        return NULL;
    }

    const u32 maxSize = 1024 * 1024 * 4;
    static char tempBuffer[maxSize];

    va_list arg;
    va_start( arg, format );
    vsprintf_s( tempBuffer, maxSize, format, arg );
    va_end(arg);

    return tempBuffer;
}

//--------------------------------------------------------------------------------
KERNEL_API CString FormatString (  const char* format, ...  )
{
    if( !format )
    {
        return NULL;
    }

// when we have move constructor we can return this string created on stack 
#ifdef THOT_ENABLE_MOVE_CONSTRUCTOR
    CString toRet;
    
    const u32 maxSize = 1024 * 1024 * 4;
    static char tempBuffer[maxSize];


    va_list arg;
    va_start( arg, format );
    vsprintf_s( tempBuffer, maxSize, format, arg );
    va_end(arg);

    toRet = tempBuffer;

    return toRet;

#else
# error MOVE CONSTRUCTOR IS NOT ENABLED. PLEASE REWRITE THIS FUNCTIONS

#endif /*THOT_ENABLE_MOVE_CONSTRUCTOR*/ 
}



KERNEL_API  void        SplitCommandLine                ( const CString& commandLine, TCommands& outCmds, char lineSeparator, char assigner  )
{
    enum eParserState
    {
         E_STATE_NONE
        ,E_STATE_READING_EQUALS
        ,E_STATE_READING_BLANKS
        ,E_STATE_READING_ATTRIBUTE
        ,E_STATE_READING_VALUE
    };


    u64 nSize = commandLine.GetLenght();
    SStringCommand stringCommand;
    eParserState currState = E_STATE_READING_BLANKS;

#define INIT_STRING_COMMAND( __cmd) __cmd.m_attribute=""; __cmd.m_value="";

    for( u64 i=0; i<nSize; i++ )
    {
        switch( currState )
        {
        case E_STATE_READING_EQUALS:
        {
            if( commandLine[i] == lineSeparator )
            {
                currState = E_STATE_READING_BLANKS;
                outCmds.PushBack(stringCommand);
                INIT_STRING_COMMAND(stringCommand);
                continue;
            }
            else
            if( commandLine[i] == assigner )
            {
                continue;
            }
            else
            {
                currState = E_STATE_READING_VALUE;
                stringCommand.m_value += CharToString( commandLine[i] );
            }


            break;
        }

        case E_STATE_READING_BLANKS:
        {
            if( commandLine[i] == lineSeparator )
            {
                continue;
            }
            else
            if( commandLine[i] == assigner )
            {
                THOT_ASSERT(0);
                currState = E_STATE_READING_EQUALS;
                continue;
            }
            else
            {
                currState = E_STATE_READING_ATTRIBUTE;
                stringCommand.m_attribute += CharToString( commandLine[i] );
            }

            break;
        }

        case E_STATE_READING_ATTRIBUTE  :
        {
            if( commandLine[i] == lineSeparator )
            {
                currState = E_STATE_READING_BLANKS;
                outCmds.PushBack(stringCommand);
                INIT_STRING_COMMAND(stringCommand);
            }
            else
            if( commandLine[i] == assigner )
            {
                currState = E_STATE_READING_EQUALS;
                continue;
            }
            else
            {
                stringCommand.m_attribute+= CharToString( commandLine[i] );
            }


            break;
        }
        case E_STATE_READING_VALUE      :
        {
            if( commandLine[i] == lineSeparator )
            {
                currState = E_STATE_READING_BLANKS;
                outCmds.PushBack(stringCommand);
                INIT_STRING_COMMAND(stringCommand);
            }
            else
            if( commandLine[i] == assigner )
            {
                THOT_ASSERT(0);
                //currState = E_STATE_READING_EQUALS;
                continue;
            }
            else
            {
                stringCommand.m_value+= CharToString( commandLine[i] );
            }




            break;
        }
        
        
        
        }
    }

    if( !stringCommand.m_attribute.IsEmpty() || !stringCommand.m_value.IsEmpty() )
    {
        outCmds.PushBack( stringCommand );
    }

#undef INIT_STRING_COMMAND
}


KERNEL_API  CString Quote (const CString& str)
{
    return "\"" + str + "\"";
}



}
