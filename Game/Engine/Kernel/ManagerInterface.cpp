#include "Kernel_PCH.h"
#include "ManagerInterface.h"

IMPLEMENT_MANAGER_CLASS_ABSTRACT(CUpdateManager,CUpdateManager)
IMPLEMENT_MANAGER_CLASS_ABSTRACT(CUpdateDrawManager,CUpdateManager)
IMPLEMENT_MANAGER_CLASS_ABSTRACT(CManagerInterface,CUpdateDrawManager);    
