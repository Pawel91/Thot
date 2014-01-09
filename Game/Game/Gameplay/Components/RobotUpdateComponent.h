#if !defined(__REBOT_UPDATE_COMPONENT_H__)
#define __REBOT_UPDATE_COMPONENT_H__

#include "Core/Components/UpdateComponent.h"

class CTerrainComponent;
class CHeightMap;
class CRobotUpdateComponent: public CUpdateComponent
{

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
     CRobotUpdateComponent();
    ~CRobotUpdateComponent();


//*********************************************
//            INTERFACE
//*********************************************
public:
    virtual     void        OnUpdate( float deltaTime)override;
    virtual     void        OnBindToEntity()override;
                void        ReturnToSpaceShip();
                void        OnEndGetNearestPoint();
                Bool        IsScouting(){ return m_scout;}
                Bool        IsReturning(){ return !m_scout;}
protected:
                void        OnUpdateScout(float deltaTime);
                void        OnUpdateReturnToShip(float deltaTime);
                void        ChangeDir();

//*********************************************
//            MEMBERS
//*********************************************
protected:
    float                               m_totalTime;
    float                               m_currentTime;
    tVect3                              m_returnDir;
    tVect3                              m_nearestPoint;
    tVect3                              m_lastScoutPoint;
    Bool                                m_canGoToShip;

    class CGetNearestPointCommand*      m_GetNearestPointCommand;
    Bool                                m_scout;
    CTerrainComponent*                  m_terrainComponent;
    CHeightMap*                         m_heightMap;
    float                               m_speed;
    tVect3                              m_direction;
    float                               m_timeFromLastDirectionChange;
    float                               m_timeIntervalToChangeDirection;

};

#endif//__REBOT_UPDATE_COMPONENT_H__