#ifndef __KERNEL_RAPIDXML_CONVERTER_H__
#define __KERNEL_RAPIDXML_CONVERTER_H__
#include "Kernel/DebugSystem/DebugSystem.h"

#include <new>

#define RAPIDXML_NO_STDLIB
#define RAPIDXML_NO_EXCEPTIONS
#define assert THOT_ASSERT
#define RAPIDXML_STATIC_POOL_SIZE 1

void*   rapidXmlAllocator_allocate  ( thTSize size );
void    rapidXmlAllocator_free      ( void* data );

namespace std
{
    typedef thTSize size_t;
}

#include "rapidxml.hpp"
#undef assert

THOT_DECLARE_TEMPLATE_API(KERNEL_TEMPLATE_API, rapidxml::xml_document<char>);
THOT_DECLARE_TEMPLATE_API(KERNEL_TEMPLATE_API, rapidxml::xml_base<char> );
THOT_DECLARE_TEMPLATE_API(KERNEL_TEMPLATE_API, rapidxml::xml_attribute<char>);
THOT_DECLARE_TEMPLATE_API(KERNEL_TEMPLATE_API, rapidxml::xml_node<char> );



class CRapidXmlDocumentWrapper:public rapidxml::xml_document<char>
{
public:
    typedef rapidxml::xml_document<char> super;
    CRapidXmlDocumentWrapper()
    {
        super::set_allocator(rapidXmlAllocator_allocate, rapidXmlAllocator_free );
    }

    void    Parse         ( const char* text )
    {
        super::parse<ms_rapidXmlDefaultParsingFlags>( const_cast<char*>(text) );//safe to make const cast; because of the parsing flags that we use the text will not be modified
    }

private:
    static const int  ms_rapidXmlDefaultParsingFlags = rapidxml::parse_non_destructive | rapidxml::parse_validate_closing_tags;
};


#endif //__KERNEL_RAPIDXML_CONVERTER_H__