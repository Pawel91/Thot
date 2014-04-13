#ifndef __KERNEL_XML_NODE_H__
#define __KERNEL_XML_NODE_H__

#include "Kernel/XML/XMLBase.h"

class CXMLAttribute;
 
class KERNEL_API CXMLNode: public IXMLBase
{
public:

    THOT_DECLARE_XML_CLASS(CXMLNode, EXmlNodeType_Element);

     CXMLNode();
    ~CXMLNode();


    CXMLNode*               GetFirstChildNode();
    CXMLNode*               GetLastChildNode();
    const CXMLNode*         GetFirstChildNode() const;
    const CXMLNode*         GetLastChildNode() const;

    void                    InsertNode( CXMLNode* node);
    void                    InsertAttribute( CXMLAttribute* attribute );

protected:
    IXMLBase*       m_firstAttribute;
    IXMLBase*       m_lastAttribute;
    CXMLNode*       m_firstChildNode;
    CXMLNode*       m_lastChildNode;
};



#endif