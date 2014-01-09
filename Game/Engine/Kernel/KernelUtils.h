#ifndef __KERNEL_UTILS_H__
#define __KERNEL_UTILS_H__


#include "Kernel/DebugSystem/Assert.h"
#include "Kernel/Defines.h"

//--------------------------------------------------------------------------------
inline float bToKb( u64 bytes)
{
    float result = ((float)bytes)/1024.0f;
    return result;
}

//--------------------------------------------------------------------------------
template <class T, class U>
inline T ThMax( const T&a, const U& b )
{
    T _b = ThNumericCast<T>(b);
    return (a>_b)?a:_b;
}

//--------------------------------------------------------------------------------
template <class T>
inline T ThMin( const T&a, const T& b )
{
    T _b = ThNumericCast<T>(b);
    return (a>_b)?_b:a;
}

//--------------------------------------------------------------------------------
template<class T>
inline T ThClamp( const T& min, const T&max, const T& value )
{
    if( value > max )
    {
        return max;
    }

    if( value < min )
    {
        return min;
    }

    return value;
}

//--------------------------------------------------------------------------------
// extrat a byte from a number
#define BYTE( nIdxByte, nNumber )           (( 0xff<<((nIdxByte-1)*8) & (nNumber))>>((nIdxByte-1)*8))
#define CONCAT_BYTES( nByte1, nByte2)       ( ((nByte1)<<8) + (nByte2) )

#define LOW_SEMI_BYTE(nByte)                ( 0x0f & (nByte) )
#define HIGH_SEMI_BYTE(nByte)               ( (0xf0 & (nByte)) >> 4 )
#define CONCAT_SEMI_BYTES(nSB1, nSB2 )      ( (nSB1<<4) + (nSB2) )

//--------------------------------------------------------------------------------
inline void        Flags_AddProp        ( dword& flags, dword prop );
inline void        Flags_RemoveProp     ( dword& flags, dword prop );
inline Bool        Flags_HasProp        ( dword flags, dword prop );

//--------------------------------------------------------------------------------
inline  void        Flags_AddProp           ( dword& flags, dword prop );
inline  void        Flags_RemoveProp        ( dword& flags, dword prop );
inline  Bool        Flags_HasProp           ( dword flags, dword prop );
inline  Bool        fequals                 ( float f1, float f2, float fEps = 0.000001f );


//--------------------------------------------------------------------------------
inline void Flags_AddProp( dword& flags, dword prop )
{
    flags = flags | prop;
}


//--------------------------------------------------------------------------------
inline void Flags_RemoveProp( dword& flags, dword prop )
{
    flags = flags & ~prop;
}

//--------------------------------------------------------------------------------
inline Bool Flags_HasProp( dword flags, dword prop )
{
    return (flags & prop)==0?false:true;
}

//--------------------------------------------------------------------------------
inline Bool fequals ( float f1, float f2, float fEps )
{
    float dif = f1-f2;
    return (dif)>=-fEps && (dif)<=fEps;
}

//--------------------------------------------------------------------------------
template<typename Type_TO, typename Type_FROM>
THOT_FORCE_INLINE Type_TO ThNumericCast ( Type_FROM from )
{
    THOT_ASSERT(   ( (Type_FROM) ( (Type_TO)(from))) == from, "Numeric Cast failed");
    return (Type_TO) (from);
}

//--------------------------------------------------------------------------------
template <class T>
void ThZeroMemoryTmpl ( T& obj )
{
    memset( &obj, 0, sizeof(T) );
}

//--------------------------------------------------------------------------------


#endif