#include "Game_PCH.h"
#include "Mod_GameManager.h"

#include "Kernel/Utils/StringUtils.h"
#include "Kernel/DataStructures/Array/Vector.h"
#include "Kernel/FileSystem/Path.h"
#include "Kernel/Time/Timer.h"
#include "Kernel/FileSystem/FileSystem.h"
#include "Kernel/MemoryManagement/FrameAllocator.h"
#include "Kernel/DataStructures/FixedString.h"

#include "Render/ShaderFramework/ShaderManager.h"

#include "Core/EntitySystem/EntitySystem.h"
#include "Core/Components/RenderableComponent.h"
#include "Core/Components/AnimationComponent.h"
#include "Core/Components/BindingComponent.h"
#include "Core/Components/UpdateComponent.h"
#include "Core/Terrain/Terrain.h"
#include "Core/System/RenderSystem.h"
#include "Core/System/CameraSystem.h"
#include "Core/System/UpdateSystem.h"
#include "Core/Cameras/FreeCameraComponent.h"
#include "Core/Components/LightComponent.h"

#include "Game/Gameplay/Components/SpaceShipUpdateComponent.h"
#include "Game/Gameplay/Components/SpaceShipCameraComponent.h"
#include "Game/Gameplay/Components/RobotUpdateComponent.h"

#include <vector>
#include "Kernel/Profiler/Profiler.h"
#include "Kernel/MemoryManagement/MemoryUtils.h"

#include "Core/SceneGraph/AssimpNode.h"

#include "Kernel/DebugSystem/StackWalker.h"


#define MY_TEST_XML //REMOVE ME
#if defined(MY_TEST_XML)
#   include "Kernel/XML/XmlDocument.h"
#   include "Kernel/XML/DOMBuilder.h"
#   include "Kernel/MemoryManagement/FreePool.h"
#   include "Kernel/MemoryManagement/Bucket.h"

#if defined(GetClassName)
#   undef GetClassName
#endif

#endif 

#if defined(CreateFile)
#   undef CreateFile
#endif

//#define TEST_LOAD_MESH
//
//#if defined TEST_LOAD_MESH
//THOT_TODO("REMOVE ASSIMP INCLUDES FROM HERE AND PUT LOADING MESH SOMEWHERE ELSE");
//#include "assimp/types.h"
//#include "assimp/scene.h"
//#include "assimp/Importer.hpp"
//#include "assimp/postprocess.h"
//#include "assimp/cimport.h"
//
//#include "Core/SceneGraph/SceneRenderableNode.h"
//#include "Core/SceneGraph/SceneGraph.h"
//#include "Core/SceneGraph/SceneAssimpConverter.h"
//#include "Core/SceneGraph/AssimpNode.h"
//
//void DebugLoadRenderableComponent( CRenderableComponent* component, const char* filePath, const char* nodeName )
//{
//    CSceneGraph*            m_sceneGraph = NULL;
//    Assimp::Importer*       m_importer = NULL;
//
//    std::string extensionList;
//    m_importer = THOT_NEW Assimp::Importer;
//    m_importer->GetExtensionList(extensionList);
//    THOT_TRACE_LINE("Extensions:[%s]", extensionList.c_str());
//
//    //const char* modelName = "Data\\models\\golem_clean.dae";
//    const aiScene* scene = m_importer->ReadFile( filePath, aiProcessPreset_TargetRealtime_MaxQuality  );
//
//    if( !scene )
//    {
//        THOT_TRACE_LINE( "%s", m_importer->GetErrorString() );
//        THOT_ASSERT(0);
//    }
//
//    CSceneAssimpConverter* sceneConverter = THOT_NEW CSceneAssimpConverter(scene);
//    m_sceneGraph = sceneConverter->CreateScene( );
//
//    //CAssimpSceneNode* assimpNode = m_sceneGraph->GetNodeByName( m_sceneGraph->GetRoot(), nodeName );
//    //THOT_ASSERT(assimpNode, "FAILED TO LOAD NODE[%s]", nodeName);
//    //for(u64 i=0; i<assimpNode->m_meshes.GetSize();i++)
//    //{
//    //    component->InsertMesh( assimpNode->m_meshes[i]);
//    //}
//
//    thVector<IMesh*> meshes;
//    m_sceneGraph->GetRenderableNodes(m_sceneGraph->GetRoot(), meshes);
//    THOT_ASSERT(meshes.GetSize()>0);
//    
//    for( u64 i=0; i<meshes.GetSize(); i++)
//    {
//        component->InsertMesh(meshes[i]);
//    }
//
//
//
//    if( scene->HasTextures() )
//    {
//        THOT_TRACE_LINE("SCENE HAS TEXTURES");
//    }
//
//    if( scene->HasMaterials() )
//    {
//        THOT_TRACE_LINE( "NUMBER OF MATERIALS:[%d]", scene->mNumMaterials );
//    }
//    
//    if( scene->HasMeshes() )
//    {
//       
//        THOT_TRACE_LINE( "NUMBER OF MESHES:[%d]",scene->mNumMeshes );
//    }
//    else
//    {
//        THOT_ASSERT(0, "nothing to render? wtf?");
//    }
//}
//
//#endif //

