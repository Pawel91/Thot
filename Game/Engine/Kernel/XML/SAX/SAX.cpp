#include "Kernel_PCH.h"

#include "Kernel/XML/SAX/SAX.h"

#include "Kernel/XML/SAX/SAXHandler.h"
#include "Kernel/XML/SAX/SAXUtils.h"
#include "xercesc/parsers/SAXParser.hpp"
#include "xercesc/framework/MemBufInputSource.hpp"

//--------------------------------------------------------------------------------
ISAXParser::ISAXParser()
{
    THOT_COMPILE_ASSERT2(sizeof(ThotPrivateSAXHandler) < sizeof(m_rawData), "INCREASE SIZE OF PRIVATE DATA");
    m_privateHandler = new(m_rawData) ThotPrivateSAXHandler(this);
}

//--------------------------------------------------------------------------------
ISAXParser::~ISAXParser()
{
    m_privateHandler->~ThotPrivateSAXHandler();
}

//--------------------------------------------------------------------------------
void ISAXParser::Parse( const char* buffer, u64 size)
{
    try
    {
        xercesc::XMLPlatformUtils::Initialize();
    }
    catch(const xercesc::XMLException& toCatch)
    {
        (void)toCatch;
        THOT_ASSERT(false, "FAILED TO INIT xerxes: [%s]", SAXStringConverter::Convert(toCatch.getMessage()).c_str() );
    }

    try
    {
        xercesc::MemBufInputSource memoryBuffer ( (const XMLByte*)buffer, size, "SaxMemoryBuffer" );
        char rawData[sizeof(xercesc::SAXParser)];
        xercesc::SAXParser* parser = new(rawData) xercesc::SAXParser;
        parser->setDocumentHandler( m_privateHandler );
        parser->parse( memoryBuffer);
        parser->~SAXParser();
    }
    catch(const xercesc::XMLException& toCatch)
    {
        THOT_ASSERT(false, "FAILED TO INIT xerxes: [%s]", SAXStringConverter::Convert(toCatch.getMessage()).c_str() );
    }

    xercesc::XMLPlatformUtils::Terminate();
}

//--------------------------------------------------------------------------------