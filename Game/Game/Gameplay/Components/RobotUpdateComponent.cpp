#include "Game_PCH.h"
#include "RobotUpdateComponent.h"
#include "Core/EntitySystem/Entity.h"
#include "Core/Terrain/Terrain.h"
#include "Core/Components/BindingComponent.h"
#include "Render/Utils/HeightMap.h"
#include "MathCore/Random.h"
#include "Kernel/Utils/Command.h"

class CGetNearestPointCommand: public ICommand
{
public:
    
    CGetNearestPointCommand( CRobotUpdateComponent* updateComponent, CHeightMap* heightMap )
        : m_heightMap (heightMap)
        , m_robotUpdateComponent( updateComponent)
    {
    }
            void SetPosition( const tVect3& position);
            const tVect3& GetTargetPoint()const;

    virtual void OnDone()override;
    virtual void InternalExecute( )override;

private:
    tVect3                  m_targetPoint;
    tVect3                  m_fromPoint;
    CHeightMap*             m_heightMap;
    CRobotUpdateComponent*  m_robotUpdateComponent;
};

//--------------------------------------------------------------------------------
const tVect3& CGetNearestPointCommand::GetTargetPoint()const
{
    return m_targetPoint;
}

//--------------------------------------------------------------------------------
void CGetNearestPointCommand::OnDone()
{
    m_robotUpdateComponent->OnEndGetNearestPoint();
}

//--------------------------------------------------------------------------------
void CGetNearestPointCommand::SetPosition( const tVect3& position)
{
    m_fromPoint = position;
}

//--------------------------------------------------------------------------------
void CGetNearestPointCommand::InternalExecute()
{
    m_heightMap->GetNearestVisPoint( m_fromPoint, m_targetPoint );
}


//--------------------------------------------------------------------------------
CRobotUpdateComponent::CRobotUpdateComponent()
    : m_terrainComponent                (NULL)
    , m_heightMap                       (NULL)
    , m_speed                           (0.f)
    , m_direction                       (nullVect)
    , m_timeFromLastDirectionChange     (0.f)
    , m_timeIntervalToChangeDirection   (0.f)
    , m_scout                           (true)
    , m_GetNearestPointCommand          (NULL)
    , m_canGoToShip                     (false)
    , m_totalTime                       (0.f)
    , m_currentTime                     (0.f)
{


    m_speed = Random::GetFloat( 5.f, 13.f);
    m_timeIntervalToChangeDirection = Random::GetFloat(2.f, 15.f);
    ChangeDir();
}

//--------------------------------------------------------------------------------
void CRobotUpdateComponent::ChangeDir()
{
    // set a random direction
    float angle = Random::GetFloat(0.f, 2*PI);
    m_direction.x = cos(angle);
    m_direction.z = sin(angle);

    THOT_ASSERT( fequals( VectLen(m_direction), 1.f, 0.001f ) );

    m_timeFromLastDirectionChange = 0.f;
}

//--------------------------------------------------------------------------------
CRobotUpdateComponent::~CRobotUpdateComponent()
{
    //CBindingComponent* bindingComponent = m_entity->GetComponent<CBindingComponent>();
    //THOT_ASSERT(bindingComponent);
}

