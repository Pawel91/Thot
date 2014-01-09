#include "Core_PCH.h"
#include "SceneNode.h"

#include "Kernel\Time\Timer.h"

ISceneNode::ISceneNode( )
    : m_parent  ( NULL )
{
}
//------------------------------------------------------------------
ISceneNode::~ISceneNode(){}

//------------------------------------------------------------------
void ISceneNode::OnUpdate( float fDeltaTime )
{
    OnUpdateThis( fDeltaTime);
    UpdateChildren( fDeltaTime );
}

//------------------------------------------------------------------
void ISceneNode::UpdateChildren( float fDeltaTime )
{
    u32 childCont = this->GetChildCount();

    for( u32 i=0; i<childCont; i++ )
    {
        ISceneNode* child = this->GetChild( i );
        child->OnUpdate( fDeltaTime );
        child->m_transformComponent.UpdateWorldTM( this->GetWorldTM() );
    }
}


//------------------------------------------------------------------------------------
void ISceneNode::SetLocalTM( m4x4 TM)
{
    m_transformComponent.SetLocalTM( TM );
}

//------------------------------------------------------------------------------------
const m4x4& ISceneNode::GetLocalTM( )const
{
    return m_transformComponent.GetLocalTM();
}

//------------------------------------------------------------------------------------
const m4x4& ISceneNode::GetWorldTM () const
{
    return m_transformComponent.GetWorldTM();
}

//------------------------------------------------------------------------------------
u32 ISceneNode::GetChildCount( )const
{
    return ThNumericCast<u32>( m_children.Size() );
}

//------------------------------------------------------------------------------------
ISceneNode* ISceneNode::GetChild( u32 index )
{
    return m_children[index];
}

//------------------------------------------------------------------------------------
const ISceneNode* ISceneNode::GetChild( u32 index ) const
{
    return m_children[index];
}

//------------------------------------------------------------------------------------
ISceneNode* ISceneNode::GetParent( )
{
    return m_parent;
}

//------------------------------------------------------------------------------------
const ISceneNode*   ISceneNode::GetParent( )const
{
    return m_parent;
}

//------------------------------------------------------------------------------------
void ISceneNode::AppendChild( ISceneNode* sceneNode )
{
    m_children.PushBack( sceneNode );
}

//------------------------------------------------------------------------------------
void ISceneNode::SetParent( ISceneNode* parentNode )
{
    m_parent = parentNode;
}

//------------------------------------------------------------------------------------
const CString& ISceneNode::GetName( )const
{
    return m_name;
}

//------------------------------------------------------------------------------------
Bool ISceneNode::SetName( const CString& name )
{
    m_name = name;

    return true;
}