#if !defined(__KERNEL_XML_ATTRIBUTE_H__)
#define __KERNEL_XML_ATTRIBUTE_H__


#include "Kernel/XML/XMLBase.h"


class KERNEL_API CXMLAttribute: public IXMLBase
{
public:
    THOT_DECLARE_XML_CLASS( CXMLAttribute, EXmlNodeType_Attribute )

     CXMLAttribute();
    ~CXMLAttribute();


protected:
};



#endif //__KERNEL_XML_ATTRIBUTE_H__