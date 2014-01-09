#include "Kernel\Kernel.h"


#include "stdio.h"
#include "windows.h"
#include "direct.h"

#include "FiniteStateMachine/FiniteStateMachine.h"
#include "LexicalAnalyzer/Lexer.h"
#include "LexicalAnalyzer/TokenCharacterHelper.h"
#include "LexicalAnalyzer/TokenProcessor.h"
#include "Compiler/Compiler.h"
#include "Compiler/EntryPoint.h"

#ifdef CreateFile
#undef CreateFile
#endif




template class  CSmartPtr<IFile>;




s32 CompareFunction( char const& op1, char const& op2 )
{
    return op1-op2;
}


class CClassDestructor
{
public:
    CClassDestructor()
    {
        someData = 0xFFFFFFFF;
    }
    ~CClassDestructor(){someData = 13;}

    u32 someData;
};

class CSimpleClass
{
public:
    u32 someData;
};

struct SMemoryHeader
{
    enum 
    {
        NEW,
        NEW_ARRAY,
        MALLOC
    };

    u32 m_fromID ;
    union
    {
        u8      m_compilerInfo[8];

        struct  
        {
            u32 m_uselessData;

            union
            {
                Bool m_hasDestructor;
                u32 m_objectCount;
            };
            
        };

    };
};


void* operator new[] ( size_t size )
{
    u8* memory = (u8*) malloc( size + sizeof(SMemoryHeader) );
    SMemoryHeader* header = (SMemoryHeader*)memory;
    ThZeroMemoryTmpl(*header);
    header->m_fromID = SMemoryHeader::NEW_ARRAY;
    

    memory += sizeof(SMemoryHeader);
    return memory;
}

void operator delete[]( void* memory )
{
    if( !memory )
    {
        return ;
    }

    u8* realMem = (u8*) memory - sizeof(SMemoryHeader);
    SMemoryHeader* header = (SMemoryHeader*) realMem;
    free(realMem);
}

int main( int argc, char* argv[] )
{
    size_t size = sizeof(SMemoryHeader);

    CClassDestructor* mem = new CClassDestructor[213];
    THOT_TRACE_LINE( "%d", mem->someData);
    delete[] mem;

    //return 0;
    CRegex regex( "error C[0-9]+:[^\n]*", true );
    CRegex::TCaptures captures;

    if( regex.Match( "1>TehniciCompilare.cpp(31): error C2065: 'asd' : undeclared identifier" ) )
    {
        THOT_TRACE_LINE("DA");
    }
    else
    {
        THOT_TRACE_LINE("NU");
    }


    CString out = regex.Replace( "1>TehniciCompilare.cpp(31): error C2065: 'asd' : undeclared identifier\n1>TehniciCompilare.cpp(31): error C2065: 'myasda' : undeclared identifier", " PULA MEA" );

    CRegex::TCaptures findResult;
    regex.Find("1>TehniciCompilare.cpp(31): error C2065: 'asd' : undeclared identifier\n1>TehniciCompilare.cpp(31): error C2065: 'myasda' : undeclared identifier", findResult);


    const char* sourceCode = "#include <stdio.h>\n int main(){int n = -100; scanf(\"%d\",&n);printf(\"%d\",n+3);}";

    const char* str =  _Compile( sourceCode, "3 5", "c:\\Users\\Radu\\Documents\\GitHub\\InfoBac\\CompilerDummy\\" );
    Bool rez = true;
    if( rez == false )
    {
        THOT_TRACE_LINE( "Compilation failed\n" );
    }
    else
    {
        THOT_TRACE_LINE( "Compilation succeded\n" );
    }

//#define TEMA_TEHNICI_COMPILARE
#if defined(TEMA_TEHNICI_COMPILARE)
    CAutomataState<char>::RegisterCompareFunction( CompareFunction );

    CLexer lexer;
    bool rez = lexer.Init();
    if( !rez )
    {}
   
    if( !lexer.ReadSourceCode("sourceCode.cpp") )
    {
        return -1;
    }

    if( !lexer.SetOutputFile("tokens.out") )
    {
        THOT_ASSERT(false);
        return -1;
    }


    CString testString("01234");
    CString substr;
    testString.SubStr( 0, 2, substr );

        

    CToken token;
    
    //[TODO]!!!!!!!!!! test character literal automata
    while( lexer.GetNextToken( token ) )
    {

        CString tokenContent;
        token.GetContent(tokenContent);

        THOT_TRACE_LINE("%s", token.ToString().GetBuffer() );

        lexer.WriteToken( token );
    }

    lexer.OnExit();


#endif /*TEMA_TEHNICI_COMPILARE*/
    return 0;
}

