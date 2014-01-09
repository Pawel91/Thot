#include "Core_PCH.h"
#include "RenderableComponent.h"

#include "Render/ShaderFramework/ShaderManager.h"

//----------------------------------------------------------
CRenderableComponent::CRenderableComponent()
    : m_shader   (NULL)
    , m_shaderID (INVALID_SHADERID)
{

}

//----------------------------------------------------------
CRenderableComponent::~CRenderableComponent()
{

}

//----------------------------------------------------------
void CRenderableComponent::InsertMesh( IMesh* mesh)
{
    m_meshes.PushBack(mesh);
}

//--------------------------------------------------------------------------------
void CRenderableComponent::SetShaderID( ShaderID shaderID)
{
    if( shaderID == INVALID_SHADERID )
    {
        return;
    }

    m_shaderID = shaderID;

    THOT_ASSERT( CShaderManager::GetInstance() );
    CShaderManager* shaderManager =  CShaderManager::GetInstance();
    m_shader = shaderManager->GetShaderFromID( shaderID );
    THOT_ASSERT(m_shader);
}

//--------------------------------------------------------------------------------
const CShader* CRenderableComponent::GetShader()const
{
    return m_shader;
}

//--------------------------------------------------------------------------------
Bool CRenderableComponent::CopyMeshes( const CRenderableComponent* other )
{
    for( u64 i=0; i<other->m_meshes.Size(); i++ )
    {
        m_meshes.PushBack( other->m_meshes[i]);
    }

    return true;
}