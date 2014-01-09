#include "Game_PCH.h"
#include "SpaceShipUpdateComponent.h"

#include "Kernel/FileSystem/Path.h"
#include "Core/EntitySystem/Entity.h"
#include "Core/EntitySystem/EntitySystem.h"
#include "Core/Components/BindingComponent.h"
#include "Core/Terrain/Terrain.h"
#include "Render/Utils/HeightMap.h"
#include "Render/ShaderFramework/ShaderManager.h"
#include "Input/Input.h"

#include "Core/SceneGraph/AssimpNode.h"
#include "Game/Gameplay/Components/RobotCameraComponent.h"
#include "Game/Gameplay/Components/RobotUpdateComponent.h"
#include "Kernel/Utils/Command.h"


class CSpawnRobotsCommand:public ICommand
{
public:
    CSpawnRobotsCommand( CSpaceShipUpdateComponent* updateComponent, const tVect3& position )
        : m_updateComponent ( updateComponent)
        , m_position(position)
    {}


    virtual void InternalExecute()override
    {
        m_updateComponent->SpawnRobots(m_position);
    }

private:
    tVect3                      m_position;
    CSpaceShipUpdateComponent*  m_updateComponent;
};


//--------------------------------------------------------------------------------
CSpaceShipUpdateComponent::CSpaceShipUpdateComponent()
    : m_bindingComponent            ( NULL )
    , m_speed                       ( 1.f )
    , m_landed                      ( false )
    , m_robotRenderableComponent    (NULL)
    , m_spawnCommand                (NULL)
{
    m_robotRenderableComponent = THOT_NEW CRenderableComponent;
    const char* filePath = "Data\\models\\SpaceShip\\SpaceShip.obj";
    const char* nodeName = "mesh01";

    THOT_ASSERT( CPath::FileExists(filePath), "file[%s] does not exists", filePath );
    DebugLoadRenderableComponent( m_robotRenderableComponent, filePath, nodeName );
}

//--------------------------------------------------------------------------------
CSpaceShipUpdateComponent::~CSpaceShipUpdateComponent()
{
}

//--------------------------------------------------------------------------------
void CSpaceShipUpdateComponent::VerifyLanding()
{
    if( m_landed )
    {
        return;
    }

    CTerrainComponent* terrainComponent = (CTerrainComponent*)m_bindingComponent->GetParent()->GetComponent<CRenderableComponent>();
    CHeightMap* heightMap = terrainComponent->GetHeightMap();

    m4x4 localMatrix = m_bindingComponent->GetLocalTM();
    tVect3 spaceShipPosition = POS(localMatrix);
    float currentHeight = spaceShipPosition.y;

    if( currentHeight < heightMap->GetHeight( spaceShipPosition.x, spaceShipPosition.z) )
    {
        spaceShipPosition.y = currentHeight;
        OnLanding();
        heightMap->MakeVisTest_Asynchronous( spaceShipPosition + yAxis*2.f );
    }
}

//--------------------------------------------------------------------------------
void CSpaceShipUpdateComponent::OnLanding()
{ 
    CTimer toLandTime;
    toLandTime.Start();

    m4x4 worldTM = m_bindingComponent->GetWorldTM(true);
    tVect3 worldPos = POS(worldTM);

    //for( u32 i=0; i< 20; i++ )
    //{
    //
    //    SpawnRobot( worldPos);
    //}
    m_spawnCommand = THOT_NEW CSpawnRobotsCommand( this, worldPos);
    CHeightMapHelpers::GetInstance()->AddAsynchronousCommand( m_spawnCommand );



    m_landed = true;

    CTimer::TimeUnits deltaStart =  toLandTime.Stop();
    THOT_TRACE_LINE( "TIME ON LANING = [%d]Milis; [%d]Micros", CTimer::GetMiliseconds(deltaStart), CTimer::GetMicroseconds(deltaStart) );
}

//--------------------------------------------------------------------------------
void CSpaceShipUpdateComponent::SpawnRobots( const tVect3& position )
{
    for( u32 i=0; i< 8; i++ )
    {

        SpawnRobot( position);
    }
}

//--------------------------------------------------------------------------------
void CSpaceShipUpdateComponent::SpawnRobot( const tVect3& position )
{
    CTimer spawnTimer;
    spawnTimer.Start();

    CEntityHandle robotEntity =  CEntitySystem::GetInstance()->CreateNewEntity();
    robotEntity->SetDebugName( "robot_spawned" );
    CRenderableComponent* renderableComponent = THOT_NEW CRenderableComponent;
    renderableComponent->SetShaderID( CShaderManager::GetInstance()->GetShaderID("spaceship"));
    robotEntity->InsertComponent( renderableComponent);
    CBindingComponent* bindingComponent = THOT_NEW CBindingComponent;
    robotEntity->InsertComponent( bindingComponent );

    m4x4 localMatrix = bindingComponent->GetLocalTM();
    POS(localMatrix) = position;
    bindingComponent->SetLocalTM(localMatrix);

    if( !robotEntity->AttachTo( m_bindingComponent->GetParent() )) //attach to terrain;
    {
        THOT_ASSERT(false);
    }

    CRobotUpdateComponent* robotUpdateComponent = THOT_NEW CRobotUpdateComponent;
    robotEntity->InsertComponent( robotUpdateComponent );
    m_robotUpdateComponents.PushBack( robotUpdateComponent );

    //robot camera
    CEntityHandle robotCameraEntity = CEntitySystem::GetInstance()->CreateNewEntity();
    robotCameraEntity->SetDebugName("robotCameraEntity");
    robotCameraEntity->InsertComponent( THOT_NEW CBindingComponent );
    robotCameraEntity->InsertComponent( THOT_NEW CRobotCameraComponent );
    robotCameraEntity->AttachTo( robotEntity );


    renderableComponent->CopyMeshes( m_robotRenderableComponent );
    

    CTimer::TimeUnits deltaStart =  spawnTimer.Stop();
    THOT_TRACE_LINE( "TIME TO SPAWN ROBOT = [%d]Milis; [%d]Micros", CTimer::GetMiliseconds(deltaStart), CTimer::GetMicroseconds(deltaStart) );

}

