#pragma once
#ifndef __MOD_GAME_MANAGER_H__
#define __MOD_GAME_MANAGER_H__

#include "Kernel/Singleton.h"
#include "Kernel/Kernel.h"


class CSceneGraph;

class CGameManager: public CSingleton<CGameManager>
{
    template<class T> friend class CSingleton;
//*********CONSTRUCTORS
protected:
      CGameManager(){}
     ~CGameManager();

//*********INTERFACE
public:
        void            Init                ( );
        void            Destroy             ( );
        void            OnBeginFrame        ( );
        void            OnEndFrame          ( );
        void            OnUpdate            ( float fDeltaTime ) ;



//***********MEMBERS
protected:

};





#endif /*__MOD_GAME_MANAGER_H__*/