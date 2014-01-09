#if !defined(__GAME_SPACE_SHIP_UPDATE_COMPONENT_H__)
#define __GAME_SPACE_SHIP_UPDATE_COMPONENT_H__

#include "Kernel/DataStructures/Array/Vector.h"
#include "Core/Components/UpdateComponent.h"

class CRobotUpdateComponent;

class CSpaceShipUpdateComponent: public CUpdateComponent
{

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
     CSpaceShipUpdateComponent();
    ~CSpaceShipUpdateComponent();


//*********************************************
//            INTERFACE
//*********************************************
public:
    virtual     void        OnUpdate ( float deltaTime);
                Bool        Landed(){ return m_landed;}
                void        BringRobotsHome();
                void        SpawnRobots( const tVect3& position );
                void        SpawnRobot( const tVect3& position );

protected:
                void        PrivateUpdate( float deltaTime);

                void        OnLanding();
                void        VerifyLanding();
                


//*********************************************
//            MEMBERS
//*********************************************
protected:
    thVector<CRobotUpdateComponent*>    m_robotUpdateComponents;
    Bool                                m_landed;
    float                               m_speed;
    class CBindingComponent*            m_bindingComponent;
    class CRenderableComponent*         m_robotRenderableComponent;
    class CSpawnRobotsCommand*          m_spawnCommand;
};


#endif //__GAME_SPACE_SHIP_UPDATE_COMPONENT_H__