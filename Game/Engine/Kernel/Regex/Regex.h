#ifndef __KERNEL_REGEX_H__
#define __KERNEL_REGEX_H__

#define __KERNEL_NOT_USE_REGEX_CLASS

// skip regex class compiling for now so we cand remove the boos dependency
#if !defined(__KERNEL_NOT_USE_REGEX_CLASS)


#include "Kernel\KernelDef.h"
#include "Kernel\DataTypes.h"
#include "Kernel\DataStructures\CString.h"
#include "Kernel\DataStructures\DataStructures.h"

class KERNEL_API CRegex
{

//*********************************************
//            CONSTR/DESTR
//*********************************************
public:

explicit    CRegex      ( const CString& regex, Bool bIgnoreCase = false );
    
            ~CRegex     ( );

    
//*********************************************
//            INTERFACE
//*********************************************
public:
    typedef thVector<CString>        TCaptures;

    Bool            GetRegexString      ( CString& out );
    CString         Replace             ( const CString& what, const CString& with );
    Bool            Match               ( const CString& string );
    Bool            Match               ( const CString& string, TCaptures& outCaptures );
    Bool            Find                ( const CString& string, TCaptures& outResult );


//*********************************************
//            HELPERS
//*********************************************
protected:



//*********************************************
//            MEMBERS
//*********************************************
protected:

    Bool                m_bIgnoreCase;
    void*               m_regex;

};



#endif //!defined(__KERNEL_NOT_USE_REGEX_CLASS)

#endif /*__KERNEL_REGEX_H__*/

