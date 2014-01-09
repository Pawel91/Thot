#pragma once
#ifndef __TEHNICI_COMPILARE_TOKEN_INSTANCES_H__
#define __TEHNICI_COMPILARE_TOKEN_INSTANCES_H__

#include "TokenProcessor.h"


#define DECLARE_INTERFACE_OF_TOKEN_PROCESSOR_CLASS( __className, __tokenType )    \
class __className: public ITokenProcessor                                        \
{                                                                       \
    DECLARE_TOKEN_PROCESSOR_CLASS( __className, __tokenType );   \
public:                                                                 \
    Bool        BuildPatternMatcher()     override;                       \
virtual const char* GetProcessorName () override { return #__className;}    \
}

DECLARE_INTERFACE_OF_TOKEN_PROCESSOR_CLASS( CTokenCommentSingleLineProcessor,   E_TOKEN_TYPE_COMMENT_SINGLELINE );  // DONE
DECLARE_INTERFACE_OF_TOKEN_PROCESSOR_CLASS( CTokenCommentMultiLineProcessor,    E_TOKEN_TYPE_COMMENT_MULTILINE );   // DONE
DECLARE_INTERFACE_OF_TOKEN_PROCESSOR_CLASS( CTokenLiteralStringProcessor,       E_TOKEN_TYPE_LITERAL_STRING );      // DONE
DECLARE_INTERFACE_OF_TOKEN_PROCESSOR_CLASS( CTokenLiteralFloatProcessor,        E_TOKEN_TYPE_LITERAL_FLOAT );       // DONE
DECLARE_INTERFACE_OF_TOKEN_PROCESSOR_CLASS( CTokenLiteralIntegerProcessor,      E_TOKEN_TYPE_LITERAL_INTEGER );     // DONE
DECLARE_INTERFACE_OF_TOKEN_PROCESSOR_CLASS( CTokenCharLiteral,                  E_TOKEN_TYPE_LITERAL_CHAR );
DECLARE_INTERFACE_OF_TOKEN_PROCESSOR_CLASS( CTokenKeyWordProcessor,             E_TOKEN_TYPE_KEY_WORD );
DECLARE_INTERFACE_OF_TOKEN_PROCESSOR_CLASS( CTokenIdentifierProcessor,          E_TOKEN_TYPE_IDENTIFIER );
DECLARE_INTERFACE_OF_TOKEN_PROCESSOR_CLASS( CTokenOperatorProcessor,            E_TOKEN_TYPE_OPERATOR );
DECLARE_INTERFACE_OF_TOKEN_PROCESSOR_CLASS( CTokenPunctuatorProcessor,          E_TOKEN_TYPE_PUNCTUATOR );



#endif /*__TEHNICI_COMPILARE_TOKEN_INSTANCES_H__*/