#pragma once
#ifndef __KERNEL_DEF_H__
#define __KERNEL_DEF_H__

//***********************************************
//********** DLL EXPORT/IMPORT*******************
//***********************************************
#ifdef KERNEL_EXPORTS

#   define KERNEL_API  __declspec(dllexport)
#   define KERNEL_TEMPLATE_API template class KERNEL_API

#else
#define KERNEL_API __declspec(dllimport)

#   if defined(THOT_ENABLE_EXTERN_TEMPLATE)
#   define KERNEL_TEMPLATE_API extern template class KERNEL_API
#   else
#   define KERNEL_TEMPLATE_API template class KERNEL_API
#   endif

#endif /*KERNEL_EXPORTS*/


//***********************************************
//***********************************************





#endif /*__KERNEL_DEF_H__*/