#pragma once
#ifndef __KERNEL_DATA_TYPES_H__
#define __KERNEL_DATA_TYPES_H__

#include "Kernel/Basics/CompilerSpecific.h"

#if defined(THOT_PLATFORM_WINDOWS)

    typedef bool Bool;

    typedef unsigned long           dword;
    typedef unsigned short          word;
    typedef unsigned int            uint;

    // 8 bit types
    typedef __int8                  s8;
    typedef unsigned __int8         u8;
    typedef u8                      byte;
    #ifndef S8
    #   define S8   __int8
    #else
    #   error "S8 is allready defined"
    #endif S8

    #ifndef U8
    #   define U8 unsigned __int8
    #else
    #   error "U8 is allready defined"
    #endif //U8



    // 16 bit types
    typedef __int16                 s16;
    typedef unsigned __int16        u16;
    #ifndef S16
    #   define S16 __int16
    #else
    #   error "S16 is allready defined"
    #endif //S16

    #ifndef U16
    #   define U16 unsigned __int16
    #else
    #   error "U16 is allready defined"
    #endif //U16


    //32 bit types
    typedef __int32                 s32;
    typedef unsigned __int32        u32;
    #ifndef S32
    #   define S32 __int32
    #else
    #   error "S32 is allready defined"
    #endif //S32

    #ifndef U32
    #   define U32 unsigned __int32
    #else
    #   error "U32 is allready defined"
    #endif //U32





    //64 bit types
    typedef __int64                 s64;
    typedef unsigned __int64        u64;
    #ifndef S64
    #   define S64 __int64
    #else
    #   error "S64 is allready defined"
    #endif //S64

    #ifndef U64
    #   define U64 unsigned __int64
    #else
    #   error "U64 is allready defined"
    #endif //U64


    #ifndef NULL
    #   define NULL nullptr
    #else
    //#   error Kernel MUST NOT INTERFERE WITH OTHER LIBRARYES DIRECTLY
    #pragma message("********[WARNING]   NULL WAS ALLREADY DEFINED")
    #endif /*NULL*/


#if defined(THOT_PLATFORM_ARCH_X64)
    typedef u64     thSize;
#else
    typedef u32     thSize;
#endif 


#if !defined(_SIZE_T_DEFINED)
typedef thSize size_t;
#define _SIZE_T_DEFINED
#else
#   error WHERE DA FUCK THIS WAS DEFINED
#endif


#else
#   error "BASIC TYPES ARE UNDEFINED FOR THIS PLATFORM"
#endif /*(defined _WIN32 || defined _WIN64) && defined   _MSC_VER*/

//static_assert( sizeof(void*)==8, "ONLY 64 bit platform supported" );
static_assert( sizeof(u8    )==1, "u8       TYPE MUST HAVE 1 BYTE");
static_assert( sizeof(s8    )==1, "s8       TYPE MUST HAVE 1 BYTE");
static_assert( sizeof(byte  )==1, "byte     TYPE MUST HAVE 1 BYTE");

static_assert( sizeof(u16    )==2, "u16       TYPE MUST HAVE 2 BYTES");
static_assert( sizeof(s16    )==2, "s16       TYPE MUST HAVE 2 BYTES");

static_assert( sizeof(u32    )==4, "u32       TYPE MUST HAVE 4 BYTES");
static_assert( sizeof(s32    )==4, "s32       TYPE MUST HAVE 4 BYTES");


#endif