#include "Token.h"
#include "Lexer.h"

u32         CToken::ms_invalidContentHandle     = 0xffffffff;


CToken::CToken()
    :m_lexer            ( NULL )
    ,m_contentHandle    ( ms_invalidContentHandle )
    ,m_tokenType        ( E_TOKEN_TYPE_NONE )
{
}

Bool CToken::GetContent ( CString& outString )const
{
    outString = "";
    
    if( !m_lexer || m_contentHandle == ms_invalidContentHandle )
    {
        return false;
    }

    outString = m_lexer->GetTokenContent( m_contentHandle );

    return true;
}

CString CToken::ToString()const
{
    CString tokenType = ::ToString( m_tokenType );
    CString content;
    GetContent( content );

    CString out = tokenType + ": " + content;
    return out;
}