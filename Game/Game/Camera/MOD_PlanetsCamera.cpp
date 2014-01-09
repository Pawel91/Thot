#include "MOD_PlanetsCamera.h"
#include "Game\Actors\MOD_ActorTemaGeometrie.h"
#include "Game\Managers\MOD_ActorManager.h"


IMPLEMENT_RTTI(cMod_PlanetsCamera,cMod_FreeCamera);

cMod_PlanetsCamera:: cMod_PlanetsCamera()
:m_pPlanetsManager      ( NULL )
,m_nParentPlanet        ( -1 )
{
    CMod_ActorManager* pActorManager  =CMod_ActorManager::s_GetInstance();
    const tActorList& actorList = pActorManager->GetActorList();
    
    u64 nSize = actorList.GetSize();
    for( int i=0; i<nSize; i++ )
    {
        if( actorList[i]->IsA( cMod_ActorTemaGeometrie::s_GetClassReplicator() ) )
        {
            // hack
            m_pPlanetsManager = (cMod_ActorTemaGeometrie*)actorList[i];
        }
    }


}

cMod_PlanetsCamera::~cMod_PlanetsCamera()
{

}

void cMod_PlanetsCamera::OnClientCommand    ( const CInput& input )
{
    const CKeyInputInterface* pKeyboard = input.GetDeviceInputT<CKeyInputInterface>(InputDevices::E_INPUT_DEVICE_KEYBOARD);

    if( pKeyboard->ButtonDown( InputKey::E_KEY_1 ) )
    {
        m_nParentPlanet = 1;
    }

    if( pKeyboard->ButtonDown( InputKey::E_KEY_2 ) )
    {
        m_nParentPlanet = 2;
    }

    if( pKeyboard->ButtonDown( InputKey::E_KEY_3 ) )
    {
        m_nParentPlanet = 3;
    }


    if( pKeyboard->ButtonDown( InputKey::E_KEY_4 ) )
    {
        m_nParentPlanet = 4;
    }


}

void cMod_PlanetsCamera::AttachedToPlanet( int nIdx )
{
    if( !m_pPlanetsManager)
        return;

}

void cMod_PlanetsCamera::GetTM ( m4x4& out )const
{

    m4x4 mLocalTM;  super::GetTM( mLocalTM);
    m4x4 mPlanetTM = i4x4;
    if( m_pPlanetsManager && m_nParentPlanet > 0 && (u32)m_nParentPlanet < m_pPlanetsManager->GetPlanets().GetSize() )
    {
        m_pPlanetsManager->GetPlanets()[m_nParentPlanet]->GetTM( mPlanetTM);
    }

    out =  mLocalTM * mPlanetTM;
}

