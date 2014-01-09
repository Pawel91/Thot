#include "Lexer.h"

#include "TokenProcessor.h"
#include "TokenProcessorInstances.h"
#include "Token.h"
#include "TokenCharacterHelper.h"


#ifdef _DEBUG

//#define ASSERT_ON_TRACE

#ifndef TRACE_LEXER
#   ifndef ASSERT_ON_TRACE
#       define TRACE_LEXER(_format, ...) do{ THOT_TRACE_LINE(_format, __VA_ARGS__)}while(false);
#   else
#       define TRACE_LEXER(_format, ...) do{ THOT_ASSERT(false, _format, __VA_ARGS__); }while(false)
#   endif /*ASSERT_ON_TRACE*/
#else
#       error TRACE_LEXER allready defined; change macro name to resolve conflict;
#endif /*TRACE_LEXER*/

#else
#   define TRACE_LEXER(_format, ...) void(0)
#endif /*_DEBUG*/


#ifndef DECLARE_DEFAULT_CONSTRUCTOR_LIST
#define DECLARE_DEFAULT_CONSTRUCTOR_LIST    \
    :m_cursorPos    ( 0 )                   \
    ,m_lastTokenPos ( 0 )                   \
    ,m_outputFile   ( NULL )

#else
#   error DECLARE_DEFAULT_CONSTRUCTOR_LIST allready defined
#endif 


CLexer::CLexer( )
    DECLARE_DEFAULT_CONSTRUCTOR_LIST
{
    for( u64 i=0; i<m_tokenProcessorCreateCallbacks.GetSize(); i++)
    {
        m_tokenProcessorCreateCallbacks[i] = NULL;
    }
}

CLexer::CLexer ( const CString& fileName )
    DECLARE_DEFAULT_CONSTRUCTOR_LIST
{
    for( u64 i=0; i<m_tokenProcessorCreateCallbacks.GetSize(); i++)
    {
        m_tokenProcessorCreateCallbacks[i] = NULL;
    }
}

CLexer::~CLexer()
{
    if( m_outputFile )
    {
        FileSystem::DestroyFile( m_outputFile );
    }
}

