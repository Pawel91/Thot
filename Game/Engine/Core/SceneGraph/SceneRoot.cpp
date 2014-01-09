#include "Core_PCH.h"
#include "SceneRoot.h"

#include "Core/Cameras/SceneCamera.h"
#include "Core/SceneGraph/SceneRenderableNode.h"

//-------------------------------------------------------------------
void CSceneRoot::OnUpdateThis( float fDeltaTime )
{
    // the root does nothing;
}

//-------------------------------------------------------------------
void CSceneRoot::OnInit()
{
    AppendChild( THOT_NEW CSceneCameraBase() );
    AppendChild( THOT_NEW CSceneRenderableDemo() );

    // init all the children
    for( u64 i=0; i<m_children.Size(); i++ )
    {
        ISceneNode* child = m_children[i];
        child->OnInit();
    }
}