//--------------------------------------------------------------------------------
CGameManager::~CGameManager()
{
    Destroy();
}

//--------------------------------------------------------------------
void CGameManager::Init ( )
{
#if defined(MY_TEST_XML)
    SYSTEM_INFO siSysInfo;
    GetSystemInfo(&siSysInfo); 
    THOT_TRACE("Hardware information: \n");  
    THOT_TRACE("    OEM ID:                         %u\n", siSysInfo.dwOemId);
    THOT_TRACE("    Number of processors:           %u\n", siSysInfo.dwNumberOfProcessors); 
    THOT_TRACE("    Page size:                      %u\n", siSysInfo.dwPageSize); 
    THOT_TRACE("    Processor type:                 %u\n", siSysInfo.dwProcessorType); 
    THOT_TRACE("    Minimum application address:    %lx\n",siSysInfo.lpMinimumApplicationAddress); 
    THOT_TRACE("    Maximum application address:    %lx\n", siSysInfo.lpMaximumApplicationAddress); 
    THOT_TRACE("    Active processor mask:          %u\n", siSysInfo.dwActiveProcessorMask); 

    CFreePool freePool( 8, 3);
    void* p1 = freePool.Alloc();
    void* p2 = freePool.Alloc();
    void* p3 = freePool.Alloc();
    freePool.Free( p2 );

    CXMLDocument xmlDocument;
    CString currentPath;

    FileSystem::FileHandle file = FileSystem::CreateFile( EFileType::E_FILE_TYPE_MEMORY );
    file->Open( "Data/testXML.abc", EAccesMode::E_ACCES_MODE_READ );
    
    u64 fileSize = file->GetSize();
    char* fileContent = THOT_MALLOCT<char>(fileSize);
    Memory::Set( fileContent, fileSize, 0);
    if( !file->Read( fileContent, fileSize, 1 ) )
    {
        THOT_ASSERT( false );
    }
    THOT_TRACE_LINE("-----------------------------------------------------");
    THOT_TRACE_LINE("%s", fileContent);
    THOT_TRACE_LINE("-----------------------------------------------------");
    
    CDOMBuilder domBuilder;
    domBuilder.Parse( fileContent, fileSize );
    
    //xmlDocument.SetText( fileContent, fileSize );
    //xmlDocument.Parse();

    THOT_TRACE_LINE("==== AND AFTER===");
    THOT_TRACE_LINE("-----------------------------------------------------");
    THOT_TRACE_LINE("%s", fileContent);
    THOT_TRACE_LINE("-----------------------------------------------------");
#endif //MY_TEST_XML



    THOT_ASSERT(CEntitySystem::GetInstance() == NULL, "HERE IS THE BEST PLACE TO INIT THE ENTITY SYSTEM");

    CEntitySystem::CreateInstance();

    // register components
    CEntitySystem::GetInstance()->RegisterComponent<CRenderableComponent>();
    CEntitySystem::GetInstance()->RegisterComponent<CAnimationComponent>();
    CEntitySystem::GetInstance()->RegisterComponent<CBindingComponent>();
    CEntitySystem::GetInstance()->RegisterComponent<CCameraComponentBase>();
    CEntitySystem::GetInstance()->RegisterComponent<CLightComponent>();
    CEntitySystem::GetInstance()->RegisterComponent<CUpdateComponent>();

    //register systems
    CEntitySystem::GetInstance()->RegisterSystem<CRenderSystem>( );
    CEntitySystem::GetInstance()->RegisterSystem<CCameraSystem>( );
    CEntitySystem::GetInstance()->RegisterSystem<CUpdateSystem>( );

    // init the entitySystem
    const u16 maxEntityCount = 1024;
    CEntitySystem::GetInstance()->OnInit( maxEntityCount );


    CRenderableComponent* robotRenderable = THOT_NEW CRenderableComponent;
    CRenderableComponent* renderableComponent = THOT_NEW CRenderableComponent;
    
    renderableComponent->SetShaderID( CShaderManager::GetInstance()->GetShaderID("spaceship") );
    robotRenderable->SetShaderID( CShaderManager::GetInstance()->GetShaderID("spaceship") );
#if defined(TEST_LOAD_MESH)
    //const char* filePath = "Data\\models\\golem_clean.dae";
    //const char* nodeName = "golem";

    //const char* nodeName = "Cube_Cube_Base";
    //const char* filePath = "Data\\models\\SpaceShip\\SpaceShip.obj";
    //const char* filePath = "Data\\models\\scout\\scoutpatrol\\scout patrol.obj";
    
    const char* filePath = "Data\\models\\SpaceShip\\SpaceShip.obj";
    const char* nodeName = "mesh01";

    THOT_ASSERT( CPath::FileExists(filePath), "file[%s] does not exists", filePath );
    DebugLoadRenderableComponent( renderableComponent, filePath, nodeName );
    robotRenderable->CopyMeshes( renderableComponent );
#endif

    //space ship
    CEntityHandle spaceShipEntity = CEntitySystem::GetInstance()->CreateNewEntity();
    spaceShipEntity->SetDebugName("spaceShipEntity");
    spaceShipEntity->InsertComponent(renderableComponent);
    spaceShipEntity->InsertComponent( THOT_NEW CBindingComponent);
    spaceShipEntity->InsertComponent( THOT_NEW CSpaceShipUpdateComponent );
    CBindingComponent* bindingComp = spaceShipEntity->GetComponent<CBindingComponent>();
    THOT_ASSERT(bindingComp);
    m4x4 spaceLocalMatrix =  i4x4;
    //POS(spaceLocalMatrix) = tVect3( 25, 250.f, 25.f );
    POS(spaceLocalMatrix) = tVect3( 0, 80.f, 0.f );
    bindingComp->SetLocalTM( spaceLocalMatrix);


    //spaceShipEntity->InsertComponent( THOT_NEW CSpaceShipCameraComponent );

    //    // robot
    //CEntityHandle robotEntity = CEntitySystem::GetInstance()->CreateNewEntity();
    //robotEntity->SetDebugName("robotEntity");
    //robotEntity->InsertComponent( robotRenderable );
    //robotEntity->InsertComponent( THOT_NEW CBindingComponent);


    //===== TEST RENDERABLE COMPONENT
    CEntityHandle terrainEntity = CEntitySystem::GetInstance()->CreateNewEntity();
    terrainEntity->SetDebugName("terrainEntity");

    CTerrainComponent* terrain = THOT_NEW CTerrainComponent;
    terrain->OnInit();
    terrain->SetShaderID( CShaderManager::GetInstance()->GetShaderID( "terrain" ) );
    terrainEntity->InsertComponent( terrain );
    terrainEntity->InsertComponent( THOT_NEW CTerrainUpdateComponent );
    //terrainEntity->InsertComponent( renderableComponent );
    terrainEntity->InsertComponent( THOT_NEW CBindingComponent );


    spaceShipEntity->AttachTo(terrainEntity);
    //robotEntity->AttachTo(terrainEntity);
    //robotEntity->InsertComponent( THOT_NEW CRobotUpdateComponent);

    // Space Ship Camera
    CEntityHandle spaceShipCameraEntity = CEntitySystem::GetInstance()->CreateNewEntity();
    spaceShipCameraEntity->SetDebugName("spaceShipCameraEntity");
    //freeCameraEntity->InsertComponent( THOT_NEW CFreeCameraComponent );
    spaceShipCameraEntity->InsertComponent( THOT_NEW CSpaceShipCameraComponent );
    spaceShipCameraEntity->InsertComponent( THOT_NEW CBindingComponent );
    spaceShipCameraEntity->AttachTo( spaceShipEntity );

    // free camera
    CEntityHandle freeCameraEntity = CEntitySystem::GetInstance()->CreateNewEntity();
    freeCameraEntity->SetDebugName("freeCameraEntity");
    freeCameraEntity->InsertComponent( THOT_NEW CFreeCameraComponent);
    freeCameraEntity->InsertComponent( THOT_NEW CBindingComponent);


    // TEST SOME LIGHTS
    CEntityHandle lightEntity = CEntitySystem::GetInstance()->CreateNewEntity();
    s32 refCount = CEntitySystem::GetInstance()->GetRefCount(lightEntity->GetID());
    lightEntity->SetDebugName("lightEntity");
    CLightComponent* lightComponent = THOT_NEW CLightComponent;
    lightEntity->InsertComponent( lightComponent );
    lightEntity->InsertComponent( THOT_NEW CBindingComponent );
    lightComponent->SetType( ELightType_Directional );
    lightComponent->SetAmbient( CColor( 0.13f, 0.13f, 0.13f, 1.f ) );
    lightComponent->SetDiffuse( CColor( 1.f, 1.f, 1.f, 1.f ) );
    lightComponent->SetSpecular( CColor( 0.5f, 0.5f, 0.5f, 1.f ) );
    lightComponent->SetDirectionToLight( -Unit( tVect3( -0.852f, 0.350f, -0.389f )) );
    //lightComponent->SetDirection( zAxis );

    //lightEntity->AttachTo( freeCameraEntity );
}

