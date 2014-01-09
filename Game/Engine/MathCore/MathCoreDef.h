#ifndef __MATH_CORE_DEF_H__
#define __MATH_CORE_DEF_H__


#ifdef MATHCORE_EXPORTS

#   define MATHCORE_API __declspec(dllexport)
#   define MATHCORE_TEMPLATE_API template class MATHCORE_API


#else /* if defined MATHCORE_EXPORTS*/

#   define MATHCORE_API __declspec(dllimport)

#   if defined(THOT_ENABLE_EXTERN_TEMPLATE)
#       define MATHCORE_TEMPLATE_API extern template class MATHCORE_API
#   else
#       define MATHCORE_TEMPLATE_API template class MATHCORE_API
#   endif



#endif /*MATHCORE_EXPORTS*/




#endif /*__MATH_CORE_DEF_H__*/