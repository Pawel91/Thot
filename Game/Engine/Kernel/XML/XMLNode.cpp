#include "Kernel_PCH.h"

#include "Kernel/XML/XMLNode.h"
#include "Kernel/XML/XmlAttribute.h"

//--------------------------------------------------------------------------------
CXMLNode::CXMLNode()
    :m_firstAttribute   (NULL)
    ,m_lastAttribute    (NULL)
    ,m_firstChildNode   (NULL)
    ,m_lastChildNode    (NULL)
{
}

//--------------------------------------------------------------------------------
CXMLNode::~CXMLNode()
{
}

//--------------------------------------------------------------------------------
CXMLNode* CXMLNode::GetFirstChildNode()
{
    return m_firstChildNode;
}

//--------------------------------------------------------------------------------
const CXMLNode* CXMLNode::GetFirstChildNode() const
{
    return m_firstChildNode;
}

//--------------------------------------------------------------------------------
CXMLNode* CXMLNode::GetLastChildNode()
{
    return m_lastChildNode;
}

//--------------------------------------------------------------------------------
const CXMLNode* CXMLNode::GetLastChildNode() const
{
    return m_lastChildNode;
}

//--------------------------------------------------------------------------------
void CXMLNode::InsertNode( CXMLNode* node)
{
    node->SetParent( this );
    node->SetPrevSibling( m_lastChildNode );
    node->SetNextSibling(NULL);
    m_lastChildNode->SetNextSibling( node );
}

//--------------------------------------------------------------------------------
void CXMLNode::InsertAttribute( CXMLAttribute* attribute )
{
    attribute->SetParent( this );
    attribute->SetNextSibling( NULL );
    attribute->SetPrevSibling( m_lastAttribute );
    m_lastAttribute->SetNextSibling( attribute );
}

//--------------------------------------------------------------------------------





