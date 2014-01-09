#include "Kernel_PCH.h"
#include "CriticalSection.h"
#include "Kernel/ThotWindows.h"
#include "Kernel/DebugSystem/Assert.h"
//-------------------------------------------------------------------
CCritSection::CCritSection()
{
    InitializeCriticalSection( (CRITICAL_SECTION*)m_rawData );
}

//-------------------------------------------------------------------
CCritSection::~CCritSection()
{
    THOT_COMPILE_ASSERT2( sizeof(CRITICAL_SECTION) <=sizeof(m_rawData), "INCREASE SIZEOF RAW DATA TO MACH NATIVE OBJECT SIZE" );
    DeleteCriticalSection( (CRITICAL_SECTION*)m_rawData );
}

//-------------------------------------------------------------------
void CCritSection::Lock()
{
    EnterCriticalSection( (CRITICAL_SECTION*)m_rawData );
}

//-------------------------------------------------------------------
void CCritSection::Unlock()
{
    LeaveCriticalSection( (CRITICAL_SECTION*)m_rawData );
}

//-------------------------------------------------------------------