#pragma once
#include "TokenTypes.h"
#include "Token.h"


class ITokenProcessor;
class CToken;


class IFile;

class CLexer
{

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
            CLexer( );
            CLexer ( const CString& fileName );
virtual    ~CLexer();



//*********************************************
//            INTERFACE
//*********************************************
public:
    typedef ITokenProcessor* (*pfnTokenProcessorCreator)();
    typedef CStaticArray < pfnTokenProcessorCreator, E_TOKEN_TYPE_COUNT > TTokenProcessorCreateCallbacks;

    typedef CVector<CString>                                    TTokensContent;
    typedef CStaticArray<ITokenProcessor*,E_TOKEN_TYPE_COUNT>         TTokenProcessorArray;
    typedef u64                                                 TCursor;



        Bool                        Init                        ( ); // init the lexer

        u64                         GetCursorPos                () { return m_cursorPos; }
        ITokenProcessor*            GetTokenProcessor           ( ETokenType tokenType );
        const ITokenProcessor*      GetTokenProcessor           ( ETokenType tokenType )const;

        Bool                ReadSourceCode          ( const CString& filePath );
        Bool                SetOutputFile           ( const CString& filePath );
        Bool                WriteToken              ( const CToken& token );
        void                OnExit                  ( );

        // return false in case of error in the parser
        Bool                GetNextToken            ( CToken& outToken );

        const CString&      GetTokenContent         ( u32 handle );



//*********************************************
//            HELPERS
//*********************************************
protected:
        ITokenProcessor*    CreateTokenProcessor            ( ETokenType tokenType );
        Bool                BuildProcessorsStateMachines    ( );
        Bool                RegisterAllTokenProcessors      ( );
        Bool                CreateAllTokenProcessor         ( );

        Bool                ResetAllProcessor               ( );
        Bool                AddInputToProcessors            ( CVector<ITokenProcessor*>& processors, char ch );
        void                GetUnblockedProcessors          ( CVector<ITokenProcessor*>& outProcessors );
        void                GetMatchedProcessors            ( const CVector<ITokenProcessor*>& processors, CVector<ITokenProcessor*>& out );

        CString             GetCurrentContent               ( );

        void                DebugPrintMultipleTokensCase    ( const CVector<ITokenProcessor*>& processors );

        CToken::TTokenContentHandle FindCreateTokenContentHandle ( const CString& string );

        template<class T>
        Bool                RegisterTokenProcessor  ( ); // register a token


//*********************************************
//            MEMBERS
//*********************************************
protected:
            FileSystem::FileHandle              m_outputFile;                       // file to output tokens
            CString                             m_fileName;                         // name of the file to be analysed;
            CString                             m_sourceCode;                       // source code of the file;
            TTokensContent                      m_tokensContent;                    // array with all tokens;
            TCursor                             m_lastTokenPos;
            TCursor                             m_cursorPos;                        // current position in the file;
            TTokenProcessorArray                m_tokenProcessors;                  // array with all created tokens
            TTokenProcessorCreateCallbacks      m_tokenProcessorCreateCallbacks;    // array with pointer to function; to create tokens    
};


template<class T>
inline Bool CLexer::RegisterTokenProcessor( )
{
    u64 callbackIdx = ThNumericCast<u64>(T::GetTokenType());

    if( m_tokenProcessorCreateCallbacks[callbackIdx] != NULL )
    {
        THOT_TRACE_LINE("THIS TOKEN IS ALLREADY REGISTRED");
        return false;
    }

    m_tokenProcessorCreateCallbacks[callbackIdx] = T::CreateNewInstance ;
    return true;
}