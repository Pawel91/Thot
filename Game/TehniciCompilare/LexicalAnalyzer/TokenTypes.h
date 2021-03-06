#pragma once
#ifndef __TEHNICI_COMPILARE_TOKEN_TYPES_H__
#define __TEHNICI_COMPILARE_TOKEN_TYPES_H__
#include "Kernel\KernelUtils.h"

enum ETokenType
{
    E_TOKEN_TYPE_NONE = -1

    ,E_TOKEN_TYPE_KEY_WORD
    ,E_TOKEN_TYPE_IDENTIFIER
    ,E_TOKEN_TYPE_OPERATOR
    ,E_TOKEN_TYPE_COMMENT_MULTILINE
    ,E_TOKEN_TYPE_COMMENT_SINGLELINE
    ,E_TOKEN_TYPE_LITERAL_STRING
    ,E_TOKEN_TYPE_LITERAL_INTEGER
    ,E_TOKEN_TYPE_LITERAL_FLOAT
    ,E_TOKEN_TYPE_LITERAL_CHAR
    ,E_TOKEN_TYPE_PUNCTUATOR

    ,E_TOKEN_TYPE_COUNT
};

THOT_FORCE_INLINE CString ToString( ETokenType type )
{
#ifndef THOT_STRINGIFY
#   define THOT_STRINGIFY(x) (#x)
#endif 

#define TOKEN_TYPE_TO_STRING(__type) CString( THOT_STRINGIFY(__type) )

    static CString stringArray[]    = {  
     TOKEN_TYPE_TO_STRING ( E_TOKEN_TYPE_KEY_WORD )
    ,TOKEN_TYPE_TO_STRING ( E_TOKEN_TYPE_IDENTIFIER )
    ,TOKEN_TYPE_TO_STRING ( E_TOKEN_TYPE_OPERATOR )
    ,TOKEN_TYPE_TO_STRING ( E_TOKEN_TYPE_COMMENT_MULTILINE )
    ,TOKEN_TYPE_TO_STRING ( E_TOKEN_TYPE_COMMENT_SINGLELINE )
    ,TOKEN_TYPE_TO_STRING ( E_TOKEN_TYPE_LITERAL_STRING )
    ,TOKEN_TYPE_TO_STRING ( E_TOKEN_TYPE_LITERAL_INTEGER )
    ,TOKEN_TYPE_TO_STRING ( E_TOKEN_TYPE_LITERAL_FLOAT )
    ,TOKEN_TYPE_TO_STRING ( E_TOKEN_TYPE_LITERAL_CHAR )
    ,TOKEN_TYPE_TO_STRING ( E_TOKEN_TYPE_PUNCTUATOR )

                };

    THOT_ASSERT( type >=0 && type <E_TOKEN_TYPE_COUNT, "parameter is not a ETokenType" );
    return stringArray[type];


#undef TOKEN_TYPE_TO_STRING
}



#endif /*__TEHNICI_COMPILARE_TOKEN_TYPES_H__*/