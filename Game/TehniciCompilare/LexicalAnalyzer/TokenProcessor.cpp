#include "TokenProcessor.h"
#include "Lexer.h"
#include "TokenCharacterHelper.h"


#ifndef DECLARE_DEFAULT_CONSTRUCTOR_LIST

#define DECLARE_DEFAULT_CONSTRUCTOR_LIST            \
:m_eTokenType           ( E_TOKEN_TYPE_NONE )       \
,m_lexer                ( NULL )                    \
,m_patternMatcher         ( NULL )



#endif /*DECLARE_DEFAULT_CONSTRUCTOR_LIST*/


ITokenProcessor::ITokenProcessor()
    DECLARE_DEFAULT_CONSTRUCTOR_LIST
{
    if( !CTokenCharacterHelper::s_GetInstance() )
    {
        CTokenCharacterHelper::s_CreateInstance();
        CTokenCharacterHelper::s_GetInstance()->OnInit();
    }

}



Bool ITokenProcessor::SetLexerOwner   ( CLexer* lexer )
{
    if( !lexer )
    {
        return false;
    }

    m_lexer = lexer;

    return true;
}

ITokenProcessor::~ITokenProcessor(){}

ITokenProcessor::TTokenPatternMatcher* ITokenProcessor::GetPatternMatcher ()
{
    return m_patternMatcher;
}

const ITokenProcessor::TTokenPatternMatcher* ITokenProcessor::GetPatternMatcher ()const
{
    return m_patternMatcher;
}

void ITokenProcessor::Reset()
{
    m_patternMatcher->Reset();
}