//--------------------------------------------------------------------------------
void CRobotUpdateComponent::OnUpdateScout(float deltaTime)
{
    THOT_ASSERT(m_terrainComponent);
    THOT_ASSERT(m_heightMap);
    float terrainXSize = m_heightMap->GetTerrainXSize()-( float( m_heightMap->GetWidth()-1)/m_heightMap->GetProperties().m_width ) ;
    float terrainZSize = m_heightMap->GetTerrainZSize()-( float( m_heightMap->GetLenght()-1)/m_heightMap->GetProperties().m_lenght ) ;


    Bool shouldChangeDir = false;
    m_timeFromLastDirectionChange += deltaTime;
    if( m_timeFromLastDirectionChange > m_timeIntervalToChangeDirection )
    {
        shouldChangeDir = true;
    }

    CBindingComponent* bindingComponent = m_entity->GetComponent<CBindingComponent>();
    THOT_ASSERT(bindingComponent);

    m4x4 localMatrix = bindingComponent->GetLocalTM();
    tVect3 posOnHeightMap = POS(localMatrix);
    
    posOnHeightMap = posOnHeightMap + m_direction * m_speed * deltaTime;

    // terrain limits detection
    if( posOnHeightMap.x <0.f || posOnHeightMap.x >terrainXSize)
    {
        posOnHeightMap.x = ThClamp( 0.f, terrainXSize, posOnHeightMap.x );
        shouldChangeDir = true;
    }
    if(posOnHeightMap.z < 0.f || posOnHeightMap.z > terrainZSize )
    {
        posOnHeightMap.z = ThClamp( 0.f, terrainZSize, posOnHeightMap.z );
        shouldChangeDir = true;
    }

    if( shouldChangeDir )
    {
        ChangeDir();
    }

    posOnHeightMap.y = m_heightMap->GetHeight( posOnHeightMap.x, posOnHeightMap.z);
    POS(localMatrix) = posOnHeightMap;
    bindingComponent->SetLocalTM( localMatrix );

}

//--------------------------------------------------------------------------------
void CRobotUpdateComponent::ReturnToSpaceShip()
{
    THOT_ASSERT( m_GetNearestPointCommand );

    m4x4 robotMatrix = m_entity->GetComponent<CBindingComponent>()->GetLocalTM();
    m_lastScoutPoint = POS(robotMatrix);
    m_GetNearestPointCommand->SetPosition( m_lastScoutPoint );

    CHeightMapHelpers::GetInstance()->AddAsynchronousCommand( m_GetNearestPointCommand);
    m_scout = false;


}

//--------------------------------------------------------------------------------
void CRobotUpdateComponent::OnUpdate( float deltaTime)
{
    if( m_scout )
    {
        OnUpdateScout(deltaTime);
    }
    else
    {
        OnUpdateReturnToShip( deltaTime );
    }
}

//--------------------------------------------------------------------------------
void CRobotUpdateComponent::OnEndGetNearestPoint( )
{
    m_nearestPoint = m_GetNearestPointCommand->GetTargetPoint();
    m_returnDir = m_nearestPoint - m_lastScoutPoint;
    m_totalTime = VectLen(m_lastScoutPoint - m_nearestPoint)/m_speed;
    m_canGoToShip = true;
}

//--------------------------------------------------------------------------------
void CRobotUpdateComponent::OnUpdateReturnToShip(float deltaTime)
{
    if( !m_canGoToShip )
    {
        // wait until we get the target point
        return;
    }

    //float m_totalTime = VectLen(m_lastScoutPoint - m_nearestPoint)/m_speed;
    m_currentTime+= deltaTime;
    float ratio = m_currentTime/m_totalTime;
    ratio = ThClamp(0.f, 1.f, ratio);

    CBindingComponent* bindingComponent = m_entity->GetComponent<CBindingComponent>();
    THOT_ASSERT(bindingComponent);
    m4x4 localMatrix = bindingComponent->GetLocalTM();

    tVect3 position = (1.f-ratio) * m_lastScoutPoint + ratio * m_nearestPoint;
    

    tVect3 posOnHeightMap = position;
    posOnHeightMap.y = m_heightMap->GetHeight( position.x, position.z);
    POS(localMatrix) = posOnHeightMap;
    bindingComponent->SetLocalTM( localMatrix );
}

//--------------------------------------------------------------------------------
void CRobotUpdateComponent::OnBindToEntity()
{
    CBindingComponent* bindingComponent = m_entity->GetComponent<CBindingComponent>();
    THOT_ASSERT(bindingComponent);
    THOT_ASSERT( bindingComponent->GetParent() );
    m_terrainComponent = (CTerrainComponent*)bindingComponent->GetParent()->GetComponent<CRenderableComponent>();
    THOT_ASSERT( m_terrainComponent);
    m_heightMap =  m_terrainComponent->GetHeightMap();

    m_GetNearestPointCommand = THOT_NEW CGetNearestPointCommand( this, m_heightMap );
}