Bool CLexer::GetNextToken( CToken& outToken )
{
    outToken.m_lexer = this;

    if( m_sourceCode.GetLenght() == 0 )
    {
        TRACE_LEXER( "SOURCE CODE IS NULL" );
        return false;
    }

    if( m_cursorPos >= m_sourceCode.GetLenght() )
    {
        return false;
    }

    THOT_ASSERT( m_cursorPos == m_lastTokenPos );

    // remove the blank characters;
    if( !CTokenCharacterHelper::s_GetInstance() )
    {
        CTokenCharacterHelper::s_CreateInstance();
    }

    while(  CTokenCharacterHelper::s_GetInstance()->IsBlank(  m_sourceCode[m_cursorPos] ) )
    {
        m_lastTokenPos = ++m_cursorPos;
        if( m_cursorPos >= m_sourceCode.GetLenght() )
        {
            return false;
        }
    }

    CVector<ITokenProcessor*> tokenProcessors;
    CVector<ITokenProcessor*> matchedProcessors;

    TCursor matchedCursor = m_cursorPos;

    GetUnblockedProcessors( tokenProcessors );
    ITokenProcessor* lastTokenProcessor = NULL;

    while( tokenProcessors.GetSize() > 0 )
    {
        if( m_cursorPos >= m_sourceCode.GetLenght() )
        {
            break;
        }

        char ch = m_sourceCode[m_cursorPos];
        AddInputToProcessors( tokenProcessors, ch );
        GetUnblockedProcessors(tokenProcessors);

        CVector<ITokenProcessor*> tempVector;
        GetMatchedProcessors( tokenProcessors, tempVector );

        if( tempVector.GetSize() > 0 )
        {
            CVector<ITokenProcessor*>::CopyVectors( matchedProcessors, tempVector );
            matchedCursor = m_cursorPos;
        }

        m_cursorPos++;
    }

    m_cursorPos = matchedCursor + 1;

    if( matchedProcessors.GetSize()==0  )
    {
        return false;
    }
    else if(matchedProcessors.GetSize()==1 )
    {
        lastTokenProcessor = matchedProcessors[0];
    }
    else if(matchedProcessors.GetSize()==2 ) //[TODO] find a way to remove this case;
    {
        if  (   ( matchedProcessors[0]->GetType() == E_TOKEN_TYPE_KEY_WORD && matchedProcessors[1]->GetType() == E_TOKEN_TYPE_IDENTIFIER ) ||
                ( matchedProcessors[1]->GetType() == E_TOKEN_TYPE_KEY_WORD && matchedProcessors[0]->GetType() == E_TOKEN_TYPE_IDENTIFIER )
            )
        {
            lastTokenProcessor = (matchedProcessors[0]->GetType() == E_TOKEN_TYPE_KEY_WORD)? matchedProcessors[0] : matchedProcessors[1];
        }
        else if  (  ( matchedProcessors[0]->GetType() == E_TOKEN_TYPE_LITERAL_FLOAT && matchedProcessors[1]->GetType() == E_TOKEN_TYPE_LITERAL_INTEGER ) ||
                    ( matchedProcessors[1]->GetType() == E_TOKEN_TYPE_LITERAL_FLOAT && matchedProcessors[0]->GetType() == E_TOKEN_TYPE_LITERAL_INTEGER )
                )
        {
            lastTokenProcessor = (matchedProcessors[0]->GetType() == E_TOKEN_TYPE_LITERAL_INTEGER)? matchedProcessors[0] : matchedProcessors[1];
        }
        else
        {
            THOT_ASSERT(false, " to many token processors. Current content = [%s]", GetCurrentContent().GetBuffer() );
        }
    }
    else
    {
        THOT_ASSERT(false, " to many token processors. Current content = [%s]", GetCurrentContent().GetBuffer() );
    }


    // get the token content from source code between m_lastTokenPos and m_cursorPos
    CString currentTokenContent = GetCurrentContent( );
    
    THOT_ASSERT( currentTokenContent.GetLenght() > 0, "current token content must not be null" );

    // set last token pos to current cursor pos
    m_lastTokenPos = m_cursorPos;


    if(     lastTokenProcessor->GetType() == E_TOKEN_TYPE_COMMENT_MULTILINE 
        ||  lastTokenProcessor->GetType() == E_TOKEN_TYPE_COMMENT_SINGLELINE )
    {
        ResetAllProcessor( );
        return GetNextToken( outToken );
    }


    // put parameters into output token
    outToken.m_contentHandle =  FindCreateTokenContentHandle( currentTokenContent );
    outToken.m_tokenType = lastTokenProcessor->GetType( );


    // reset all processor so it can be used next time
    ResetAllProcessor( );

    return true;
}


void CLexer::DebugPrintMultipleTokensCase( const CVector<ITokenProcessor*>& processors )
{

}

CString CLexer::GetCurrentContent( )
{
    CString currentTokenContent;

    //THOT_ASSERT(false, "CString::SubStr function has been change. please rewrite the code");
    m_sourceCode.SubStr( m_lastTokenPos, m_cursorPos-m_lastTokenPos, currentTokenContent );
    return currentTokenContent;
}

Bool CLexer::Init( )
{

    if( !RegisterAllTokenProcessors() )
    {
        THOT_TRACE_LINE( "Cannot init all token processors" );
        return false;
    }

    if( !CreateAllTokenProcessor() )
    {
        THOT_TRACE_LINE( "Cannot create all token processors" );
        return false;
    }

    if( !BuildProcessorsStateMachines() )
    {
        THOT_TRACE_LINE( "Cannot build state machine for all processors" ) ;
        return false;
    }

    return true;
}

ITokenProcessor* CLexer::CreateTokenProcessor( ETokenType tokenType )
{
    THOT_ASSERT(tokenType>=0 && tokenType < E_TOKEN_TYPE_COUNT, "Value[%d] is not a token", tokenType );
    u64 callbackIdx = ThNumericCast<u64>(tokenType);

    if( !m_tokenProcessorCreateCallbacks[callbackIdx] )
    {
        return NULL;
    }

    ITokenProcessor* tokenProcessor = m_tokenProcessorCreateCallbacks[callbackIdx]();
    
    THOT_ASSERT(tokenProcessor->GetType() == (ETokenType)callbackIdx, "Token of type[%s] is not in the right index in token array", ToString(tokenType) );

    tokenProcessor->SetLexerOwner(this);

    return tokenProcessor;
}

