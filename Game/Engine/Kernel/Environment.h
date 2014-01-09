#pragma once
#ifndef __KERNEL_ENVIRONMENT_H__
#define __KERNEL_ENVIRONMENT_H__

#include "DataTypes.h"
#include "Kernel\KernelDef.h"

class CString;


KERNEL_API Bool        ThGetEnvVariable        ( const CString& var, CString& outValue );
KERNEL_API Bool        ThSetEnvVariable        ( const CString& var, const CString& value );



#endif /*__KERNEL_ENVIRONMENT_H__*/