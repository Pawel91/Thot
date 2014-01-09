#pragma once
#ifndef __MANAGER_INTERFACE_H__
#define __MANAGER_INTERFACE_H__

#include "Kernel\RTTI.h"
#include "Kernel\DataTypes.h"

#define DECLARE_MANAGER_CLASS_ABSTRACT(_className,_baseName)            DECLARE_RTTI_ABSTRACT(_className,_baseName)
#define IMPLEMENT_MANAGER_CLASS_ABSTRACT(_className,_baseName)          IMPLEMENT_RTTI_ABSTRACT(_className,_baseName)

#define DECLARE_MANAGER_CLASS(_className,_baseName)                     DECLARE_RTTI(_className,_baseName)
#define IMPLEMENT_MANAGER_CLASS(_className,_baseName)                   IMPLEMENT_RTTI(_className,_baseName)

class CInput;

class KERNEL_API CUpdateManager
{
DECLARE_MANAGER_CLASS_ABSTRACT(CUpdateManager,CUpdateManager)

public:

                CUpdateManager(){}
virtual        ~CUpdateManager(){}

virtual        void        Init            ( )                              = 0;
virtual        void        OnUpdate        ( float fDeltaTime )             = 0;
};


class KERNEL_API CUpdateDrawManager:public CUpdateManager
{
DECLARE_MANAGER_CLASS_ABSTRACT(CUpdateDrawManager,CUpdateManager)

public:

            CUpdateDrawManager(){}
virtual     ~CUpdateDrawManager(){}

virtual        void        OnDraw            ( )const                       = 0;
};


//class CManagerInterface
class KERNEL_API CManagerInterface:public CUpdateDrawManager
{
//DECLARE_MANAGER_CLASS_ABSTRACT(CManagerInterface,CManagerInterface)    
DECLARE_MANAGER_CLASS_ABSTRACT(CManagerInterface,CUpdateDrawManager)    

public:
             CManagerInterface(){}
virtual     ~CManagerInterface(){}

virtual         void    Init                    ( )                             = 0;
virtual         void    OnUpdate                ( float fDeltaTime )            = 0;
virtual         void    OnClientCommand         ( const CInput& input )         = 0;
virtual         void    OnDraw                  ( )const{};
};


#endif /*__MANAGER_INTERFACE_H__*/