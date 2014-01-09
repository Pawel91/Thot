#pragma once
#ifndef __FILE_TYPES_H__
#define __FILE_TYPES_H__
#include "../DataTypes.h"

enum class EFileType
:S32
{
     E_FILE_TYPE_NONE        =-1
    ,E_FILE_TYPE_NORMAL
    ,E_FILE_TYPE_MEMORY
    
    ,E_FILE_TYPE_COUNT
};

enum EAccesMode
{
     E_ACCES_MODE_NONE      = 0xffffffff
    ,E_ACCES_MODE_READ      = 1<<1
    ,E_ACCES_MODE_WRITE     = 1<<2
    ,E_ACCES_MODE_APPEND    = 1<<3
    ,E_ACCES_MODE_TEXT      = 1<<4  // for text files
};

enum class ESeek
:S32
{
     E_SEEK_NONE         =-1
    
    ,E_SEEK_BEGIN
    ,E_SEEK_CURR
    ,E_SEEK_END

    ,E_SEEK_COUNT
};

#endif /*__FILE_TYPES_H__*/