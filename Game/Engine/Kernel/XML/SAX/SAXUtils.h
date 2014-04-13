#if !defined(__KERNEL_SAX_UTILS_H__)
#define __KERNEL_SAX_UTILS_H__


#include "Kernel/Basics.h"
#include "Kernel/DataStructures/CString.h"
#include "xercesc/sax/HandlerBase.hpp"

class SAXStringConverter
{
public:

    static CString Convert( const XMLCh* const name );

};



#endif //__KERNEL_SAX_UTILS_H__