//--------------------------------------------------------------------
void CGameManager::Destroy ( )
{
    CEntitySystem::DestroyInstance();
}

//--------------------------------------------------------------------------------
void CGameManager::OnBeginFrame( )
{
    CFrameAllocator::GetInstance()->OnNewFrame();
}

//--------------------------------------------------------------------------------
void CGameManager::OnEndFrame( )
{

}

//--------------------------------------------------------------------
void CGameManager::OnUpdate ( float fDeltaTime )
{
    THOT_ASSERT( CEntitySystem::GetInstance(), "ERROR!! ENTITY SYSTEM IS NOT CREATED!" );

    CUpdateSystem* updateSystem = CEntitySystem::GetInstance()->GetSystem<CUpdateSystem>();
    THOT_ASSERT( updateSystem, "UPDATE SYSTEM IS NOT AVAILABLE");
    if( updateSystem )
    {
        updateSystem->Execute();
    }

    // Execute Camera system
    CCameraSystem* cameraSystem =  CEntitySystem::GetInstance()->GetSystem<CCameraSystem>();
    THOT_ASSERT(cameraSystem, "CAMERA SYSTEM IS NOT AVAILABLE");
    if( cameraSystem )
    {
        cameraSystem->Execute();
    }

    // Execute Render System
    CRenderSystem* renderSystem = CEntitySystem::GetInstance()->GetSystem<CRenderSystem>();
    THOT_ASSERT( renderSystem, "RENDER SYSTEM IS NOT AVAILABLE");
    if( renderSystem )
    {
        renderSystem->Execute( );
    }
}


