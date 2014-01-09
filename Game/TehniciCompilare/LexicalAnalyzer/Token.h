#ifndef __TEHNICI_COMPILARE_TOKEN_H__
#define __TEHNICI_COMPILARE_TOKEN_H__

#include "TokenTypes.h"


class CLexer;

class CToken
{
friend class CLexer;

public:
    CToken();

public:
    typedef u32     TTokenContentHandle;


    CString         ToString    ()const;
    Bool            GetContent  ( CString& outString )const;

protected:
    static u32      ms_invalidContentHandle;

    CLexer*                 m_lexer;                // lexer owner
    TTokenContentHandle     m_contentHandle;        // index of content in the content array of lexer
    ETokenType              m_tokenType;
};




#endif /*__TEHNICI_COMPILARE_TOKEN_H__*/