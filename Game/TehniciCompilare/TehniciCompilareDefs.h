#pragma once
#ifndef __TEHNICI_COMPILARE_DEF_H__
#define __TEHNICI_COMPILARE_DEF_H__


//***********************************************
//********** DLL EXPORT/IMPORT*******************
//***********************************************

#if defined(THOT_PLATFORM_WINDOWS)
#if defined(TEHNICI_COMPILARE_EXPORTS)

#   define COMPILER_API             __declspec(dllexport)
#   define COMPILER_TEMPLATE_API    template class COMPILER_API

#else

#   define COMPILER_API __declspec(dllimport)
#   define COMPILER_TEMPLATE_API THOT_EXTERN_TEMPLATE class COMPILER_API

#endif //TEHNICI_COMPILARE_EXPORTS
#endif //THOT_PLATFORM_WINDOWS

#if !defined(COMPILER_API) || !defined(COMPILER_TEMPLATE_API)
#   error COMPILER_API and COMPILER_TEMPLATE_API must be defined
#endif



#endif //__TEHNICI_COMPILARE_DEF_H__
