#ifndef __RENDER_DEF_H__
#define __RENDER_DEF_H__


#ifdef RENDER_EXPORTS

#   define RENDER_API __declspec(dllexport)
#   define RENDER_TEMPLATE_API template class RENDER_API

#else /* if !define RENDER_EXPORTS*/

#   define RENDER_API __declspec(dllimport)

#   if defined(THOT_ENABLE_EXTERN_TEMPLATE)
#       define RENDER_TEMPLATE_API extern template class RENDER_API
#   else
#       define RENDER_TEMPLATE_API template class RENDER_API
#endif /*defined(THOT_ENABLE_EXTERN_TEMPLATE)*/

#endif /*RENDER_EXPORTS*/


#endif /*__RENDER_DEF_H__*/