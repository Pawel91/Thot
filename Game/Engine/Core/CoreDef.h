#pragma once
#ifndef __CORE_DEF_H__
#define __CORE_DEF_H__


#ifdef CORE_EXPORTS
#   define CORE_API     __declspec(dllexport)
#   define CORE_TEMPLATE_API    template class CORE_API

#else
#   define CORE_API     __declspec(dllimport)

#   if defined(THOT_ENABLE_EXTERN_TEMPLATE)
#       define CORE_TEMPLATE_API extern template class CORE_API
#   else
#       define CORE_TEMPLATE_API template class CORE_API
#   endif


#endif /*__CORE_DEF_H__*/



#endif /*__CORE_DEF_H__*/