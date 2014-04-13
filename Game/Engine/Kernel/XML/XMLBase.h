#ifndef __KERNEL_XML_BASE_H__
#define __KERNEL_XML_BASE_H__

#include "Kernel/Basics.h"
#include "Kernel/XML/XMLConfig.h"
#include "Kernel/XML/XmlTypes.h"
#include "Kernel/DataStructures/CString.h"

class KERNEL_API IXMLBase
{
public:
                 IXMLBase();
    virtual     ~IXMLBase();


    virtual EXmlNodeType        GetNodeType()       = 0;

    IXMLBase*                   GetDocument();
    IXMLBase*                   GetParent();
    void                        SetParent( IXMLBase* parent );

    const CString&              GetName()const;
    CString&                    GetName();
    void                        SetName( const CString& name );

    const CString&              GetValue()const;
    CString&                    GetValue();
    void                        SetValue(const CString& value);

    IXMLBase*                   GetNextSibling();
    const IXMLBase*             GetNextSibling()const;
    void                        SetNextSibling( IXMLBase* xmlNode);

    IXMLBase*                   GetPrevSibling();
    const IXMLBase*             GetPrevSibling()const;
    void                        SetPrevSibling(IXMLBase* xmlNode);

    template<typename XMLTYPE>
    XMLTYPE* GetAs()
    {
        return GetNodeType() == XMLTYPE::GetStaticType()? static_cast<XMLTYPE*>(this);
    }

    template<typename XMLTYPE>
    XMLTYPE* GetNextSibling()
    {
        THOT_ASSERT( GetNodeType() == XMLTYPE::GetStaticType(), "SIBLINGS MUST HAVE SAME TYPE" );
        return static_cast<XMLTYPE>( GetNextSibling() );
    }

    //static EXmlNodeType GetStaticType()
    //{
    //    THOT_COMPILE_ASSERT2(false, "PLEASE OVERRIDE IN DERIVED CLASS");
    //}

protected:

    CString         m_name;
    CString         m_value;
    IXMLBase*       m_parent;
    IXMLBase*       m_nextSibling;
    IXMLBase*       m_prevSibling;
};


#define THOT_DECLARE_XML_CLASS(__class, __xmlNodeType)\
static EXmlNodeType GetStaticType()                                     \
{                                                                       \
    return __xmlNodeType;                                               \
}\
virtual EXmlNodeType GetNodeType()\
{\
    return __xmlNodeType;\
}




#endif