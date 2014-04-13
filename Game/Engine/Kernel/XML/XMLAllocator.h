#if !defined(__KERNEL_XML_ALLOCATOR_H__)
#define __KERNEL_XML_ALLOCATOR_H__



class CXMLAllocator
{
public:
     CXMLAllocator();
    ~CXMLAllocator();


public:

    template<class XML_TYPE>
    XML_TYPE*       New();

    template<class XML_TYPE>
    void            Free( XML_TYPE* xmlNode );



}


#endif //__KERNEL_XML_ALLOCATOR_H__