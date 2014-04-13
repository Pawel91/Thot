#if !defined(__KERNEL_SAX_HANDLER_H__)
#define __KERNEL_SAX_HANDLER_H__

#include "Kernel/Basics.h"
#include "xercesc/sax/HandlerBase.hpp"

#if !defined(KERNEL_EXPORTS)
#   error THIT IS A KERNEL PRIVATE HEADER
#endif

class ISAXParser;

class ThotPrivateSAXHandler: public xercesc::HandlerBase
{
    typedef xercesc::HandlerBase super;
public:
     ThotPrivateSAXHandler( ISAXParser* saxParser );
    ~ThotPrivateSAXHandler();

public:
    virtual void        startDocument   ()override;
    virtual void        endDocument     ()override;
    virtual void        startElement    ( const XMLCh* const, xercesc::AttributeList&  ) override;
    virtual void        characters      ( const   XMLCh* const chars, const XMLSize_t length) override;
    virtual void        endElement      ( const XMLCh* const name ) override;
    virtual void        error           (const xercesc::SAXParseException& exc) override;
    virtual void        fatalError      (const xercesc::SAXParseException& exc) override;
    virtual void        warning         (const xercesc::SAXParseException& exc) override;

private:
    ISAXParser*         m_saxParser; // does not own the parser
};


#endif //__KERNEL_SAX_HANDLER_H__