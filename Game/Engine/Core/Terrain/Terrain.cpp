#include "Core_PCH.h"
#include "Terrain.h"

#include "Render/Utils/HeightMap.h"
#include "Kernel/Time/Timer.h"

#include "Render/Mesh/Mesh.h"
#include "Render/Buffers/Vertex.h"
#include "Core/EntitySystem/Entity.h"
#include "Input/Input.h"

//--------------------------------------------------------------------------------
CTerrainComponent::CTerrainComponent()
    : m_heightMap   (NULL)
{
}

//--------------------------------------------------------------------------------
CTerrainComponent::~CTerrainComponent()
{

}

//--------------------------------------------------------------------------------
Bool CTerrainComponent::OnInit( )
{
    if( !LoadHeightMap())
    {
        return false;
    }

    // everything went well
    return true;
}

//--------------------------------------------------------------------------------
Bool CTerrainComponent::LoadHeightMap( )
{
    CTimer heightmapLoadTimer;
    heightmapLoadTimer.Start();

    SHeightMapProperties properties;
    properties.m_maxHeight = 200.f; 
    properties.m_lenght = 600.f;
    properties.m_width = 600.f;

    m_heightMap = THOT_NEW CHeightMap;
    if( !m_heightMap->LoadFromTexture("Data\\textures\\HM2.bmp", properties) )
    {
        return false;
    }

    CTimer::TimeUnits deltaStart =  heightmapLoadTimer.Stop();
    THOT_TRACE_LINE( "HEIGHT MAP LOADED IN:[%d]miliseconds [%d] microseconds", CTimer::GetMiliseconds(deltaStart), CTimer::GetMicroseconds( deltaStart) );
   
    m_meshes.PushBack( m_heightMap->GetGeneratedMesh() );

    return true;
}

//--------------------------------------------------------------------------------
void CTerrainComponent::DebugUpdateVertices ()
{
    if(m_meshes.Size() )
    {
        m_heightMap->DebugUpdateVertices(m_meshes[0]);
        m_heightMap->SetDirty(false);
    }
}

//--------------------------------------------------------------------------------
void CTerrainUpdateComponent::OnUpdate ( float deltaTime)
{
    CTerrainComponent* terrainComponent = (CTerrainComponent*) m_entity->GetComponent<CRenderableComponent>();
    if(!terrainComponent)
    {
        return;
    }

    CInput& input =  *CInput::GetInstance();
    const CKeyInputInterface* keyboard = input.GetDeviceInputT<CKeyInputInterface>(InputDevices::E_INPUT_DEVICE_KEYBOARD);

    static u32 index = 0;
    static s32 col = 0;
    static s32 row = 0;

    if(keyboard->ButtonDown(InputKey::E_KEY_ARR_RIGHT))
    {
        col++;
    }

    if(keyboard->ButtonDown(InputKey::E_KEY_ARR_LEFT))
    {
        col--;
    }

    if(keyboard->ButtonDown(InputKey::E_KEY_ARR_UP))
    {
        row--;
    }

    if(keyboard->ButtonDown(InputKey::E_KEY_ARR_DOWN))
    {
        row++;
    }

    row = ThClamp( (s32)0, ThNumericCast<s32>(terrainComponent->m_heightMap->GetLenght()-1), row);
    col = ThClamp( (s32)0, ThNumericCast<s32>(terrainComponent->m_heightMap->GetWidth()-1), col);


    if(keyboard->ButtonDown(InputKey::E_KEY_V))
    {
        index++;
    }

    //index = 16134;
    index = row * terrainComponent->m_heightMap->GetLenght() + col;

    //if(keyboard->ButtonDown(InputKey::E_KEY_V))

    Bool makeVis = false;

    if(keyboard->ButtonDown(InputKey::E_KEY_V))
    {
        makeVis = true;
    }


    static Bool continous = false;
    if(keyboard->ButtonDown(InputKey::E_KEY_C))
    {
        continous = !continous;
    }

    if(continous)
    {
        makeVis = true;
    }


    if(makeVis)
    {
        CTimer visTestTimer;
        visTestTimer.Start();
        //terrainComponent->m_heightMap->MakeVisTest(tVect3(), index);
        terrainComponent->m_heightMap->MakeVisTest_Asynchronous(tVect3());
        CTimer::TimeUnits deltaStart = visTestTimer.Stop();
        
        //THOT_TRACE_LINE( "VIS TAKE MADE IN:[%d]miliseconds [%d] microseconds", CTimer::GetMiliseconds(deltaStart), CTimer::GetMicroseconds( deltaStart) );




    }

    //if( terrainComponent->m_heightMap->IsDirty() )
    if( terrainComponent->m_heightMap->VisTestsDone() )
    {
        terrainComponent->DebugUpdateVertices();
    }

}