//--------------------------------------------------------------------------------
void CSpaceShipUpdateComponent::BringRobotsHome()
{

}

//--------------------------------------------------------------------------------
void CSpaceShipUpdateComponent::OnUpdate( float deltaTime)
{
    m_bindingComponent = NULL;
    if( (m_bindingComponent = m_entity->GetComponent<CBindingComponent>()) == NULL )
    {
        // binding component not found; cannot update position and other stuff
        return;
    }

    if( !m_landed )
    {
        PrivateUpdate( deltaTime );
    }
    VerifyLanding();

    if( m_landed )
    {
        CInput& input =  *CInput::GetInstance();
        const CKeyInputInterface* keyboard = input.GetDeviceInputT<CKeyInputInterface>(InputDevices::E_INPUT_DEVICE_KEYBOARD);
        if( keyboard->ButtonPress(InputKey::E_KEY_SPACE) )
        {
            for( u64 i=0; i<m_robotUpdateComponents.Size(); i++ )
            {
                if(m_robotUpdateComponents[i]->IsScouting())
                {
                    m_robotUpdateComponents[i]->ReturnToSpaceShip();
                    //THOT_TRACE_LINE("RETURNING ROBOT:[%p]", m_robotUpdateComponents[i]);
                }
            }
        }
    }

}

//--------------------------------------------------------------------------------
void CSpaceShipUpdateComponent::PrivateUpdate( float deltaTime)
{
    CTerrainComponent* terrain = (CTerrainComponent*) m_bindingComponent->GetParent()->GetComponent<CRenderableComponent>();
    CHeightMap* heightMap = terrain->GetHeightMap();

    CInput& input =  *CInput::GetInstance();
    const CMouseInputInterface* pMouse = input.GetDeviceInputT<CMouseInputInterface>(InputDevices::E_INPUT_DEVICE_MOUSE);
    const CKeyInputInterface* pKeyboard = input.GetDeviceInputT<CKeyInputInterface>(InputDevices::E_INPUT_DEVICE_KEYBOARD);

    Bool WIsPress = pKeyboard->ButtonPress( InputKey::E_KEY_W);
    Bool AIsPress = pKeyboard->ButtonPress( InputKey::E_KEY_A);
    Bool SIsPress = pKeyboard->ButtonPress( InputKey::E_KEY_S);
    Bool DIsPress = pKeyboard->ButtonPress( InputKey::E_KEY_D);

    int mouseWheelDelta = pMouse->GetMouseWheelDelta();
    if( mouseWheelDelta > 0 )
    {
        m_speed *= 1.2f;
    }
    else if( mouseWheelDelta < 0 )
    {
        m_speed *= 0.8f;
    }


    m4x4 spaceShipRotMatrix = m_bindingComponent->GetLocalTM();
    tVect3 originalPos = POS( spaceShipRotMatrix);
    POS(spaceShipRotMatrix) = nullVect;

    const float XAxisRotSpeed = 60.f;
    float XAxisRot = 0.f;
    if( WIsPress )
    {
        XAxisRot = XAxisRotSpeed * deltaTime * -1.f;
    }
    else if(SIsPress)
    {
        XAxisRot = XAxisRotSpeed * deltaTime * 1.f;
    }

    m4x4 XAxisRotMat = i4x4;
    MakeAnyRotMat( AXEX(spaceShipRotMatrix), XAxisRot, XAxisRotMat );
    spaceShipRotMatrix = spaceShipRotMatrix * XAxisRotMat;
    
    const float zAxisRotSpeed = 90.f;
    float ZAxisRot = 0.f;
    if(AIsPress)
    {
        ZAxisRot = zAxisRotSpeed * deltaTime * -1.f;
    }
    else if(DIsPress)
    {
        ZAxisRot = zAxisRotSpeed * deltaTime * 1.f;
    }

    m4x4 ZAxisRotMat = i4x4;
    MakeAnyRotMat(AXEZ( spaceShipRotMatrix), ZAxisRot, ZAxisRotMat );
    spaceShipRotMatrix = spaceShipRotMatrix * ZAxisRotMat;

    m4x4 spaceShipMatrix = spaceShipRotMatrix;
    POS(spaceShipMatrix) = originalPos + AXEZ(spaceShipRotMatrix) * m_speed * deltaTime;
    tVect3 spaceShipPos = POS(spaceShipMatrix);
    spaceShipPos.x = ThClamp( 0.f, heightMap->GetTerrainXSize()-3.f, spaceShipPos.x );
    spaceShipPos.z = ThClamp( 0.f, heightMap->GetTerrainZSize()-3.f, spaceShipPos.z );

    POS(spaceShipMatrix) = spaceShipPos;

    m_bindingComponent->SetLocalTM(spaceShipMatrix);
}

//--------------------------------------------------------------------------------