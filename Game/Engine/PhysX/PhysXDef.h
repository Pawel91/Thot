#pragma once
#ifndef __PHYSX_DEF_H__
#define __PHYSX_DEF_H__


#ifdef PHYSX_EXPORTS
#   define PHYSX_API        __declspec(dllexport)
#else
#   define PHYSX_API        __declspec(dllimport)
#endif /*__PHYSX_DEF_H__*/



#endif /*__PHYSX_DEF_H__*/