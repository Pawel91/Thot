#pragma once
#ifndef __PLANETS_CAMERA_H_
#define __PLANETS_CAMERA_H_

#include "MOD_FreeCamera.h"

class cMod_ActorTemaGeometrie;

class cMod_PlanetsCamera:public cMod_FreeCamera
{
DECLARE_RTTI(cMod_PlanetsCamera,cMod_FreeCamera);
public:
         cMod_PlanetsCamera();
virtual    ~cMod_PlanetsCamera();


virtual        void            OnClientCommand    ( const CInput& input )        override;
virtual        void            GetTM            ( m4x4& out )const            override;

virtual        void            AttachedToPlanet( int nIdx );

protected:

    cMod_ActorTemaGeometrie*    m_pPlanetsManager;
    int                            m_nParentPlanet;

    
};

#endif __PLANETS_CAMERA_H_