#include "Kernel_PCH.h"

#include "Kernel/XML/XMLBase.h"

IXMLBase::IXMLBase()
    :m_parent       (NULL)
    ,m_nextSibling  (NULL)
{
}

//--------------------------------------------------------------------------------
IXMLBase::~IXMLBase()
{
}

//--------------------------------------------------------------------------------
IXMLBase* IXMLBase::GetNextSibling()
{
    return m_nextSibling;
}

//--------------------------------------------------------------------------------
IXMLBase* IXMLBase::GetParent()
{
    return m_parent;
}

//--------------------------------------------------------------------------------
IXMLBase* IXMLBase::GetDocument()
{
    IXMLBase* node = this;
    while( node->GetParent() )
    {
        node = node->GetParent();
    }

    return node->GetNodeType() == EXmlNodeType_Document? node: NULL;
}

//--------------------------------------------------------------------------------
void IXMLBase::SetPrevSibling(IXMLBase* xmlNode)
{
    THOT_ASSERT( xmlNode != this);
    m_prevSibling = xmlNode;
}

//--------------------------------------------------------------------------------
IXMLBase* IXMLBase::GetPrevSibling()
{
    return m_prevSibling;
}

//--------------------------------------------------------------------------------
void IXMLBase::SetNextSibling( IXMLBase* xmlNode)
{
    THOT_ASSERT( xmlNode != this );
    m_nextSibling = xmlNode;
}

//--------------------------------------------------------------------------------
const IXMLBase* IXMLBase::GetNextSibling()const
{
    return m_nextSibling;
}

//--------------------------------------------------------------------------------
const IXMLBase* IXMLBase::GetPrevSibling()const
{
    return m_prevSibling;
}

//--------------------------------------------------------------------------------
const CString& IXMLBase::GetName()const
{
    return m_name;
}

//--------------------------------------------------------------------------------
void IXMLBase::SetName(const CString& name)
{
    m_name = name;
}

//--------------------------------------------------------------------------------
CString& IXMLBase::GetName()
{
    return m_name;
}

//--------------------------------------------------------------------------------
void IXMLBase::SetValue( const CString& value )
{
    m_value = value;
}

void IXMLBase::SetParent( IXMLBase* parent )
{
    THOT_ASSERT( parent != this);
    m_parent = parent;
}

//--------------------------------------------------------------------------------
const CString& IXMLBase::GetValue()const
{
    return m_value;
}

//--------------------------------------------------------------------------------
CString& IXMLBase::GetValue()
{
    return m_value;
}

//--------------------------------------------------------------------------------
