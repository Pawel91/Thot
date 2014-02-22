#if !defined(__KERNEL_RAPID_XML_CONFIG_H__)
#define __KERNEL_RAPID_XML_CONFIG_H__

#if defined(RAPIDXML_HPP_INCLUDED)
#   error rapidxml.hpp included before condig file.
#error

#define RAPIDXML_NO_STDLIB
#define RAPIDXML_NO_EXCEPTIONS
#define RAPIDXML_STATIC_POOL_SIZE   (64*1024)
#define RAPIDXML_DYNAMIC_POOL_SIZE  (64*1024)
#define RAPIDXML_ALIGNMENT          (sizeof(void*))
#define RAPIDXML_NO_STREAMS        


#endif //__KERNEL_RAPID_XML_CONFIG_H__