#include "Kernel_PCH.h"

#include "Kernel/XML/SAX/SAXUtils.h"
#include "xercesc/sax/HandlerBase.hpp"
#include "xercesc/util/XMLString.hpp"

//--------------------------------------------------------------------------------
CString SAXStringConverter::Convert( const XMLCh* const name )
{
    char* string = xercesc_3_1::XMLString::transcode(name);
    CString toRet(string);
    xercesc_3_1::XMLString::release(&string);
    return toRet;
}

//--------------------------------------------------------------------------------
