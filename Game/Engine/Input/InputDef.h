#pragma once
#ifndef __INPUT_DEF_H__
#define __INPUT_DEF_H__


#ifdef INPUT_EXPORTS

#   define INPUT_API __declspec(dllexport)
#   define INPUT_TEMPLATE_API template class INPUT_API


#else /* if !defined INPUT_EXPORTS*/

#   define INPUT_API __declspec(dllimport)

#   if defined(THOT_ENABLE_EXTERN_TEMPLATE)
#       define INPUT_TEMPLATE_API extern template class INPUT_API
#   else
#       define INPUT_TEMPLATE_API template class INPUT_API
#   endif


#endif /*INPUT_EXPORTS*/


#endif /*__INPUT_DEF_H__*/