const CString& CLexer::GetTokenContent( u32 handle )
{
    return m_tokensContent[ ThNumericCast<u64, u32>(handle)];
}

Bool CLexer::RegisterAllTokenProcessors ( )
{
    bool registerSucceded = true;

#define REGISTER_TOKEN_PROCESSOR_CLASS(__className, __tokenType) \
    registerSucceded &= RegisterTokenProcessor<__className>();

REGISTER_TOKEN_PROCESSOR_CLASS( CTokenIdentifierProcessor,          E_TOKEN_TYPE_IDENTIFIER );
REGISTER_TOKEN_PROCESSOR_CLASS( CTokenOperatorProcessor,            E_TOKEN_TYPE_OPERATOR );
REGISTER_TOKEN_PROCESSOR_CLASS( CTokenCommentSingleLineProcessor,   E_TOKEN_TYPE_COMMENT_SINGLELINE );
REGISTER_TOKEN_PROCESSOR_CLASS( CTokenCommentMultiLineProcessor,    E_TOKEN_TYPE_COMMENT_MULTILINE );
REGISTER_TOKEN_PROCESSOR_CLASS( CTokenKeyWordProcessor,             E_TOKEN_TYPE_KEY_WORD );
REGISTER_TOKEN_PROCESSOR_CLASS( CTokenLiteralStringProcessor,       E_TOKEN_TYPE_LITERAL_STRING );
REGISTER_TOKEN_PROCESSOR_CLASS( CTokenLiteralFloatProcessor,        E_TOKEN_TYPE_LITERAL_FLOAT );
REGISTER_TOKEN_PROCESSOR_CLASS( CTokenLiteralIntegerProcessor,      E_TOKEN_TYPE_LITERAL_INTEGER );
REGISTER_TOKEN_PROCESSOR_CLASS( CTokenPunctuatorProcessor,          E_TOKEN_TYPE_PUNCTUATOR );
REGISTER_TOKEN_PROCESSOR_CLASS( CTokenCharLiteral,                  E_TOKEN_TYPE_LITERAL_CHAR );

    return registerSucceded;

#undef REGISTER_TOKEN_CLASS
}


Bool CLexer::CreateAllTokenProcessor( )
{
    for( u64 i=0; i<m_tokenProcessors.GetSize(); i++ )
    {
        if( m_tokenProcessorCreateCallbacks[i] )
        {
            m_tokenProcessors[i] = CreateTokenProcessor( (ETokenType)i );
            THOT_ASSERT(m_tokenProcessors[i], "Cannot create a token processor of type[%s]", ToString((ETokenType)i) );
        }
        else
        {
            return false;
        }
    }

    return true; // registration of all token succeeded;
}


ITokenProcessor* CLexer::GetTokenProcessor( ETokenType tokenType )
{
    return m_tokenProcessors[ThNumericCast<u64, ETokenType>(tokenType)];    
}


const ITokenProcessor* CLexer::GetTokenProcessor( ETokenType tokenType )const
{
    return m_tokenProcessors[ThNumericCast<u64, ETokenType>(tokenType)];
}

Bool CLexer::BuildProcessorsStateMachines( )
{
    Bool rezult = true;
    for( u64 i=0; i<m_tokenProcessors.GetSize(); i++ )
    {
        THOT_ASSERT(m_tokenProcessors[i], "Processor is not initialized");
        ITokenProcessor* processor = m_tokenProcessors[i];
        if( !processor->BuildPatternMatcher() )
        {
            TRACE_LEXER( "failed to build state machine for processor type [%s]", ToString( processor->GetType() ) );
            rezult = false;
        }
    }

    return rezult;
}


Bool CLexer::ResetAllProcessor( )
{
    for( u64 i=0; i<m_tokenProcessors.GetSize(); i++ )
    {
        ITokenProcessor* processor = m_tokenProcessors[i];
        THOT_ASSERT( processor );
        processor->Reset();
    }

    return true;
}

