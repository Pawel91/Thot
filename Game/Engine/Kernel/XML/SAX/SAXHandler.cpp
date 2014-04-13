#include "Kernel_PCH.h"

#include "Kernel/XML/SAX/SAXHandler.h"
#include "Kernel/XML/SAX/SAXUtils.h"
#include "Kernel/XML/SAX/SAX.h"
#include "xercesc/sax/AttributeList.hpp"



//--------------------------------------------------------------------------------
ThotPrivateSAXHandler::ThotPrivateSAXHandler( ISAXParser* saxParser )
    : m_saxParser(saxParser)
{
    THOT_ASSERT(m_saxParser, "CANNOT PROVIDE A NULL PARSER");
}

//--------------------------------------------------------------------------------
ThotPrivateSAXHandler::~ThotPrivateSAXHandler()
{

}

//--------------------------------------------------------------------------------
void ThotPrivateSAXHandler::startElement( const XMLCh* const name, xercesc::AttributeList& nativeAttributes )
{
    CString elementName = SAXStringConverter::Convert(name);
    ISAXParser::TAttributesList attributes;
    attributes.Reserve(nativeAttributes.getLength());
    
    for( XMLSize_t i=0; i<nativeAttributes.getLength(); i++ )
    {
        thPair<CString,CString> pair;
        pair.m_first = SAXStringConverter::Convert( nativeAttributes.getName(i) );
        pair.m_second = SAXStringConverter::Convert( nativeAttributes.getValue(i) );
        attributes.PushBack( pair );
    }

    m_saxParser->OnStartElement( elementName, attributes );
}

//--------------------------------------------------------------------------------
void ThotPrivateSAXHandler::startDocument()
{
    m_saxParser->OnStartDocument();
}

//--------------------------------------------------------------------------------
void ThotPrivateSAXHandler::endDocument()
{
    m_saxParser->OnEndDocument();
}

//--------------------------------------------------------------------------------
void ThotPrivateSAXHandler::characters( const   XMLCh* const chars, const XMLSize_t length)
{
    CString characters = SAXStringConverter::Convert( chars );
    m_saxParser->OnCharacters( characters );
}

//--------------------------------------------------------------------------------
void ThotPrivateSAXHandler::endElement( const XMLCh* const name )
{
    CString elementName = SAXStringConverter::Convert( name );
    m_saxParser->OnEndElement( elementName);
}

void ThotPrivateSAXHandler::error(const xercesc::SAXParseException& exc)
{
    CString message = SAXStringConverter::Convert(exc.getMessage() );
    m_saxParser->OnError( message );
}

//--------------------------------------------------------------------------------
void ThotPrivateSAXHandler::fatalError(const xercesc::SAXParseException& exc)
{
    CString message = SAXStringConverter::Convert(exc.getMessage() );
    m_saxParser->OnFatalError( message );
}

//--------------------------------------------------------------------------------
void ThotPrivateSAXHandler::warning(const xercesc::SAXParseException& exc)
{
    CString message = SAXStringConverter::Convert(exc.getMessage() );
    m_saxParser->OnWarning( message );
}

//--------------------------------------------------------------------------------