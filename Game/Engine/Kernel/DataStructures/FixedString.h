#if !defined( __KERNEL_FIXED_STRING_H__)
#define __KERNEL_FIXED_STRING_H__

#include "Kernel/KernelDef.h"
#include "Kernel/Config.h"
#include "Kernel/DataTypes.h"
#include "Kernel/Defines.h"
#include "Kernel/MetaTemplates/MetaTemplates.h"

template<u32 SIZE>
class CFixedString
{
public:
    template<u32 S> friend class CFixedString;
    typedef CFixedString<SIZE>      TSelf;

    CFixedString();
    CFixedString( const char* str, thSize size ); 
    CFixedString( const char* szBuffer ); 

    template<u32 OTHER_SIZE>
    CFixedString( const CFixedString<OTHER_SIZE>& otherString );

public:
    const char*             c_str() const;

    template<u32 OTHER_SIZE>
    Bool    operator == ( const CFixedString<OTHER_SIZE>& otherString );

    template<u32 OTHER_SIZE>
    const TSelf&    operator = ( const CFixedString<OTHER_SIZE>& otherString );
    
    const TSelf&    operator = ( const char* szBuffer );

    template<u32 OTHER_SIZE>
    CFixedString< OTHER_SIZE + SIZE > operator + ( const CFixedString<OTHER_SIZE>& otherString );

    template<u32 OTHER_SIZE>
    const CFixedString<SIZE>& operator += ( const CFixedString<OTHER_SIZE>& otherString );

    const CFixedString<SIZE>& operator += ( const char* szBuffer );

    u32         GetLenght(){ return m_realSize;}

private:
    void        ZeroInit();

private:
    char        m_string[SIZE+1];
    u32         m_realSize;
};


#include "Kernel/DataStructures/FixedString.inl"

THOT_DECLARE_TEMPLATE_API( KERNEL_TEMPLATE_API, CFixedString<8> );
THOT_DECLARE_TEMPLATE_API( KERNEL_TEMPLATE_API, CFixedString<16> );
THOT_DECLARE_TEMPLATE_API( KERNEL_TEMPLATE_API, CFixedString<32> );
THOT_DECLARE_TEMPLATE_API( KERNEL_TEMPLATE_API, CFixedString<64> );
THOT_DECLARE_TEMPLATE_API( KERNEL_TEMPLATE_API, CFixedString<128> );
THOT_DECLARE_TEMPLATE_API( KERNEL_TEMPLATE_API, CFixedString<256> );
THOT_DECLARE_TEMPLATE_API( KERNEL_TEMPLATE_API, CFixedString<512> );

#endif //__KERNEL_FIXED_STRING_H__