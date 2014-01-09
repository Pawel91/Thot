#pragma once
#ifndef __KERNEL_EXTERNALS_H__
#define __KERNEL_EXTERNALS_H__

extern "C"
{

/**
    Externals
*/
void*       memcpy  ( void* pDest, const void* pSrc, size_t size);
void*       memset  ( void* pDest, int nVal, size_t nSize );
int         memcmp  ( const void * ptr1, const void * ptr2, size_t num );
size_t      strlen  ( const char* pString );
char*       strcpy  ( char * destination, const char * source );

/*Concatenate strings
Appends a copy of the source string to the destination string. 
The terminating null character in destination is overwritten by the first character of source, and a null-character is included at the end of the new string formed by the concatenation of both in destination*/
char*       strcat  ( char * destination, const char * source );

__declspec(dllimport) int atoi( const char* string );
}



#endif /*__KERNEL_EXTERNALS_H__*/