Bool CLexer::AddInputToProcessors( CVector<ITokenProcessor*>& processors, char ch )
{
    for( u64 i=0; i<processors.GetSize(); i++ )
    {
        ITokenProcessor* processor = processors[i];
        THOT_ASSERT(processor);

        ITokenProcessor::TTokenPatternMatcher* patternMatcher = processor->GetPatternMatcher();
        THOT_ASSERT( patternMatcher );
        patternMatcher->TakeInput( ch );
    }

    return true;
}


void CLexer::GetUnblockedProcessors( CVector<ITokenProcessor*>& outProcessors )
{
    outProcessors.Resize(0);

    for( u64 i=0; i<m_tokenProcessors.GetSize(); i++ )
    {
        ITokenProcessor* tokenProcessor = m_tokenProcessors[i];
        THOT_ASSERT( tokenProcessor && tokenProcessor->GetPatternMatcher() );

        if( !tokenProcessor->GetPatternMatcher()->IsBlocked() )
        {
            outProcessors.Add( tokenProcessor );
        }
    }
}


CToken::TTokenContentHandle CLexer::FindCreateTokenContentHandle ( const CString& string )
{
    u64 index = m_tokensContent.Find( string, CString::Compare );

    // if not found we will add it
    if( index == TTokensContent::ms_invalidIndex )
    {
        index = m_tokensContent.Add( string );
    }

    return ThNumericCast<CToken::TTokenContentHandle>(index);
}

Bool CLexer::ReadSourceCode( const CString& filePath )
{
    m_fileName = filePath;
    FileSystem::FileHandle pFile = FileSystem::CreateFile( EFileType::E_FILE_TYPE_MEMORY );
    if( !pFile )
    {
        return false;
    }

    if( !pFile->Open( filePath, EAccesMode::E_ACCES_MODE_READ ) )
    {
        return false;
    }

    u64 fileSize = pFile->GetSize();
    m_sourceCode.Resize( fileSize );

    if( !pFile->Read( m_sourceCode.GetBuffer(), fileSize, 1 )  )
    {
        return false;
    }

    //FileSystem::DestroyFile(pFile);

    return true;
}

Bool CLexer::WriteToken( const CToken& token )
{
    //if( token.m_tokenType == E_TOKEN_TYPE_COMMENT_SINGLELINE || token.m_tokenType == E_TOKEN_TYPE_COMMENT_MULTILINE )
    //{
    //    return true;
    //}

    if( !m_outputFile )
    {
        return false;
    }

    CString tokenString = token.ToString();
    tokenString += "\n";
    if( !m_outputFile->Write( tokenString.GetBuffer(), tokenString.GetLenght(), 1 ) )
    {
        return false;
    }

    return true;
}

void CLexer::OnExit( )
{
    if( !m_outputFile )
    {
        return;
    }
    CString message;
    if( m_cursorPos != m_sourceCode.GetLenght() )
    {
        //char tmpBuffer[200];
        //itoa( m_cursorPos, tmpBuffer, 10 );
        message = CString("\nSINTAX ERROR!!!!!!!"); //+ tmpBuffer;
        if( !m_outputFile->Write( message.GetBuffer(), message.GetLenght(), 1 ) )
        {
            THOT_ASSERT(false);
        }
    }
}

Bool CLexer::SetOutputFile( const CString& filePath )
{
    
    if( m_outputFile )
    {
        FileSystem::DestroyFile( m_outputFile );
        m_outputFile = NULL;
    }


    m_outputFile = FileSystem::CreateFile( EFileType::E_FILE_TYPE_MEMORY );
    if( !m_outputFile )
    {
        return false;
    }


    if( !m_outputFile->Open( filePath, EAccesMode::E_ACCES_MODE_READ | EAccesMode::E_ACCES_MODE_WRITE ) )
    {
        TRACE_LEXER( "failed to open output file[%s]", filePath.GetBuffer() );
        return false;
    }

    return true;
}


void CLexer::GetMatchedProcessors( const CVector<ITokenProcessor*>& processors, CVector<ITokenProcessor*>& out )
{
    out.Resize(0);

    for( u64 i=0; i<processors.GetSize(); i++ )
    {
        ITokenProcessor* tokenProcessor = processors[i];
        if( tokenProcessor && tokenProcessor->GetPatternMatcher() && tokenProcessor->GetPatternMatcher()->IsMatch() )
        {
            out.Add( tokenProcessor );
        }
    }
}