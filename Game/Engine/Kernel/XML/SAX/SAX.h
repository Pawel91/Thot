#if !defined(__KERNEL_SAX_H__)
#define __KERNEL_SAX_H__


#include "Kernel/Basics.h"
#include "Kernel/DataStructures/Array/Vector.h"
#include "Kernel/DataStructures/CString.h"

class ThotPrivateSAXHandler;



class KERNEL_API ISAXParser
{
public:
    typedef thVector< thPair<CString, CString> > TAttributesList;

public:
                ISAXParser();
    virtual     ~ISAXParser();

public:

            void        Parse               ( const char* buffer, u64 size);

    virtual void        OnStartDocument     () = 0; 
    virtual void        OnEndDocument       () = 0; 
    virtual void        OnStartElement      ( const CString elementName, TAttributesList& attributes) = 0; 
    virtual void        OnCharacters        ( const CString& string ) = 0; 
    virtual void        OnEndElement        ( const CString& elementName) = 0; 
    virtual void        OnError             ( const CString& error ) = 0;
    virtual void        OnFatalError        ( const CString& fatalError ) = 0;
    virtual void        OnWarning           ( const CString& warning ) = 0;



private:
    char                        m_rawData[64];
    ThotPrivateSAXHandler*      m_privateHandler;

};

#endif //__KERNEL_SAX_H__