#include "Kernel_PCH.h"

#include "Kernel/DataStructures/CString.h"
#include "Kernel/Externals.h"

//--------------------------------------------------------------------------------
KERNEL_API const  CString g_dataPath = "Data//";
const float     CString::ms_growFactor = 0.25f;
const u64       CString::ms_invalidIndex = 0xffffffffffffffff;

//--------------------------------------------------------------------------------
CHeap& CString::GetStringHeap()
{
    static CHeap stringHeap( CHeap::FLAG_NONE, 1 * 1024 * 1024 * 1024, 0 );
    return stringHeap;
}

//--------------------------------------------------------------------------------
int CString::ToInt( )
{
    return atoi(m_pString);
}

//--------------------------------------------------------------------------------
void CString::InitFromOtherTemp( CString& other )
{
    if( m_allocator.IsOwnerOnStack() ^ other.m_allocator.IsOwnerOnStack() )
    {
        // One on stack and one on heap
        InitFromOther( other );
    }
    else
    {
        if( m_pString )
        {
            m_allocator.Free( m_pString);
        }

        m_nSize = other.m_nSize;
        m_nMaxSize = other.m_nMaxSize;
        m_ownBuffer = other.m_ownBuffer;
        m_pString = other.m_pString;

        other.m_pString = NULL;
        other.m_nSize = 0;
        other.m_nMaxSize = 0;
    }
}

//--------------------------------------------------------------------------------




