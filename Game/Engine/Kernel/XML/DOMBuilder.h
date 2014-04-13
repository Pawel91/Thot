#if !defined(__KERNEL_DOM_BUILDER_H__)
#define __KERNEL_DOM_BUILDER_H__

#include "Kernel/XML/SAX/SAX.h"

class KERNEL_API CDOMBuilder: public ISAXParser
{
public:
     CDOMBuilder();
    ~CDOMBuilder();

public:
    virtual void        OnStartDocument     (); 
    virtual void        OnEndDocument       (); 
    virtual void        OnStartElement      ( const CString elementName, TAttributesList& attributes); 
    virtual void        OnCharacters        ( const CString& string ); 
    virtual void        OnEndElement        ( const CString& elementName);
    virtual void        OnError             ( const CString& error );
    virtual void        OnFatalError        ( const CString& fatalError );
    virtual void        OnWarning           ( const CString& warning );
};


#endif 