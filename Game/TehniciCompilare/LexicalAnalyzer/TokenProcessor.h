#pragma once
#ifndef __TEHNICI_COMPILARE_TOKEN_PROCESSOR_H__
#define __TEHNICI_COMPILARE_TOKEN_PROCESSOR_H__

#include "TokenTypes.h"
#include "..//FiniteStateMachine/FiniteStateMachine.h"
#include "..//FiniteStateMachine/PatternMatcher.h"

class CLexer;


#define DECLARE_TOKEN_PROCESSOR_CLASS(__className, __tokenType)             \
public:                                                                     \
static ITokenProcessor* CreateNewInstance() { __className* ptr = snew(__className); ptr->SetType(__tokenType); return ptr;} \
static ETokenType GetTokenType()  { return __tokenType; }       \
static CString      GetName()       { return CString(THOT_STRINGIFY(__className));}


template class CFiniteStateMachine<char>;

class ITokenProcessor
{
friend class CLexer;


//*********************************************
//            CONSTR/DESTR
//*********************************************
protected:
            ITokenProcessor ( );
virtual     ~ITokenProcessor( )    = 0;



//*********************************************
//            INTERFACE
//*********************************************
public:
    typedef IPatternMatcher<char>           TTokenPatternMatcher; 
    typedef CAutomataState<char>            TTokenState;

virtual     const char*                     GetProcessorName    ( ) = 0;  
virtual     Bool                            BuildPatternMatcher ( ) = 0;

            ETokenType                      GetType             ( )const                    { return m_eTokenType;}
            void                            SetType             ( ETokenType tokenType )    {m_eTokenType = tokenType; }

            TTokenPatternMatcher*           GetPatternMatcher   ();
            const TTokenPatternMatcher*     GetPatternMatcher   ()const;

            void                            Reset               ();

protected:

            Bool                            SetLexerOwner       ( CLexer* lexer );

//*********************************************
//            MEMBERS
//*********************************************
protected:

    ETokenType                  m_eTokenType;           // type of this toke
    CLexer*                     m_lexer;                // lexer that owns this token
    TTokenPatternMatcher*       m_patternMatcher;         // state machine to recognize this token

};





#endif /*__TEHNICI_COMPILARE_TOKEN_H__*/