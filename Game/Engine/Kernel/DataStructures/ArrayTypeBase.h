#ifndef __KERNEL_ARRAY_TYPE_BASE_H__
#define __KERNEL_ARRAY_TYPE_BASE_H__


// a class that is composed of multiple elements of generic type T
template<class T>
class CArrayTypeBase
{
public:
    typedef T           TComponent;
    //static T*           dummyComponent;
    static const T&         Get(){static const T el; return el;}
    static u32              GetSizeofElement()  { return sizeof(T); }
};




#endif /*__KERNEL_ARRAY_TYPE_BASE_H__*/