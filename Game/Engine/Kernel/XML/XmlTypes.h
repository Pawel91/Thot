#ifndef __KERNEL_XML_TYPES_H__
#define __KERNEL_XML_TYPES_H__



class EXmlNodeType
{
    EXmlNodeType_None
    EXmlNodeType_Document,      //!< A document node. Name and value are empty.
    EXmlNodeType_Element,       //!< An element node. Name contains element name. Value contains text of first data node.
    EXmlNodeType_Data,          //!< A data node. Name is empty. Value contains data text.
    EXmlNodeType_Cdata,         //!< A CDATA node. Name is empty. Value contains data text.
    EXmlNodeType_Comment,       //!< A comment node. Name is empty. Value contains comment text.
    EXmlNodeType_Declaration,   //!< A declaration node. Name and value are empty. Declaration parameters (version, encoding and standalone) are in node attributes.
    EXmlNodeType_Doctype,       //!< A DOCTYPE node. Name is empty. Value contains DOCTYPE text.
    EXmlNodeType_Pi             //!< A PI node. Name contains target. Value contains instructions.

    EXmlNodeType_Count
};






#endif __KERNEL_XML_TYPES_H__