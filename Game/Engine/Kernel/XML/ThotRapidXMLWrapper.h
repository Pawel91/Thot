#if !defined(__KERNEL_THOT_RAPID_XML_WRAPPER_H__)
#define __KERNEL_THOT_RAPID_XML_WRAPPER_H__


#include "Kernel/Basics.h"

#include "Kernel/XML/RapidXMLConfig.h"

namespace rapidxml
{
    void parse_error_handler(const char *what, void *where)
    {
        THOT_ASSERT(false,"ERROR!! rapid xml parsing:[%s]", what);
    }
}

#include "Kernel/XML/rapidxml.hpp"


#endif //__KERNEL_THOT_RAPID_XML_WRAPPER_H__