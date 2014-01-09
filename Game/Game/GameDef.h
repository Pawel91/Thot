#ifndef __GAME_DEF_H__
#define __GAME_DEF_H__


#ifdef GAME_EXPORTS
#   define GAME_API __declspec(dllexport)
#   define GAME_TEMPLATE_API template class GAME_API


#else /* if !defined GAME_EXPORTS*/
#   define GAME_API __declspec(dllimport)

#   if defined(THOT_ENABLE_EXTERN_TEMPLATE)
#       define GAME_TEMPLATE_API extern template class GAME_API
#   else
#       define GAME_TEMPLATE_API template class GAME_API
#   endif



#endif /*GAME_EXPORTS*/



#endif /*__GAME_DEF_H__*/