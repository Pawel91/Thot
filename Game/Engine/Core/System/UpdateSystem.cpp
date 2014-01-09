#include "Core_PCH.h"
#include "UpdateSystem.h"

#include "Core/EntitySystem/Entity.h"
#include "Core/Components/UpdateComponent.h"
#include "Core/FrameTimeManager.h"

//--------------------------------------------------------------------------------
CUpdateSystem::CUpdateSystem()
{
}

//--------------------------------------------------------------------------------
CUpdateSystem::~CUpdateSystem()
{
}

//--------------------------------------------------------------------------------
void CUpdateSystem::OnInit()
{
}

//--------------------------------------------------------------------------------
void CUpdateSystem::Execute( )
{
    float deltaTime = CFrameTimeManager::GetInstance()->GetGameTime();

    for( u64 i=0; i<m_updatableEntities.Size(); i++)
    {
        CEntityHandle& handle = m_updatableEntities[i];
        CUpdateComponent* updateComponent = handle->GetComponent<CUpdateComponent>();
        THOT_ASSERT(updateComponent);
        updateComponent->OnUpdate( deltaTime );
    }
}

//--------------------------------------------------------------------------------
void CUpdateSystem::RegisterComponents()
{
    RegisterComponent<CUpdateComponent>();
}

//--------------------------------------------------------------------------------
void CUpdateSystem::OnEntityComponentChange(  const CEntityHandle& handle, IComponent* component, bool added)
{
    if( added)
    {
        m_updatableEntities.PushBack( handle );
    }
    else
    {
        //[TODO] remove this entity;
    }
}