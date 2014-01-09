#pragma once
#ifndef __LIGHT_MANAGER_H__
#define __LIGHT_MANAGER_H__

#include "Render\Lights\LightBase.h"
#include "Kernel\ManagerInterface.h"
#include "Render\Lights\LightBase.h"

//TODO: remove this shit
#define MAX_LIGHTS 8

//template class RENDER_API CStaticArray<CLightBase*, MAX_LIGHTS>;
THOT_DECLARE_TEMPLATE_API(RENDER_TEMPLATE_API, CStaticArray<CLightBase*, MAX_LIGHTS>);


class RENDER_API CLightManager:public CUpdateManager
{
DECLARE_MANAGER_CLASS(CLightManager,CUpdateManager)
THOT_DECLARE_SINGLETON( CLightManager )

private:
            CLightManager();
virtual     ~CLightManager();
public:

virtual        void         Init                ( );
virtual        void         OnUpdate            ( float fDeltaTime );
virtual        Bool         AddLight            ( CLightBase* pLight );
virtual        void         ApplyLights         ( );

protected:
virtual        int          FindFreeLightSlot   ( );
virtual        void         ApplyLight          ( int nIdx );
virtual        void         ApplyDirectional    ( int nIdx );
virtual        void         ApplyPositional     ( int nIdx );
virtual        void         ApplySpotLight      ( int nIdx );

static const int s_nMaxLights = MAX_LIGHTS;



typedef CStaticArray<CLightBase*, s_nMaxLights>    tArrayLights;
    tArrayLights                m_aLights;

};

#undef MAX_LIGHTS

#endif /*__LIGHT_MANAGER_H__*/