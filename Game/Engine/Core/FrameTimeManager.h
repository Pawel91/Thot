#pragma once
#ifndef __FRAME_TIME_MANAGER_H__
#define __FRAME_TIME_MANAGER_H__

#include "Kernel/Singleton.h"
#include "Kernel/Kernel.h"
#include "Core/CoreDef.h"


class CTimer;

/**
    Not a real manager;
*/
class CORE_API CFrameTimeManager: public CSingleton<CFrameTimeManager>
{

    //*********CONSTRUCTORS
public:
    CFrameTimeManager();
    ~CFrameTimeManager();


//************INTERFACE
public:

        Bool        Init                    ( );
        void        OnBeginFrame            ( );
        void        OnEndFrame              ( );
        float       GetGameTime             ( );




//************MEMBERS
protected:

    CTimer*         m_timer;
    float           m_currentGameTime;



};

#endif