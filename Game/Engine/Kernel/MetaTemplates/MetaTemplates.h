#if !defined(__META_TEMPLATES_H__)
#define __META_TEMPLATES_H__



#include "TypeTraits.h"



namespace MetaTemplates
{

    template<class T>
    class CWrapper
    {
    public:
        typedef T Type;
    };


    template<int VAL>
    class CIntWrap
    {
    public:
        enum
        {
            value = VAL
        };
    };

    template< int a, int b>
    class CIsGreater
    {
    public:
        enum
        {
            value = a>b
        };
    };

    template< int a, int b>
    class CIsGreaterOrEqual
    {
    public:
        enum
        {
            value = (a >= b)
        };
    };


    template< int a, int b>
    class CEquals
    {
    public:
        enum
        {
            value = (a == b)
        };
    };


    template<bool BVAL, class T, class U>
    class enable_if;

    template<class T, class U>
    class enable_if<true, T, U>
    {
    public:
        typedef T result;
    };

    template<class T, class U>
    class enable_if<false, T, U>
    {
    public:
        typedef U result;
    };

    template< int a, int b>
    class CMax
    {
    public:
        enum
        {
            value = enable_if< CIsGreater<a,b>::value,  CIntWrap<a>, CIntWrap<b> >::result::value
        };
    };

    template< int a, int b>
    class CMin
    {
    public:
        enum
        {
            value = enable_if< CIsGreater<a,b>::value,  CIntWrap<b>, CIntWrap<a> >::result::value
        };
    };

    //--------------------------------------------------------------------------------
    template<int MIN, int MAX, int VAL>
    class Clamp
    {
    public:
        enum
        {
            value = CMax< CMin<MAX,VAL>::value, MIN >::value
        };
    };

    //--------------------------------------------------------------------------------
    template<int VALUE>
    class CNumberOfSetBits;

    template<>
    class CNumberOfSetBits<0>
    {
    public:
        enum
        {
            value = 0
        };
    };

    template<int VALUE>
    class CNumberOfSetBits
    {
    public:
        enum
        {
            value = ( VALUE & 1 ) + CNumberOfSetBits< (VALUE >> 1)>::value
        };
    };

    //--------------------------------------------------------------------------------
    template<int VALUE>
    class CIsPowerOf2
    {
    public:

        enum 
        {
            value = CNumberOfSetBits<VALUE>::value == 1
        };
    };


    //--------------------------------------------------------------------------------
    template<int VALUE, int MULTIPLE_OF>
    class CRoundToSmallerMultiple
    {
    public:
        static_assert( CIsPowerOf2<MULTIPLE_OF>::value == 1, "CRoundToSmallerMultiple template WORKS ONLY FOR POWER OF 2" );
        enum 
        {
            value = VALUE & ~(MULTIPLE_OF-1)
        };
    };
}


#endif //__META_TEMPLATES_H__