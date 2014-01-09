#if !defined(__CRITICAL_SECTION_H__)
#define __CRITICAL_SECTION_H__

#include "Kernel/KernelDef.h"
#include "Kernel/DataTypes.h"


class KERNEL_API CCritSection
{
public:
    CCritSection    ();
    ~CCritSection   ();

public:
    void        Lock();
    void        Unlock();

private:
    // keep raw data so we can avoid the include of native headers in this header; includes are made only in .cpp file
    u8          m_rawData[64];
};


#endif //__CRITICAL_SECTION_H__